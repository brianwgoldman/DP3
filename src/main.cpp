#include "Configuration.h"
#include "Util.h"
#include "Problems.h"
#include "SolverCollection.h"
#include "LocalSearch.h"
#include "MonitorLayer.h"
#include <signal.h>

bool volatile signal_received = false;

void signal_receiver(int) {
  signal_received = true;
}


int main(int argc, char * argv[]) {
  Configuration config;
  config.parse(argc, argv);

  // Set up the random number seed either using the configuration value
  // or the computers built in seed generator.
  Random rand;
  int seed = config.get<int>("seed");
  if (seed == -1) {
    std::random_device rd;
    seed = rd();
    config.set("seed", seed);
  }
  // save configuration if you need to do it all again
  config.dump();
  rand.seed(seed);

  signal(SIGINT, signal_receiver);

  auto problem = config.get<problem::pointer>("problem")(config);
  shared_ptr<MonitorLayer> wrapped = shared_ptr<MonitorLayer>(new MonitorLayer(config, problem));
  auto solver_method = config.get<solver::pointer>("solver");
  auto solver = solver_method(rand, std::static_pointer_cast<Problem>(wrapped), config);
  try {
    while (wrapped->time_remaining() and not signal_received) {
      solver->iterate();
    }
  } catch (StopIteration & e) {
    // No handling necessary, just move on to the rest of the program.
  }
  cout << "Clean end" << endl;
  return 0;
}
