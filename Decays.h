#include <crpropa/Module.h>
#include <crpropa/Candidate.h>

#include<string>

class Decays : public crpropa::Module {
private:
    
    bool haveOtherSecondaries;
    bool haveNeutrinos;
    bool angularCorrection;
    double limit;
    // double thinning;
    mutable std::string decayTag;

public:
    
    /** Constructor
     @param haveOtherSecondaries    if true, add secondary particles as candidates that are not neutrinos
     @param haveNeutrinos    if true, add secondary neutrinos as candidates
     @param angularCorrection    if true, consider the decay angular distribution of the secondaries
     // @param thinning        weighted sampling of secondaries (0: all particles are tracked; 1: maximum thinning)
     @param limit            step size limit as fraction of mean free path
     */
    Decays(bool haveOtherSecondaries = false, bool haveNeutrinos = false, bool angularCorrection = false, double limit = 0.1); // double thinning = 0,
    
    void setHaveOtherSecondaries(bool haveOtherSecondaries);
    
    void setHaveNeutrinos(bool haveNeutrinos);
    
    void setAngularCorrection(bool angularCorrection);
    
    /** Limit the propagation step to a fraction of the mean free path
     * @param limit fraction of the mean free path
     */
    void setLimit(double limit);
    
    /** Apply thinning with a given thinning factor
     * @param thinning factor of thinning (0: no thinning, 1: maximum thinning)
     */
    // void setThinning(double thinning);
    
    void setDecayTag(std::string tag) const;
    std::string getDecayTag() const;
    
    void performDecay(crpropa::Candidate *candidate) const;
    void process(crpropa::Candidate *candidate) const;
};
