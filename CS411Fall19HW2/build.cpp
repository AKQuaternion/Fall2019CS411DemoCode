//
// Created by Chris Hartman on 9/30/19.
//
#include "build.h"
using std::vector;
#include <algorithm>
using std::max;
#include <numeric>
using std::accumulate;
#include <iterator>
using std::begin;
using std::end;

bool crosses(const Bridge &a, const Bridge &b) {
  return (a[0] <= b[0] && a[1] >= b[1]) || (a[0] >= b[0] && a[1] <= b[1]);
}

bool noCrossings(const vector<Bridge> &bridges) {
  for (size_t i = 0; i < bridges.size(); ++i)
    for (auto j = i + 1; j < bridges.size(); ++j)
      if (crosses(bridges[i], bridges[j]))
        return false;
  return true;
}

int sumOfTolls(const vector<Bridge> &bridges) {
  return accumulate(begin(bridges), end(bridges), 0,
                    [](int sum, const Bridge &b) { return sum + b[2]; });
}

int build(int, int, const vector<Bridge> &bridges) {
  int maxToll = 0;
  unsigned int twoToTheSize = 1u << bridges.size();
  for (unsigned int subset = 0; subset < twoToTheSize; ++subset) {
    vector<Bridge> theseBridges;
    for (size_t bitIndex = 0; bitIndex < bridges.size(); ++bitIndex)
      if (subset & 1u << bitIndex)
        theseBridges.push_back(bridges[bitIndex]);
    if (noCrossings(theseBridges))
      maxToll = max(maxToll, sumOfTolls(theseBridges));
  }

  return maxToll;
}
