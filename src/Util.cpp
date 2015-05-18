// Brian Goldman

// Collection of utilities not better suited for placement
// in other files

#include "Util.h"

vector<int> random_vector(Random & rand, const vector<int>& variable_range) {
  vector<int> result(variable_range.size());
  for (size_t i=0; i < variable_range.size(); i++) {
    std::uniform_int_distribution<int> dist(0, variable_range[i] - 1);
    result[i] = dist(rand);
  }
  return result;
}

void print(const vector<int>& solution, ostream & out) {
  for (const auto & value : solution) {
    out << value << " ";
  }
  out << endl;
}

void throwStop(int dummy) {
   throw StopIteration();
}
