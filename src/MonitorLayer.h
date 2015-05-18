/*
 * MonitorLayer.h
 *
 *  Created on: May 18, 2015
 *      Author: goldman
 */

#ifndef MONITORLAYER_H_
#define MONITORLAYER_H_
#include <chrono>

#include "Problems.h"
#include "Record.h"

using std::chrono::steady_clock;

class MonitorLayer : public Problem {
 public:
  MonitorLayer(Configuration& config, std::shared_ptr<Problem> _problem);
  double virtual evaluate(const vector<int> & solution) override;
  const vector<int>& variable_range() const override {
    return problem->variable_range();
  }

  Record record;
  // Used to track total run time.
  void start_clock() {
    start_time = steady_clock::now();
  }

  // Returns the number of seconds elapsed between start_clock() and best fitness found.
  double seconds_elapsed() {
    return std::chrono::duration<double>(steady_clock::now() - start_time).count();
  }
  bool time_remaining() {
    return seconds_elapsed() < maximum_seconds;
  }
 private:
  steady_clock::time_point start_time;

  std::shared_ptr<Problem> problem;
  int evaluations;
  int maximum_evaluations;
  double maximum_seconds;
  double maximum_fitness;
};

#endif /* MONITORLAYER_H_ */
