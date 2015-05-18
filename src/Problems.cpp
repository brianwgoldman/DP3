
#include "Problems.h"

// Template specialization to convert a string to a function pointer
// Used to allow configurable problem choice
template<>
problem::pointer Configuration::get(const string key) const {
  auto value = get<string>(key);
  auto it = problem::lookup.find(value);
  if (it == problem::lookup.end()) {
    throw std::invalid_argument(
        "Cannot find problem '" + value + "' specified by key '" + key + "'");
  }
  return it->second;
}


void Problem::construct_range(Configuration & config) {
  ifstream input(config.get<string>("range_file"));
  int value;
  while (input >> value) {
    value_range.push_back(value);
  }
}

ValueMax::ValueMax(Configuration& config) {
  construct_range(config);
  maximum_fitness = 0;
  for (const auto value : value_range) {
    maximum_fitness += value - 1;
  }
}


double ValueMax::evaluate(const vector<int> & solution) {
  int result = 0;
  for (const auto & value : solution) {
    result += value;
  }
  return static_cast<double>(result) / maximum_fitness;
}
