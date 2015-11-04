/*
 * LinkagePopulation.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: goldman
 */

#include "LinkagePopulation.h"

LinkagePopulation::LinkagePopulation(Random& _rand, size_t length) : tree(_rand, length), rand(_rand) {

}

void LinkagePopulation::add(const vector<int> & solution) {
  tree.add(solution);
  solutions.push_back(solution);
  options.push_back(solutions.size() - 1);
}

void LinkagePopulation::improve(vector<int> & solution, double & fitness, Problem* problem) {
  for (const auto & cluster : tree.get_clusters()) {
    int unused = options.size() - 1;
    bool donor_found = false;

    // Find a donor which has at least one gene value different
    // from the current solution for this cluster of genes
    do {
     // Choose a donor
     size_t index = std::uniform_int_distribution<size_t>(0, unused)(rand);
     size_t working = options[index];
     // make certain that donor cannot be chosen again
     std::swap(options[unused], options[index]);
     unused -= 1;

     // Attempt the donation
     donor_found = donate(solution, fitness, solutions[working], cluster, problem);
     // Break loop if configured to stop_after_one or donate returned true
    } while (unused >= 0 and not donor_found);
  }
}

bool LinkagePopulation::donate(vector<int> & solution, double & fitness, vector<int> & source, const vector<int> & cluster, Problem* problem) {
  // swap all of the cluster indices, watching for any change
  bool changed = false;
  for (const auto& index : cluster) {
    changed |= (solution[index] != source[index]);
    // uses the "source" to store the original value of "solution"
    std::swap(solution[index], source[index]);
  }
  if (changed) {
    double new_fitness = problem->evaluate(solution);
    if (fitness <= new_fitness) {
      // improvement made, keep change to solution
      fitness = new_fitness;
      // copy pattern back into the source, leave solution changed
      for (const auto& index : cluster) {
        source[index] = solution[index];
      }
    } else {
      // revert both solution and source
      for (const auto& index : cluster) {
        std::swap(solution[index], source[index]);
      }
    }
  }
  return changed;

}
