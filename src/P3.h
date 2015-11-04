/*
 * P3.h
 *
 *  Created on: Nov 3, 2015
 *      Author: goldman
 */

#ifndef P3_H_
#define P3_H_
#include "Solver.h"
#include "LocalSearch.h"
#include "LinkagePopulation.h"
#include <unordered_set>


class P3 : public Solver {
 public:
  P3(Random& _rand, shared_ptr<Problem> _problem, Configuration& _config);
  create_solver(P3);
  virtual bool iterate() override;
 protected:
  local_search::pointer ls;
  vector<LinkagePopulation> pyramid;
  std::unordered_set<vector<int>> seen;
  void add_if_unique(const vector<int> & solution, size_t level);
};

#endif /* P3_H_ */
