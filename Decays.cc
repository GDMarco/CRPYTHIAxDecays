#include "Decays.h"
#include "PythiaDecay.h"

#include "crpropa/Units.h"
#include "crpropa/Random.h"

#include <string>
#include <cstdlib>
#include <cmath>

namespace crpropa {

static const tau_muon = 2.1969811e-6 * s; // averaged proper time of the muon decay
static const mass_muon = 1.883531627e-28 * kilogram;

static const tau_charged_pion = 2.6033e-8 * s; // averaged proper time of the charged pion decay
// mass W boson
static const double massWGeV = 80.379;
static const double mWkg = 1.43288582 * 1e-25; // kg
// static const double mW2 = (mWkg*c_light**2.) ** 2; //squared W mass [J^2/c^4]

// mass charged pion
static const double massPionGeV = 139.57039e-3; // GeV/c^2
static const double mass_cpion = mWkg * massPionGeV / massWGeV * kilogram;
static const double mcpic2 = mass_cpion * c_squared;

Decays::Decays(bool haveSecondaries) { // double thinning, double limit
    
    // setThinning(thinning);
    // setLimit(limit);
    setHaveSecondaries(haveSecondaries);
    
    setDescription("Decay from PYTHIA");
    // tablePath = "/dir/to/table/";
    // initDecayTime(tablePath + "decayTable.txt");
    
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


void Decays::initDecayTime(std::string filename) {
    
    std::ifstream infile(filename.c_str());
    
    if (!infile.good())
        throw std::runtime_error("CRPYTHIAxDecay: could not open file " + filename);
    
    tabIDs.clean();
    tabDecayTime.clean();
    
    while (infile.good()) {
        if (infile.peek() != '#') {
            int a;
            double b;
            
            infile >> a >> b;
            
            if (infile) {
                tabIDs.push_back(a);
                tabDecayTime.push_back(b);
            }
        }
        infile.ignore(std::numeric_limits < std::streamsize > ::max(), '\n');
    }
    infile.close();
}
 */

void Decays::performDecay(Candidate *candidate) const {
    
    int Id = candidate->current.getId();
    double E = candidate->current.getEnergy();
    
    // I'd need to change the Candidate.cpp in order to get the Vector3d dir.
    // double px =
    
    candidate->setActive(false);
    
    if (not haveMuons)
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
    PythiaDecay pythiaDecay(IdDecaying, hadronize);
    
    this->pythiaDecay = pythiaDecay;
    this->pythiaDecay.generateSecondaries(Id, E / GeV);
    
    std::vector<std::vector<double>> secondaries = this->pythiaDecay.getSecondaries(); // pay attention to the units! here in CRPropa the SI is used, so convert before using.
    
    std::string decayTag = getDecayTag();
    double w = 1; // not developed
    // sample random position along current step
    Random &random = Random::instance();
    Vector3d pos = random.randomInterpolatedPosition(candidate->previous.getPosition(), candidate->current.getPosition());
    
    for (int i = 0; i < secondaries.size(); i++) {
        // to see how to use the w (it should be multiplicative), dir and z...
        // in addSecondary(...) z and dir are not allowed as arguments
        std::vector<double> row = secondaries[i];
        candidate->addSecondary(row[0], row[1] * GeV, pos, w, decayTag); // , dir, z, w, ?
    }
    
}

void Decays::process(Candidate *candidate) const {
    
    int Id = candidate->current.getId();
    // double z = candidate->getRedshift();
    double E = candidate->current.getEnergy();
    double d = candidate->current.getTrajectoryLenght();
    
    if (std::abs(Id) == 13) {
        
        double gamma = E / mass_muon / c_squared;
        double t_lab = gamma * tau_muon;
        
        setInteractionTag('MD');
        
    } else if (std::abs(Id) == 211) {
    
        double gamma = E / mcpic2;
        double t_lab = gamma * tau_charged_pion;
        
        setInteractionTag('CPD');
        
    } else {
        return;
    }
    
    double beta = sqrt(1 - 1 / gamma / gamma);
    double distance = c_light * beta * t_lab;
    double decayRate = 1 / distance;
    
    // check if it makes sense
    Random &random = Random::instance();
    double randDistance = -log(random.rand()) / decayRate;
    
    if (d < randDistance) {
        return;
    } else {
        performDecay(candidate);
        return;
    }
}

void Decays::setDecayTag(std::string tag) {
    this->interactionTag = tag;
}

std::string Decays::getDecayTag() {
    return this->interactionTag;
}

} // end namespace crpropa
