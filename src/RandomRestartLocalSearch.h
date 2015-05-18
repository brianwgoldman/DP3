/*
 * RandomRestartLocalSearch.h
 *
 *  Created on: May 18, 2015
 *      Author: goldman
 */

#ifndef RANDOMRESTARTLOCALSEARCH_H_
#define RANDOMRESTARTLOCALSEARCH_H_

#include "Solver.h"
#include "LocalSearch.h"

class RandomRestartLocalSearch : public Solver {
 public:
  RandomRestartLocalSearch(Random& _rand, shared_ptr<Problem> _problem, Configuration& _config);
  create_solver(RandomRestartLocalSearch);
  virtual bool iterate() override;
 protected:
  local_search::pointer ls;

};

#endif /* RANDOMRESTARTLOCALSEARCH_H_ */
