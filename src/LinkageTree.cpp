/*
 * LinkageTree.cpp
 *
 *  Created on: Nov 3, 2015
 *      Author: goldman
 */

#include "LinkageTree.h"

double PairFrequency::distance(const double total) {
  // Consider making these static
  auto together = map_entropy(pairings.begin(), pairings.end(), total);
  auto first_entropy = map_entropy(first_counts.begin(), first_counts.end(), total);
  auto second_entropy = map_entropy(second_counts.begin(), second_counts.end(), total);
  if (together == 0) {
    return 0;
  }
  return 2 - ((first_entropy + second_entropy) / together);
}

LinkageTree::LinkageTree(Random& _rand, size_t _length) : rand(_rand), length(_length) {
  added = 0;
  rebuild_required = true;
  // create a triangular matrix
  occurrences.resize(length);
  for (size_t i = 1; i < length; i++) {
    occurrences[i].resize(i);
  }
}

void LinkageTree::add(const vector<int> & solution) {
  for (size_t i = 1; i < length; i++) {
    for (size_t j = 0; j < i; j++) {
      occurrences[i][j].add(solution[i], solution[j]);
    }
  }
  added ++;
  rebuild_required = true;
}

void LinkageTree::rebuild() {
  // Should allocate exactly one copy of this memory regardless of how many trees exist or
  // how many function calls are made
  static vector<vector<double>> distances(2 * length - 1, vector<double>(2 * length - 1));
  for (size_t i = 1; i < length; i++) {
    for (size_t j = 0; j < i; j++) {
      // TODO Verify this change broke nothing
      distances[i][j] = occurrences[i][j].distance(added);
      // make it symmetric
      distances[j][i] = distances[i][j];
    }
  }

  // Initially all single bit clusters are top level
  vector<int> top_level(length);
  iota(top_level.begin(), top_level.end(), 0);
  clusters.resize(2 * length - 1);
  for (size_t i=0; i < length; i++) {
    clusters[i].resize(1);
    clusters[i][0] = i;
  }
  vector<bool> useful(2 * length - 1, true);
  // Each iteration we add some amount to the path, and remove the last
  // two elements.  This keeps track of how much of usable is in the path.
  size_t end_of_path = 0;
  // build all clusters of size greater than 1
  for (size_t index = length; index < clusters.size(); index++) {
    advance_path(top_level, end_of_path, distances);
    // Last two elements in the path are the clusters to join
    int first = top_level[end_of_path - 2];
    int second = top_level[end_of_path - 1];
    // Only keep a cluster if the distance between the joining clusters is > zero
    bool keep = distances[first][second] > 0;
    useful[first] = keep;
    useful[second] = keep;
    // create the new cluster
    clusters[index] = clusters[first];
    // merge the two clusters
    clusters[index].insert(clusters[index].end(), clusters[second].begin(),
                           clusters[second].end());

    // Calculate distances from all clusters to the newly created cluster
    int i = 0;
    int end = top_level.size() - 1;
    while (i <= end) {
      int x = top_level[i];
      // Moves 'first' and 'second' to after "end" in top_level
      if (x == first or x == second) {
        std::swap(top_level[i], top_level[end]);
        end--;
        continue;
      }
      // Use the previous distances to calculate the joined distance
      double first_distance = distances[first][x];
      first_distance *= clusters[first].size();
      double second_distance = distances[second][x];
      second_distance *= clusters[second].size();
      distances[x][index] = ((first_distance + second_distance)
          / (clusters[first].size() + clusters[second].size()));
      // make it symmetric
      distances[index][x] = distances[x][index];
      i++;
    }
    // Remove first and second from the path
    end_of_path -= 2;
    top_level.pop_back();
    top_level.back() = index;
  }
  order_clusters(useful);
  rebuild_required = false;
}

void LinkageTree::advance_path(vector<int>& top_level, size_t & end_of_path, const vector<vector<double>> & distances) {
  // Shuffle everything not yet in the path
  shuffle(top_level.begin() + end_of_path, top_level.end(), rand);
  // if nothing in the path, just add a random usable node
  if (end_of_path == 0) {
    end_of_path = 1;
  }
  while (end_of_path < top_level.size()) {
    // last node in the path
    int final = top_level[end_of_path - 1];
    // best_index stores the location of the best thing in the top level
    int best_index = end_of_path;
    double min_dist = distances[final][top_level[best_index]];
    // check all options which might be closer to "final" than "top_level[best_index]"
    for (size_t option = end_of_path + 1; option < top_level.size(); option++) {
      if (distances[final][top_level[option]] < min_dist) {
        min_dist = distances[final][top_level[option]];
        best_index = option;
      }
    }
    // If the current last two in the path are minimally distant
    if (end_of_path > 1 and min_dist >= distances[final][top_level[end_of_path - 2]]) {
      break;
    }
    // move the best to the end of the path
    std::swap(top_level[end_of_path], top_level[best_index]);
    end_of_path++;
  }
}

void LinkageTree::order_clusters(const vector<bool> & useful) {
  vector<vector<vector<int>>> bins(length + 1);
  size_t count=0;
  for (size_t i=0; i < clusters.size(); i++) {
    if (not useful[i]) {
      continue;
    }
    // efficient way to move cluster into the bin
    bins[clusters[i].size()].emplace_back(0);
    swap(clusters[i], bins[clusters[i].size()].back());
    count++;
  }
  clusters.clear();
  for (auto & bin : bins) {
    shuffle(bin.begin(), bin.end(), rand);
    for (auto & cluster : bin) {
      // efficient way to move cluster out of the bin
      clusters.emplace_back(0);
      swap(cluster, clusters.back());
    }
  }
}

const vector<vector<int>>& LinkageTree::get_clusters() {
  if (rebuild_required) {
    rebuild();
  }
  return clusters;
}
