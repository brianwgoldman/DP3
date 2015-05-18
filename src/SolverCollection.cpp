// Brian Goldman

// Configurable optimization methods

#include "SolverCollection.h"

// Template specialization allowing strings to be converted
// directly to the functions which create solver objects.
template<>
solver::pointer Configuration::get(const string key) const {
  auto value = get<string>(key);
  auto it = solver::lookup.find(value);
  if (it == solver::lookup.end()) {
    throw std::invalid_argument(
        "Cannot find solver '" + value + "' specified by key '" + key + "'");
  }
  return it->second;
}

