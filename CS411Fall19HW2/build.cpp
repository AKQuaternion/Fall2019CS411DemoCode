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

int buildRec(int nextBridge, vector<Bridge> &bridgesSoFar, int tollSoFar,
             const vector<Bridge> &bridges) {
  if (nextBridge == bridges.size())
    return tollSoFar;

  int without = buildRec(nextBridge + 1, bridgesSoFar, tollSoFar, bridges);
  for (const auto &b : bridgesSoFar)
    if (crosses(b, bridges[nextBridge]))
      return without;

  bridgesSoFar.push_back(bridges[nextBridge]);
  int with = buildRec(nextBridge + 1, bridgesSoFar,
                      tollSoFar + bridges[nextBridge][2], bridges);
  bridgesSoFar.pop_back();
  return max(without, with);
}

bool crosses(int i, vector<int> s, const vector<Bridge> &bridges) {
  for (auto b : s)
    if (crosses(bridges[i], bridges[b]))
      return true;
  return false;
}
#include <memory>
using std::make_unique;

int backtrackNonrecursive(const vector<Bridge> &bridges) {
  int maxToll = 0;
  int curToll = 0;

  int i = 0;
  vector<int> s;

  while (true) {
    while (i < bridges.size()) {
      if (s.empty() || (bridges[i][0] > bridges[s.back()][0] &&
                        bridges[i][1] > bridges[s.back()][1])) {
        curToll += bridges[i][2];
        s.push_back(i);
      }
      ++i;
    }

    maxToll = max(maxToll, curToll);

    if (s.empty())
      return maxToll;

    i = s.back();
    curToll -= bridges[i][2];
    s.pop_back();
    ++i;
  }
}

#include <algorithm>
using std::sort;
using std::unique;
#include <tuple>
using std::forward_as_tuple;

int build(int, int, const vector<Bridge> &bridges) {
  vector<Bridge> sortedBridges(bridges);
  std::sort(begin(sortedBridges), end(sortedBridges),
            [](const auto &x, const auto &y) {
              return forward_as_tuple(x[0], x[1], y[2]) <
                     forward_as_tuple(y[0], y[1], x[2]);
            });
  std::unique(begin(sortedBridges), end(sortedBridges));
  return backtrackNonrecursive(sortedBridges);
  //  vector<Bridge> tries;
  //  return buildRec(0,tries,0,bridges);
  int maxToll = 0;
  auto twoToTheSize = 1u << bridges.size();
  vector<Bridge> theseBridges;
  theseBridges.reserve(bridges.size());

  for (auto subset = 0u; subset < twoToTheSize; ++subset) {
    theseBridges.clear();
    for (size_t bitIndex = 0; bitIndex < bridges.size(); ++bitIndex)
      if (subset & 1u << bitIndex)
        theseBridges.push_back(bridges[bitIndex]);
    if (noCrossings(theseBridges))
      maxToll = max(maxToll, sumOfTolls(theseBridges));
  }

  return maxToll;
}
