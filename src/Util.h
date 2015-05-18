// Brian Goldman

// This is a collection of utilities used throughout programming.
// Basically just a bunch of misfits.

#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <algorithm>
#include <exception>


using std::vector;
using std::ifstream;
using std::ofstream;
using std::ostream;
using std::cout;
using std::endl;

// Defines that the random number generator in use is the Mersenne Twister
using Random=std::mt19937;

vector<int> random_vector(Random & rand, const vector<int>& variable_range);

void print(const vector<int>& solution, ostream & out=cout);


// Returns the entropy given the list of counts and a total number,
// where total = sum(counts)
template<class ForwardIt>
double entropy(const ForwardIt& begin, const ForwardIt & end, const double& total) {
  double sum = 0;
  double p;
  for (auto it=begin; it != end; it++) {
    if (*it) {
      p = (*it) / total;
      sum -= (p * log(p));
    }
  }
  return sum;
}

class StopIteration : public std::exception {
 public:
  virtual char const * what() const noexcept{
    return "An algorithm has hit a termination condition";
  }
};

void throwStop(int dummy=0);

#endif /* UTIL_H_ */
