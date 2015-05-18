// Brian Goldman

// Implementation of the various local search algorithms used in
// informal testing.

#include "LocalSearch.h"

// Template specialization to allow Configuration to return
// a hill climber function pointer given a string key
template<>
local_search::pointer Configuration::get(const string key) const {
  auto value = get<string>(key);
  auto it = local_search::lookup.find(value);
  if (it == local_search::lookup.end()) {
    throw std::invalid_argument(
        "Cannot find local search method '" + value + "' specified by key '" + key + "'");
  }
  return it->second;
}

// Iteratively tests bits in a random order, accepting improvements as they
// are found.  Tracks bits that have been tested since the last modification
// to prevent waste.
void local_search::first_improvement(Random & rand, vector<int> & solution,
                                   double & fitness, shared_ptr<Problem> problem) {
  // Set up data structure for random bit selection
  vector<int> options(solution.size());
  iota(options.begin(), options.end(), 0);
  double new_fitness;
  bool improvement;
  // keep track of locations already tried since last improvement
  std::unordered_set<int> tried;

  // Keep looping until there is no single bit flip improvement
  do {
    improvement = false;
    // Test the bits in a random order
    std::shuffle(options.begin(), options.end(), rand);
    for (const auto& index : options) {
      // If this location has already been tried, skip to the next one
      if (tried.count(index) != 0) {
        continue;
      }
      vector<int> value_choices(problem->variable_range()[index]);
      iota(value_choices.begin(), value_choices.end(), 0);
      shuffle(value_choices.begin(), value_choices.end(), rand);
      for (const auto & value : value_choices) {
        if (solution[index] == value) {
          continue;
        }
        auto prev = solution[index];
        // flip and evaluate the modification
        solution[index] = value;
        new_fitness = problem->evaluate(solution);
        if (fitness < new_fitness) {
          // Keep change, update variables
          fitness = new_fitness;
          improvement = true;
          tried.clear();
        } else {
          // Revert the change
          solution[index] = prev;
        }
      }
      tried.insert(index);
    }
  } while (improvement);
}
