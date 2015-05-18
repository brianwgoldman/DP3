// Brian Goldman

// Defines the base class all optimization methods should inherit from.
// Provides tools for setting up configurable selection of optimization method.

#ifndef SOLVER_H_
#define SOLVER_H_

#include <memory>

#include "Util.h"
#include "Problems.h"
#include "Configuration.h"

using std::shared_ptr;

// Macro used to create a function which returns new instances of the desired optimization method.
#define create_solver(name)\
static shared_ptr<Solver> create(Random& rand, shared_ptr<Problem> problem, Configuration& config){\
	return shared_ptr<Solver>(new name(rand, problem, config));\
}

// Base class for optimization methods
class Solver {
 public:
  Solver(Random& _rand, shared_ptr<Problem> _problem,
            Configuration& _config)
      : rand(_rand),
        problem(_problem),
        config(_config) {
  }
  virtual ~Solver() = default;
  // External tools interact with the optimizer by telling it to "iterate",
  // and the optimizer will return true as long as it can continue to improve by iterating.
  // As example, an iteration may perform a generation of evolution, with the optimizer returning
  // false when convergence is detected.
  virtual bool iterate() = 0;

  virtual string metadata() {
    return string();
  }

 protected:
  // Tools useful to the actual optimization methods.
  Random& rand;
  shared_ptr<Problem> problem;
  Configuration& config;
};

#endif /* SOLVER_H_ */
