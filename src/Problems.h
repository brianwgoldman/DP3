#ifndef PROBLEMS_H_
#define PROBLEMS_H_
#include <unordered_map>
#include <memory>

#include "Util.h"
#include "Configuration.h"
#include <math.h>

// This macro is used to define a factory function, simplifying the transition from
// configuration option to object capable of performing evaluation.
#define create_problem(name)\
static std::shared_ptr<Problem> create(Configuration& config){\
  return std::shared_ptr<Problem>(new name(config));\
}

// Base class to define the interface for evaluation functions
class Problem {
 public:
  Problem() = default;
  virtual ~Problem() = default;
  double virtual evaluate(const vector<int> & solution) = 0;
  const virtual vector<int>& variable_range() const {
    return value_range;
  }
 protected:
  vector<int> value_range;
  void construct_range(Configuration & config);
};

class ValueMax : public Problem {
 public:
  ValueMax(Configuration& config);
  double virtual evaluate(const vector<int> & solution) override;
  create_problem(ValueMax);
 protected:
  int maximum_fitness;
};

class DeceptiveTrap : public Problem {
 public:
  DeceptiveTrap(Configuration& config);
  double virtual evaluate(const vector<int> & solution) override;
  create_problem(DeceptiveTrap);
 protected:
  int maximum_fitness;
};

class PairsEqual : public Problem {
 public:
  PairsEqual(Configuration& config);
  double virtual evaluate(const vector<int> & solution) override;
  create_problem(PairsEqual);
 protected:
  int maximum_fitness;
};

class Rastrigin : public Problem {
 public:
  Rastrigin(Configuration& config) { construct_range(config); };
  double virtual evaluate(const vector<int> & solution) override;
  create_problem(Rastrigin);
};

class HIFF : public Problem {
 public:
  HIFF(Configuration& config);
  double virtual evaluate(const vector<int> & solution) override;
  create_problem(HIFF);
 protected:
  int maximum_fitness;
};

// This object uses external scripts to determine the fitness
// of a solution. It writes out the solution, calls the script,
// then reads in the fitness value.
class External : public Problem {
 public:
  External(Configuration& config, int run_number)
      : script_file(config.get<string>("script_path")),
        out_file(config.get<string>("external_out")),
        in_file(config.get<string>("external_in")) {
  }
  double evaluate(const vector<int> & solution) override;
  create_problem(External);

 private:
  string script_file;
  string out_file;
  string in_file;
};


namespace problem {
using pointer=std::shared_ptr<Problem> (*)(Configuration &);
static std::unordered_map<string, pointer> lookup = {
    { "ValueMax", ValueMax::create },
    { "DeceptiveTrap", DeceptiveTrap::create },
    { "PairsEqual", PairsEqual::create },
    { "Rastrigin", Rastrigin::create },
    { "HIFF", HIFF::create },
    { "External", External::create },
};
}

#endif /* PROBLEMS_H_ */
