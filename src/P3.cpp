/*
 * P3.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: goldman
 */

#include "P3.h"

P3::P3(Random& _rand, shared_ptr<Problem> _problem, Configuration& _config)
    : Solver(_rand, _problem, _config),
      ls(config.get<local_search::pointer>("local_search")) {

}

bool P3::iterate() {
  // generate a random solution
  auto solution = random_vector(rand, problem->variable_range());
  double fitness = problem->evaluate(solution);
  // perform a local search hill climber
  ls(rand, solution, fitness, problem);
  // perform crossover with each level of the pyramid
  add_if_unique(solution, 0);
  for (size_t level = 0; level < pyramid.size(); level++) {
    double previous = fitness;
    pyramid[level].improve(solution, fitness, problem.get());
    if (previous < fitness) {
      add_if_unique(solution, level + 1);
    }
  }

  // P3 never "converges"
  return true;
}

void P3::add_if_unique(const vector<int> & solution, size_t level) {
  auto result = seen.insert(solution);
  // if it was actually inserted
  if (result.second) {
    while (pyramid.size() <= level) {
      pyramid.emplace_back(rand, problem->variable_range().size());
    }
    pyramid[level].add(solution);
  }
}
