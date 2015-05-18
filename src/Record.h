// Brian Goldman

// A record stores the result information for a single optimization run,
// recording how many evaluations are required to reach each new fitness level

#ifndef RECORD_H_
#define RECORD_H_

#include <vector>

#include "Util.h"
#include "Configuration.h"

class RecordEntry {
 public:
  int evaluations;
  double seconds;
  double fitness;
  vector<int> solution;

  RecordEntry(int evals = 0, double sec = 0, double fit = 0,
              const vector<int>& _solution = vector<int>())
      : evaluations(evals),
        seconds(sec),
        fitness(fit),
        solution(_solution) {
  }
};

// Stores optimization history information
class Record {
 public:
  Record(Configuration& config)
      : verbosity(config.get<int>("verbosity")) {
  }
  virtual ~Record() = default;
  // Tracks increases in fitness.  If verbosity is set high enough, outputs
  // information to the screen.
  void add(int evals, double seconds, double fitness, const vector<int>& solution);
  // The best fitness achieved in this optimization run
  const RecordEntry& best() const {
    return levels.back();
  }
  // access to the stored values:
  const vector<RecordEntry>& progression() const {
    return levels;
  }

  bool empty() const {
    return levels.size() == 0;
  }
  string metadata;
 private:
  // Raw stored data
  vector<RecordEntry> levels;
  int verbosity;
};

#endif /* RECORD_H_ */
