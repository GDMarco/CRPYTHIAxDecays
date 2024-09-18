// #ifndef DECAYS_H
// #define DECAYS_H
#include <crpropa/Module.h>
#include <crpropa/Candidate.h>

#include<string>

// namespace crpropa {

class Decays : public crpropa::Module {
private:
    
    bool haveSecondaries;
    // double limit;
    // double thinning;
    mutable std::string decayTag;

public:
    
    /** Constructor
     @param haveSecondaries    if true, add secondary particles as candidates
     // @param thinning        weighted sampling of secondaries (0: all particles are tracked; 1: maximum thinning)
     // @param limit            step size limit as fraction of mean free path
     */
    Decays(bool haveSecondaries = false); // double thinning = 0,double limit = 0.1
    
    void setHaveSecondaries(bool haveSecondaries);
    
    /** Limit the propagation step to a fraction of the mean free path
     * @param limit fraction of the mean free path
     */
    // void setLimit(double limit);
    
    /** Apply thinning with a given thinning factor
     * @param thinning factor of thinning (0: no thinning, 1: maximum thinning)
     */
    // void setThinning(double thinning);
    
    void setDecayTag(std::string tag) const;
    std::string getDecayTag() const;
    
    void performDecay(crpropa::Candidate *candidate) const;
    void process(crpropa::Candidate *candidate) const;
};

//} // end crpropa namespace

// #endif
