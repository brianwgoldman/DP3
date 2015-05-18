/*
 * MonitorLayer.cpp
 *
 *  Created on: May 18, 2015
 *      Author: goldman
 */

#include "MonitorLayer.h"
#include <limits>

MonitorLayer::MonitorLayer(Configuration& config, std::shared_ptr<Problem> _problem) : record(config), problem(_problem), evaluations(0) {
  maximum_evaluations = config.get<int>("max_evaluations");
  if (maximum_evaluations < 0) {
    maximum_evaluations = std::numeric_limits<int>::max();
  }
  maximum_seconds = config.get<double>("max_seconds");
  if (maximum_seconds < 0) {
    maximum_seconds = std::numeric_limits<double>::max();
  }
  maximum_fitness = config.get<double>("max_fitness");
  if (maximum_fitness < 0) {
    maximum_fitness = std::numeric_limits<double>::max();
  }
  start_clock();
}

double MonitorLayer::evaluate(const vector<int> & solution) {
  evaluations++;
  auto fitness = problem->evaluate(solution);
  if (record.empty() or record.best().fitness < fitness) {
    double seconds = seconds_elapsed();
    record.add(evaluations, seconds, fitness, solution);
  }
  if (evaluations >= maximum_evaluations or fitness >= maximum_fitness) {
    throw StopIteration();
  }
  return fitness;
}
