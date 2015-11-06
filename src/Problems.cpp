
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
  string token;
  while (input >> token) {
    auto multiply_index = token.find('*');
    // Does not contain a *
    if (token.size() < multiply_index) {
      value_range.push_back(stoi(token));
    } else {
      int repeats = stoi(token.substr(0, multiply_index));
      int value = stoi(token.substr(multiply_index + 1));
      value_range.resize(value_range.size() + repeats, value);
    }
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

DeceptiveTrap::DeceptiveTrap(Configuration& config) {
  construct_range(config);
  maximum_fitness = 0;
  for (const auto value : value_range) {
    maximum_fitness += value - 1;
  }
}

double DeceptiveTrap::evaluate(const vector<int> & solution) {
  int result = 0;
  for (size_t i=0; i < solution.size(); i++) {

    int trapped = solution[i];
    // if not the maximum value
    if (trapped != value_range[i] - 1) {
      trapped = (value_range[i] - 1) - trapped - 1;
    }
    result += trapped;
  }
  return static_cast<double>(result) / maximum_fitness;
}

PairsEqual::PairsEqual(Configuration& config) {
  construct_range(config);
  maximum_fitness = 0;
  for (const auto value : value_range) {
    maximum_fitness += value - 1;
  }
}

double PairsEqual::evaluate(const vector<int> & solution) {
  int result = 0;
  for (size_t i=0; i < solution.size() - 1; i+= 2) {
    if (solution[i] == solution[i + 1]) {
      result += 2 * solution[i];
    }
  }
  return result;
  //return static_cast<double>(result) / maximum_fitness;
}

double Rastrigin::evaluate(const vector<int> & solution) {
  double total = 0;
  for (size_t i=0; i < solution.size(); i++) {
    double fraction = static_cast<double>(solution[i]) / (value_range[i] - 1);
    double x = 10.24 * fraction - 5.12;
    total += 10 + x * x - 10 * cos(2 * M_PI * x);
  }
  return -total;
}

HIFF::HIFF(Configuration& config) {
  construct_range(config);
}

double HIFF::evaluate(const vector<int> & solution) {
  // Data structure used to represent values as 0, 1, or -1 (Null)
  int * level = new int[solution.size()];
  int level_length = solution.size();

  // Initialize the level to the current solution
  for (size_t i = 0; i < solution.size(); i++) {
    level[i] = solution[i];
  }
  int power = 1;
  int next_length = level_length >> 1;
  int total = 0;
  int maximum = 0;

  // Keep going while the next level actual has bits in it
  while (next_length > 0) {
    int * next_level = new int[next_length];
    // Construct the next level using the current level
    for (int i = 0; i + 1 < level_length; i += 2) {
      if (level[i] == level[i + 1] and level[i] != -1) {
        // Score points for a correct setting at this level
        total += power;
        next_level[i >> 1] = level[i];
      } else {
        next_level[i >> 1] = -1;
      }
      // Keep track of the maximum possible score
      maximum += power;
    }
    delete[] level;
    level = next_level;
    level_length = next_length;
    next_length = level_length >> 1;
    power <<= 1;
  }
  delete[] level;

  // Convert to percentage of total
  return static_cast<double>(total) / maximum;
}
