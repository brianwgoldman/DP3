// Brian Goldman

// This file aggregates optimization methods
// so that they can be chosen through configuration options

#ifndef SOLVERCOLLECTION_H_
#define SOLVERCOLLECTION_H_
#include "Solver.h"
#include "Configuration.h"

#include "RandomRestartLocalSearch.h"
#include "P3.h"

#include <unordered_map>

namespace solver {
// Renaming of the function pointer used to create new optimization methods
using pointer=shared_ptr<Solver> (*)(Random& rand, shared_ptr<Problem> evaluator, Configuration& config);

// Lookup table translates strings to function pointers
static std::unordered_map<string, pointer> lookup = {
    { "RandomRestartLocalSearch", RandomRestartLocalSearch::create },
    { "P3", P3::create },
};
}

#endif /* SOLVERCOLLECTION_H_ */
