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


// Returns the entropy given the map's values a total number,
// where total = sum(counts)
template<class ForwardIt>
inline double map_entropy(const ForwardIt& begin, const ForwardIt & end, const double total) {
  double sum = 0;
  double p;
  for (auto it=begin; it != end; it++) {
    p = it->second / total;
    sum -= (p * log(p));
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


// This is taken from Boost to allow for hashing of pairs
template <class T>
inline void hash_combine(std::size_t & seed, const T & v) {
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

namespace std {
  template<typename S, typename T> struct hash<pair<S, T>> {
    inline size_t operator()(const pair<S, T> & v) const {
      size_t seed = 0;
      hash_combine(seed, v.first);
      hash_combine(seed, v.second);
      return seed;
    }
  };

  template<typename T> struct hash<vector<T>> {
    inline size_t operator()(const vector<T> & v) const {
      size_t seed = 0;
      for (const auto & elem : v) {
        hash_combine(seed, elem);
      }
      return seed;
    }
  };
}
#endif /* UTIL_H_ */
