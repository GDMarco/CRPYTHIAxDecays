#include "Decays.h"

#include "crpropa/Units.h"
#include "crpropa/Random.h"

#include <string>
#include <cstdlib>
#include <cmath>

#include "Pythia8/Pythia.h"

namespace Pythia8 {

class PythiaDecay {
private:
    Pythia pythia; // pythia instance
    std::vector<std::vector<double>> secondaries;
    
public:
    
    PythiaDecay() {
        Pythia pythia;
        pythia.init();
    };
    
    PythiaDecay(std::vector<int> IdDecaying, bool activeHadronization = false) {
        Pythia pythia;
        
        // Turn off process-level generation and enable hadronization
        pythia.readString("ProcessLevel:all = off");
        if (activeHadronization)
            pythia.readString("HadronLevel:Hadronize = on");
        
        for (int i; i < IdDecaying.size(); i++)
            pythia.readString(std::to_string(IdDecaying[i]) + ":mayDecay = on"); // Enable particle decay
        
        pythia.init();
    };
    //~PythiaDecay();
    
    // void initGeneratorDecay(int Id, double E); // check the units.
    // double mass, The mass can be taken from the Id in pythia directly.
    
    double getMomentum(double E, double mass) {
        return sqrt(E * E - mass * mass);
    };
    
    void generateSecondaries(int Id, double E) {
        double mass = pythia.particleData.m0(Id);
        
        Event& event = pythia.event;
        event.reset();
        
        double p = getMomentum(E, mass);
        
        // (id, status, mother1, mother2, daughter1, daughter2, color1, color2, px, py, pz, e, m)
        // particle momentum all along the x axis
        event.append(Id, 1, 0, 0, 0, 0, 0, 0, p, 0.0, 0.0, E, mass);
        
        if (!pythia.next()) {
            cout << "Event generation failed." << endl;
        }
        
        std::vector<std::vector<double>> secondaries;
        
        for (int i = 0; i < event.size(); ++i) {
            if (event[i].isFinal()) {
                vector<double> prop = { (double) event[i].id(), event[i].e()};
                // event[i].px(),
                secondaries.push_back(prop);
            }
        }
        
        this->secondaries = secondaries;
    };
    
    std::vector<std::vector<double>> getSecondaries() {
        return this->secondaries;
    };
};
} // end Pythia8 namespace


// namespace crpropa {

static const double tau_muon = 2.1969811e-6 * crpropa::second; // averaged proper time of the muon decay
static const double mass_muon = 1.883531627e-28 * crpropa::kilogram;

static const double tau_charged_pion = 2.6033e-8 * crpropa::second; // averaged proper time of the charged pion decay
// mass W boson
static const double massWGeV = 80.379;
static const double mWkg = 1.43288582 * 1e-25; // kg
// static const double mW2 = (mWkg*c_light**2.) ** 2; //squared W mass [J^2/c^4]

// mass charged pion
static const double massPionGeV = 139.57039e-3; // GeV/c^2
static const double mass_cpion = mWkg * massPionGeV / massWGeV * crpropa::kilogram;
static const double mcpic2 = mass_cpion * crpropa::c_squared;

Decays::Decays(bool haveSecondaries) { // double thinning, double limit
    
    // setThinning(thinning);
    // setLimit(limit);
    setHaveSecondaries(haveSecondaries);
    setDescription("Decay from PYTHIA");
    
}

void Decays::setHaveSecondaries(bool haveSecondaries) {
    this->haveSecondaries = haveSecondaries;
}

/**
void EMMuonPairProduction::setLimit(double limit) {
    this->limit = limit;
}


void EMMuonPairProduction::setThinning(double thinning) {
    this->thinning = thinning;
}
*/

void Decays::performDecay(crpropa::Candidate *candidate) const {
    
    int Id = candidate->current.getId();
    double E = candidate->current.getEnergy();
    
    // I'd need to change the Candidate.cpp in order to get the Vector3d dir.
    // double px =
    
    candidate->setActive(false);
    
    if (not haveSecondaries)
        return;
    
    /**
    if (std::abs(Id) == 13) {
        double mass = mass_muon; // kg
    } else {
        double mass = mass_cpion; // kg
    }
    */
    
    std::vector<int> IdDecaying = {13, 211};
    bool hadronize = false;
    Pythia8::PythiaDecay pythiaDecay(IdDecaying, hadronize);
    
    pythiaDecay.generateSecondaries(Id, E / crpropa::GeV);
    std::vector<std::vector<double>> secondaries = pythiaDecay.getSecondaries(); // pay attention to the units! here in CRPropa the SI is used, so convert before using.
    
    std::string decayTag = getDecayTag();
    double w = 1; // not developed
    // sample random position along current step
    crpropa::Random &random = crpropa::Random::instance();
    crpropa::Vector3d pos = random.randomInterpolatedPosition(candidate->previous.getPosition(), candidate->current.getPosition());
    
    for (int i = 0; i < secondaries.size(); i++) {
        // to see how to use the w (it should be multiplicative), dir and z...
        // in addSecondary(...) z and dir are not allowed as arguments
        std::vector<double> row = secondaries[i];
        candidate->addSecondary(row[0], row[1] * crpropa::GeV, pos, w, decayTag); // , dir, z, w, ?
    }
    
}

void Decays::process(crpropa::Candidate *candidate) const {
    
    int Id = candidate->current.getId();
    // double z = candidate->getRedshift();
    double E = candidate->current.getEnergy();
    double d = candidate->getTrajectoryLength();
    
    double t_lab, gamma;
    std::string tag;
    // only for muons and charged pions
    if (std::abs(Id) == 13) {
        
        gamma = E / mass_muon / crpropa::c_squared;
        t_lab = gamma * tau_muon;
        
        tag = "MD";
        
    } else if (std::abs(Id) == 211) {
    
        gamma = E / mcpic2;
        t_lab = gamma * tau_charged_pion;
        
        tag = "CPD";
        
    } else {
        return;
    }
    
    setDecayTag(tag);
        
    double beta = sqrt(1 - 1 / gamma / gamma);
    double distance = crpropa::c_light * beta * t_lab;
    double decayRate = 1 / distance;
    
    // check if it makes sense
    crpropa::Random &random = crpropa::Random::instance();
    double randDistance = -log(random.rand()) / decayRate;
    
    if (d < randDistance) {
        return;
    } else {
        performDecay(candidate);
        return;
    }
}

void Decays::setDecayTag(std::string tag) const {
    this->decayTag = tag;
}

std::string Decays::getDecayTag() const {
    return this->decayTag;
}

// } // end namespace crpropa

