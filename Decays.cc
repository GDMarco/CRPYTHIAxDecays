#include "Decays.h"

#include "crpropa/Units.h"
#include "crpropa/Random.h"
#include "crpropa/Vector3.h"
#include "crpropa/Variant.h"
#include "crpropa/ParticleState.h"
#include "crpropa/Candidate.h"

#include <string>
#include <cstdlib>
#include <cmath>

#include "Pythia8/Pythia.h"

namespace Pythia8 {

class PythiaDecay {
private:
    
    std::vector<std::vector<double>> secondaries;
    
public:
    
    PythiaDecay() {
        Pythia pythia;
        pythia.init();
    };
    
    PythiaDecay(int Id, double E, crpropa::Vector3d dir, std::vector<int> IdDecaying, bool activeHadronization = false) {
        std::string xmlDir = "./";
        bool printBanner = false;
        Pythia pythia(xmlDir, printBanner); // pythia instance
        
        crpropa::Random rand;
        int seed = rand.randInt(900000000);
        pythia.readString("Random:setSeed = on");
        pythia.readString("Random:seed = " + std::to_string(seed));
        
        pythia.readString("ProcessLevel:all = off");
        if (activeHadronization) {
            pythia.readString("HadronLevel:Hadronize = on");
        } else {
            pythia.readString("HadronLevel:Hadronize = off");
        }
        
        for (std::size_t i = 0; i < IdDecaying.size(); i++)
            pythia.readString(std::to_string(IdDecaying[i]) + ":mayDecay = on"); // enable particle decay
        
        pythia.readString("Print:quiet = on");
        pythia.readString("Init:showAllSettings = off");
        pythia.readString("Init:showAllParticleData = off");
        
        pythia.init();
        generateSecondaries(Id, E, dir, pythia);
        
    };
    
    double getMomentum(double E, double mass) {
        return sqrt(E * E - mass * mass);
    };
    
    void generateSecondaries(int Id, double E, crpropa::Vector3d dir, Pythia& pythia) {
        
        this->secondaries.clear();
        
        double mass = pythia.particleData.m0(Id);
        
        Event& event = pythia.event;
        event.reset();
        
        double p = getMomentum(E, mass);
        
        // (id, status, mother1, mother2, daughter1, daughter2, color1, color2, px, py, pz, e, m)
        if (std::abs(Id) == 15) {
            // The tau polarization and tau decay correlation mechanism can be determined either using internal matrix elements or external SPINUP information provided in the event, e.g. via Les Houches Event Files (LHEF). The SPINUP digit is interpreted as the particle helicity state in the lab frame: -1 and 1 are longitudinal and 0 is transverse. Other values are not valid.
            double scale = 1.0; // to understand!
            int helicity;
            
            crpropa::Random random;
            double rand = random.randUniform(0, 1);
            
            if (rand < 1. / 3.) {
                helicity = 0;
            } else if (rand < 2. / 3.) {
                helicity = 1;
            } else {
                helicity = -1;
            }
            
            event.append(Id, 1, 0, 0, 0, 0, 0, 0, p * dir.x, p * dir.y, p * dir.z, E, mass, helicity, scale);
        } else {
            event.append(Id, 1, 0, 0, 0, 0, 0, 0, p * dir.x, p * dir.y, p * dir.z, E, mass);
        }
        
        if (!pythia.next()) {
            cout << "Event generation failed!" << endl;
        }
        
        std::vector<std::vector<double>> secondaries;
        
        for (std::size_t i = 0; i < event.size(); ++i) {
            if (event[i].isFinal()) {
                vector<double> prop = { (double) event[i].id(), event[i].px(), event[i].py(), event[i].pz(), event[i].e() };
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

static const double tau_muon = 2.1969811e-6 * crpropa::second; // averaged proper time of the muon decay
static const double mass_muon = 1.883531627e-28 * crpropa::kilogram;

static const double tau_tauon = 2.903e-13 * crpropa::second;
static const double mass_tauon = 3.167e-27 * crpropa::kilogram;

static const double tau_neutral_pion = 8.43e-17 * crpropa::second;

static const double tau_charged_pion = 2.6033e-8 * crpropa::second; // averaged proper time of the charged pion decay
static const double tau_W_boson = 3e-25 * crpropa::second;

// mass W boson
static const double massWGeV = 80.379;
static const double mass_W_boson = 1.43288582e-25 * crpropa::kilogram;

// static const double mW2 = (mWkg*c_light**2.) ** 2; //squared W mass [J^2/c^4]

// mass charged pion
static const double massChargedPionGeV = 139.57039e-3; // GeV / c^2
static const double massNeutralPionGeV = 134.9768e-3; // GeV / c^2

static const double mass_neutral_pion = mass_W_boson * massNeutralPionGeV / massWGeV;
static const double mass_charged_pion = mass_W_boson * massChargedPionGeV / massWGeV;
// static const double mcpic2 = mass_cpion * crpropa::c_squared;

Decays::Decays(bool haveOtherSecondaries, bool haveNeutrinos, bool angularCorrection, double limit) { // double thinning,
    
    // setThinning(thinning);
    setLimit(limit);
    setHaveOtherSecondaries(haveOtherSecondaries);
    setHaveNeutrinos(haveNeutrinos);
    setAngularCorrection(angularCorrection);
    setDescription("Decay from PYTHIA");
    
}

void Decays::setHaveOtherSecondaries(bool haveOtherSecondaries) {
    this->haveOtherSecondaries = haveOtherSecondaries;
}

void Decays::setHaveNeutrinos(bool haveNeutrinos) {
    this->haveNeutrinos = haveNeutrinos;
}

void Decays::setAngularCorrection(bool angularCorrection) {
    this->angularCorrection = angularCorrection;
}

void Decays::setLimit(double limit) {
    this->limit = limit;
}

/**
void Decays::setThinning(double thinning) {
    this->thinning = thinning;
}
*/

void Decays::performDecay(crpropa::Candidate *candidate) const {
    
    int Id = candidate->current.getId();
    double E = candidate->current.getEnergy();
    double z = candidate->getRedshift();
    double w = candidate->getWeight();
    crpropa::Vector3d dir = candidate->current.getDirection();
    crpropa::Vector3d pos0 = candidate->current.getPosition();
    double trajectoryLength = candidate->getTrajectoryLength();
    crpropa::Candidate::PropertyMap properties = candidate->properties;
    crpropa::ParticleState source = candidate->source;
    crpropa::ParticleState created = candidate->created;
    crpropa::ParticleState current = candidate->current;
    crpropa::ParticleState previous = candidate->previous;
    crpropa::Candidate* parent = candidate;
    
    candidate->setActive(false);
    
    std::vector<int> IdDecaying;
    bool hadronize;
    
    if (std::abs(Id) == 24) {
        IdDecaying = {13, 211, 130, 310, 311, 321};
        hadronize = true;
    } else if (std::abs(Id) == 211) {
        IdDecaying = {13, 211};
        hadronize = false;
    } else if (Id == 111) {
        IdDecaying = {111};
        hadronize = false;
    } else if (std::abs(Id) == 15) {
        IdDecaying = {13, 15, 211, 111, 130, 310, 311, 321};
        hadronize = true;
    } else {
        IdDecaying = {13};
        hadronize = false;
    }
    
    Pythia8::PythiaDecay pythiaDecay(Id, E / crpropa::GeV, dir, IdDecaying, hadronize);
    
    std::vector<std::vector<double>> secondaries = pythiaDecay.getSecondaries();
    
    std::string decayTag = getDecayTag();
    // double w = 1; // not developed the decay weight
    
    // sample random position along current step
    crpropa::Random &random = crpropa::Random::instance();
    crpropa::Vector3d pos = random.randomInterpolatedPosition(candidate->previous.getPosition(), candidate->current.getPosition());
    
    for (std::size_t i = 0; i < secondaries.size(); i++) {
        // to see how to use the w (it should be multiplicative)
        std::vector<double> row = secondaries[i];
        
        if ((std::abs(int(row[0])) == 12 or std::abs(int(row[0])) == 12 or std::abs(int(row[0])) == 12)) {
            if (haveNeutrinos) {
                // row[0], row[4] * crpropa::GeV, pos, cDir / cDir.getR(), z, w, decayTag
                crpropa::Candidate* c = new crpropa::Candidate();
                
                c->setRedshift(z);
                c->setTrajectoryLength(trajectoryLength - (pos0 - pos).getR());
                c->setWeight(w); // it inherits the weight from the parent
                c->setTagOrigin(decayTag);
                for (crpropa::Candidate::PropertyMap::const_iterator it = properties.begin(); it != properties.end(); ++it) {
                        c->setProperty(it->first, it->second);
                    }
                // it can be done more efficiently
                c->source = source;
                c->previous = previous;
                c->created = previous;
                c->current = current;
                
                c->current.setId(int(row[0]));
                c->current.setEnergy(row[4] * crpropa::GeV);
                c->current.setPosition(pos);
                c->created.setPosition(pos);
                if (angularCorrection) {
                    crpropa::Vector3d cDir(row[1], row[2], row[3]);
                    c->current.setDirection(cDir / cDir.getR());
                }
                c->parent = parent; // see which parameters the outputs take
                
                candidate->addSecondary(c);
            } else {
                return;
            }
        } else if (haveOtherSecondaries) {
            crpropa::Candidate* c = new crpropa::Candidate();
            
            c->setRedshift(z);
            c->setTrajectoryLength(trajectoryLength - (pos0 - pos).getR());
            c->setWeight(w); // it inherits the weight from the parent
            c->setTagOrigin(decayTag);
            
            for (crpropa::Candidate::PropertyMap::const_iterator it = properties.begin(); it != properties.end(); ++it) {
                    c->setProperty(it->first, it->second);
                }
            
            c->source = source;
            c->previous = previous;
            c->created = previous;
            c->current = current;
            c->current.setId(int(row[0]));
            c->current.setEnergy(row[4] * crpropa::GeV);
            c->current.setPosition(pos);
            c->created.setPosition(pos);
            if (angularCorrection) {
                crpropa::Vector3d cDir(row[1], row[2], row[3]);
                c->current.setDirection(cDir / cDir.getR());
            }
            c->parent = parent;
            candidate->addSecondary(c);
        } else {
            return;
        }
    }
}

void Decays::process(crpropa::Candidate *candidate) const {
    
    int Id = candidate->current.getId();
    double z = candidate->getRedshift();
    double E = candidate->current.getEnergy();
    double d = candidate->getTrajectoryLength();
    
    double t_lab, gamma;
    std::string tag;
    
    // muons, charged/neutral pions, tauons, W bosons
    if (std::abs(Id) == 13) {
        
        gamma = E / mass_muon / crpropa::c_squared;
        t_lab = gamma * tau_muon;
        
        tag = "MD";
        
    } else if (std::abs(Id) == 211) {
        
        gamma = E / mass_charged_pion / crpropa::c_squared;
        t_lab = gamma * tau_charged_pion;
        
        tag = "CPD";
        
    } else if (std::abs(Id) == 15) {
        
        gamma = E / mass_tauon / crpropa::c_squared;
        t_lab = gamma * tau_tauon;
        
        tag = "TD";
        
    } else if (Id == 111) {
        
        gamma = E / mass_neutral_pion / crpropa::c_squared;
        t_lab = gamma * tau_neutral_pion;
        
        tag = "NPD";
        
    } else if (std::abs(Id) == 24) {
        
        gamma = E / mass_W_boson / crpropa::c_squared;
        t_lab = gamma * tau_W_boson;
        
        tag = "WD";
        
    } else {
        return;
    }
    
    setDecayTag(tag);
        
    double beta = sqrt(1 - 1 / gamma / gamma);
    double distance = crpropa::c_light * beta * t_lab;
    double decayRate = 1 / distance; // see if to multiply for (1+z)
    
    // check if it makes sense
    crpropa::Random &random = crpropa::Random::instance();
    double randDistance = -log(random.rand()) / decayRate;
    
    if (d <= randDistance) {
        candidate->limitNextStep(limit / decayRate);
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

