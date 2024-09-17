#include "PythiaDecay.h"
#include "Pythia8/Pythia.h"

namespace Pythia8 {

PythiaDecay::PythiaDecay() {
    Pythia pythia;
};

PythiaDecay::PythiaDecay(std::vector<int> IdDecaying, bool activeHadronization) {
    Pythia pythia;
    
    // Turn off process-level generation and enable hadronization
    pythia.readString("ProcessLevel:all = off");
    if (activeHadronization)
        pythia.readString("HadronLevel:Hadronize = on");
    
    for (int i; i < IdDecaying.size(); i++)
        pythia.readString(std::to_string(IdDecaying[i]) + ":mayDecay = on"); // Enable particle decay
    
    this->pythiaInit = pythia.init();
}

double PythiaDecay::getMomentum(double E, double mass) {
    return sqrt(E * E - mass * mass);
}

void PythiaDecay::generateSecondaries(int Id, double E) {
    double mass = this->pythiaInit.particleData.m0(Id);
    
    Event& event = this->pythiaInit.event;
    event.reset();
    
    double p = momentum(E, mass);
    
    // (id, status, mother1, mother2, daughter1, daughter2, color1, color2, px, py, pz, e, m)
    // particle momentum all along the x axis
    event.append(Id, 1, 0, 0, 0, 0, 0, 0, p, 0.0, 0.0, E, mass);
    
    if (!pythia.next()) {
        cout << "Event generation failed." << endl;
    }
    
    vector<vector<double>> secondaries;
    
    for (int i = 0; i < event.size(); ++i) {
        if (event[i].isFinal()) {
            vector<double> prop = { (double) event[i].id(), event[i].e()};
            // event[i].px(),
            secondaries.push_back(prop);
        }
    }
    
    this->secondaries = secondaries;
}

std::vector<std::vector<double>> PythiaDecay::getSecondaries() {
    return this->secondaries;
}

} // end namespace Pythia8
