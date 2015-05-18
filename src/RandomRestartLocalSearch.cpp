/*
 * RandomRestartLocalSearch.cpp
 *
 *  Created on: May 18, 2015
 *      Author: goldman
 */

#include "RandomRestartLocalSearch.h"

RandomRestartLocalSearch::RandomRestartLocalSearch(Random& _rand,
                                                   shared_ptr<Problem> _problem,
                                                   Configuration& _config)
    : Solver(_rand, _problem, _config),
      ls(config.get<local_search::pointer>("local_search")) {
}

bool RandomRestartLocalSearch::iterate() {
  auto solution = random_vector(rand, problem->variable_range());
  double fitness = problem->evaluate(solution);
  ls(rand, solution, fitness, problem);
  return true;
}
