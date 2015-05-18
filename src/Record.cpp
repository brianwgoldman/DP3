// Brian Goldman

// Data storage of over time optimization progress

#include "Record.h"

// Records that a new fitness level was reached after 'evals' number
// of evaluations.  Outputs information to the screen if verbosity
// is high enough
void Record::add(int evals, double seconds, double fitness, const vector<int>& solution) {
  if (verbosity > 0) {
    cout << fitness << "\t" << evals << "\t" << seconds;
    if (verbosity > 1) {
      cout << "\t";
      print(solution);
    } else {
      cout << endl;
    }
  }

  levels.emplace_back(evals, seconds, fitness, solution);
}
