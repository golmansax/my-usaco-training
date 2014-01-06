/*
ID: hogao81 
PROG: stamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;

bool IsEqual(multiset<int>& a, multiset<int>& b) {
  // Let's have two iterators to compare values
  multiset<int>::iterator a_it = a.begin();
  multiset<int>::iterator b_it = b.begin();

  while (a_it != a.end() && b_it != b.end()) {
    if (*a_it != *b_it) return false;
    a_it++;
    b_it++;
  }

  return (a_it == a.end()) && (b_it == b.end());
}

void PrintMultiset(multiset<int>& set) {
  for (multiset<int>::iterator it = set.begin(); it != set.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;
}

int GetSum(multiset<int>& set) {
  int sum = 0;
  for (multiset<int>::iterator it = set.begin(); it != set.end(); it++) {
    sum += *it;
  }
  return sum;
}

int main() {
  ofstream fout ("stamps.out");
  ifstream fin ("stamps.in");
  int k, n;
  fin >> k >> n;

  set<int> vals;
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    vals.insert(x);
  }

  // Dynamic programming
  // map of sum -> multisets that can generate it
  map<int, vector<multiset<int> > > generators;

  // Initialize map
  vector<multiset<int> > empty_generators;
  multiset<int> empty_set;
  empty_generators.push_back(empty_set);
  generators[0] = empty_generators;

  int current = 0, ans;
  while(true) {
    if (generators.find(current) == generators.end()) {
      // No value here so let's exit
      ans = current - 1;
      break;
    }

    vector<multiset<int> >& my_generators = generators[current];
    // Iterate through these and try to add vals
    for (vector<multiset<int> >::iterator generators_it = 
           my_generators.begin(); 
         generators_it != my_generators.end(); generators_it++) {

      int sum = GetSum(*generators_it);
      cout << "*** " << sum << " ***" << endl;
      //PrintMultiset(*generators_it);

      // Limit size
      if (generators_it->size() >= k) continue;
      //cout << "  processing" << endl;

      for (set<int>::iterator vals_it = vals.begin();
           vals_it != vals.end(); vals_it++) {

        multiset<int> my_set(*generators_it);
        my_set.insert(*vals_it);
        int my_sum = sum + *vals_it;

        if (generators.find(my_sum) == generators.end()) {
          generators[my_sum].push_back(my_set);
        }
        else {
          vector<multiset<int> >& my_vec = generators[my_sum];
          if (my_set.size() < my_vec[0].size()) {
            vector<multiset<int> > new_vec;
            new_vec.push_back(my_set);
            generators[my_sum] = new_vec;
          }
        }
        /*
        bool add = true;
        // Iterate through the generators to see if it is already in the vec
        for (vector<multiset<int> >::iterator vec_it = my_vec.begin();
             vec_it != my_vec.end(); vec_it++) {
          if (IsEqual(my_set, *vec_it)) {
            add = false;
            break;
          }
        }

        if (add) generators[my_sum].push_back(my_set);
        */
      }
    }

    // Destroy the previous value (we don't need it anymore)
    generators.erase(current);
    current++;
  }

  fout << ans << endl;

  return 0;
}
