/*
 * LinkageTree.h
 *
 *  Created on: Nov 3, 2015
 *      Author: goldman
 */

#ifndef LINKAGETREE_H_
#define LINKAGETREE_H_
#include "Util.h"
#include <unordered_map>
using std::unordered_map;

class PairFrequency {
 public:
  void add(int first, int second) {
    pairings[{first, second}] ++;
    first_counts[first] ++;
    second_counts[second] ++;
  }
  double distance(const double total);
 protected:
  unordered_map<std::pair<int, int>, int> pairings;
  unordered_map<int, int> first_counts, second_counts;
};

class LinkageTree {
 public:
  LinkageTree(Random& _rand, size_t length);
  virtual ~LinkageTree() = default;

  void add(const vector<int> & solution);
  const vector<vector<int>>& get_clusters();
 protected:
  Random& rand;
  vector<vector<PairFrequency>> occurrences;
  vector<vector<int>> clusters;
  size_t length;
  size_t added;
  bool rebuild_required;
  void rebuild();
  void advance_path(vector<int>& top_level, size_t& end_of_path, const vector<vector<double>> & distances);
  void order_clusters(const vector<bool> & useful);
};

#endif /* LINKAGETREE_H_ */
