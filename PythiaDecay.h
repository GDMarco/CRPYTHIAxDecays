#ifndef PYTHIADECAY_H
#define PYTHIADECAY_H

#include "Pythia8/Pythia.h"

namespace Pythia8 {

class PythiaDecay {
private:
    Pythia pythiaInit; // pythia instance
    std::vector<std::vector> secondaries;
    
public:
    
    PythiaDecay();
    PythiaDecay(std::vector<int> IdDecaying, bool activeHadronization = false);
    //~PythiaDecay();
    
    // void initGeneratorDecay(int Id, double E); // check the units.
    // double mass, The mass can be taken from the Id in pythia directly.
    
    double getMomentum(double E, double mass);
    
    void generateSecondaries(int ID, double E);
    std::vector<std::vector<double>> getSecondaries();
};

} // end Pythia8 namespace

#endif
