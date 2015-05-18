#ifndef PROBLEMS_H_
#define PROBLEMS_H_
#include <unordered_map>
#include <memory>

#include "Util.h"
#include "Configuration.h"


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

namespace problem {
using pointer=std::shared_ptr<Problem> (*)(Configuration &);
static std::unordered_map<string, pointer> lookup = {
    { "ValueMax", ValueMax::create },
};
}

#endif /* PROBLEMS_H_ */
