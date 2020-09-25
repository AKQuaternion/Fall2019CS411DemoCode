#include <memory>
using std::shared_ptr;
using std::unique_ptr;
using std::weak_ptr;
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::getline;
#include <sstream>
using std::istringstream;
using std::string;
using namespace std::literals;
#include <chrono>
#include <cstdio>
#include <fstream>
using std::ifstream;
using std::ofstream;
using std::ostream;
#include <vector>
using std::vector;
#include <algorithm>
#include <functional>
#include <initializer_list>
#include <numeric>
#include <sstream>
using std::istringstream;
#include <stdexcept>
using std::runtime_error;
#include <algorithm>
#include <fstream>
#include <iostream>
using std::iota;
#include <deque>
using std::deque;
#include <stack>
using std::stack;

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream; // for input files (similar to cin)
#include <iomanip>
using std::ios;
using std::istream;
using std::setw;

void printVector(const vector<int> &v) {
  for (auto i : v)
    cout << i << " ";
  cout << endl;
}

void printBits(size_t n,
               size_t number) { // print least significant n bits of number
  for (auto ii = (int)n - 1; ii >= 0; --ii)
    if (1 << ii & number)
      cout << "1";
    else
      cout << "0";
  cout << endl;
}

// prints the numbers of bits set in number
void printSet(size_t n, size_t number) {
  for (auto jj = 0u; jj < n; ++jj)
    if (1 << jj & number)
      cout << jj + 1 << " ";
  cout << endl;
}

void subsets(size_t n) {
  for (auto ii = 0u; ii < 1 << n; ++ii) {
    printBits(n, ii);
    printSet(n, ii);
    cout << endl;
  }
}

void flip(size_t &bits, size_t pos) { bits ^= (1 << pos); }

size_t leastSignificantOnePosition(size_t n) {
  for (auto ii = 0u; ii < 8 * sizeof(n); ++ii)
    if (n & 1 << ii)
      return ii;
  throw runtime_error("leastSignificantOnePosition(0)");
}

void grayCode(size_t n) {
  size_t bits = 0;
  auto ii = 0u;
  while (ii < 1 << n) {
    printBits(n, bits);
    printSet(n, bits);
    cout << endl;
    ++ii;
    flip(bits, leastSignificantOnePosition(ii));
  }
}

void stlPermutations(size_t n) {
  vector<int> v(n);
  iota(begin(v), end(v), 1); // fill with 1 to n

  do
    printVector(v);
  while (next_permutation(begin(v), end(v)));
}

void printSubset(const deque<bool> &comb) {
  for (auto ii = 0u; ii < comb.size(); ++ii)
    if (comb[ii])
      cout << ii + 1 << " ";
  cout << endl;
}

void combinations(size_t n, size_t k) {
  deque<bool> comb(n, false);
  fill(comb.begin(), comb.begin() + (long)k, true);

  do
    printSubset(comb);
  while (prev_permutation(begin(comb), end(comb)));
}

// goes through every possibility for true/false
// for positions n through v.size()-1 of v
void recursiveSubsets(int n, deque<bool> &v) {
  if (n == v.size()) { //base case, nothing to try
    printSubset(v);
    return;
  }
  v[n] = false;// put false in position n,
  recursiveSubsets(n + 1, v); // go through possibilities for positions n+1 on
  v[n] = true; // put true in position n
  recursiveSubsets(n + 1, v); // go through possibilities for positions n+1 on
}

int other() {

}

int main() {
//  deque<bool> d(5);
//  recursiveSubsets(0, d);
  subsets(5);
  //  grayCode(5);
  //  stlPermutations(5);
  //  combinations(5,3);  //  vector<int> v{1,2,2,3};
  //  do
  //    printVector(v);
  //  while(next_permutation(begin(v),end(v)));
  return 0;
}