/*
 * LinkagePopulation.h
 *
 *  Created on: Nov 3, 2015
 *      Author: goldman
 */

#ifndef LINKAGEPOPULATION_H_
#define LINKAGEPOPULATION_H_
#include "Util.h"
#include "LinkageTree.h"
#include "Problems.h"

class LinkagePopulation {
 public:
  LinkagePopulation(Random& rand, size_t length);
  virtual ~LinkagePopulation() = default;
  void add(const vector<int> & solution);
  void improve(vector<int> & solution, double & fitness, Problem* problem);
 protected:
  LinkageTree tree;
  vector<vector<int>> solutions;
  vector<int> options;
  Random& rand;
  bool donate(vector<int> & solution, double & fitness, vector<int> & source,
              const vector<int> & cluster, Problem* problem);
};

#endif /* LINKAGEPOPULATION_H_ */
