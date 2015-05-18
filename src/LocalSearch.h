// Brian Goldman

// There are many ways to perform local search, and this
// file contains the implementation for a lot of configuration options.
// In all published experiments (so far) "first_improvement" was used,
// for the Random Restart HC and P3, with "no_action" used for LTGA and hBOA.
// Other methods were informally tested.

#ifndef LOCALSEARCH_H_
#define LOCALSEARCH_H_

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include "Problems.h"
#include "Configuration.h"
#include "Util.h"

using std::shared_ptr;

namespace local_search {
// Creates a type name for pointers to hill climbing functions
using pointer=void (*)(Random & rand, vector<int> & solution, double & fitness, shared_ptr<Problem> problem);

// Each time an improvement is found, it is immediately kept, with search progressing
// from the modified solution
void first_improvement(Random & rand, vector<int> & solution, double & fitness,
                       shared_ptr<Problem> problem);

// Mapping used to convert configuration string names to actual function pointers
static std::unordered_map<string, pointer> lookup = {
  { "first_improvement", first_improvement },
};
}

#endif /* LOCALSEARCH_H_ */
