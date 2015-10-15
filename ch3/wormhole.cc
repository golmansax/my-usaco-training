/*
ID: hogao81
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

void helper(int n, int curr, const vector<int>& mapping,
    const unordered_set<int>& selected, vector<vector<int> >& ans) {

  // try to find a match for curr
  for (int i = curr + 1; i < n; i++) {
    if (selected.count(i)) { continue; }

    vector<int> new_mapping = mapping;
    new_mapping[curr] = i;
    new_mapping[i] = curr;

    unordered_set<int> new_selected = selected;
    new_selected.insert(curr);
    new_selected.insert(i);

    if (new_selected.size() == n) {
      ans.push_back(new_mapping);
    } else {
      for (int j = curr + 1; j < n; j++) {
        if (!new_selected.count(j)) {
          helper(n, j, new_mapping, new_selected, ans);
          break;
        }
      }
    }
  }
}

vector<vector<int> > generate_combs(int n) {
  vector<vector<int> > ans;
  vector<int> start_mapping;
  start_mapping.resize(n);
  unordered_set<int> start_selected;
  helper(n, 0, start_mapping, start_selected, ans);

  return ans;
}

struct tWormhole {
  long long x;
  long long y;
  int index;
};

int main() {
  ofstream fout ("wormhole.out");
  ifstream fin ("wormhole.in");
  int n;
  fin >> n;

  tWormhole wormholes[n];
  unordered_map<long long, vector<tWormhole> > by_y;
  for (int i = 0; i < n; i++) {
    fin >> wormholes[i].x >> wormholes[i].y;
    wormholes[i].index = i;

    vector<tWormhole>& vec = by_y[wormholes[i].y];
    int insert_index = -1;
    for (int j = 0; j < vec.size(); j++) {
      if (vec[j].x > wormholes[i].x) {
        insert_index = j;
        break;
      }
    }

    if (insert_index == -1) {
      vec.push_back(wormholes[i]);
    } else {
      vec.insert(vec.begin() + insert_index, wormholes[i]);
    }
  }
  /*
  for (unordered_map<long long, vector<tWormhole> >::iterator it = by_y.begin(); it != by_y.end(); ++it) {
    vector<tWormhole>& vec = it->second;
    for (int i = 0; i < vec.size(); i++) {
      cout << "X: " << it->first << " and " << vec[i].y << endl;
    }
  }
  */

  int arr[n];
  for (int i = 0; i < n; i++) {
    arr[i] = i;
  }

  vector<vector<int> > choices = generate_combs(n);

  // unordered_set<string> processed;
  // do {
    /*
    bool invalid = false;
    for (int i = 0; i < n; i++) {
      if (arr[i] == i) {
        invalid = true;
        break;
      }
    }
    if (invalid) { continue; }

    string hash = "";
    unordered_set<int> visited;
    for (int i = 0; i < n; i++ ){
      if (visited.count(i)) { continue; }
      int pair = arr[i];

      if (i != arr[pair]) {
        invalid = true;
        break;
      }

      hash += to_string(i) + "-" + to_string(pair) + " ";
      visited.insert(i);
      visited.insert(pair);
    }
    if (invalid) { continue; }
    cout << hash << endl;
  //} while ( std::next_permutation(arr, arr + n) );
  */
  int ans = 0;

  for (int blah = 0; blah < choices.size(); blah++) {
    vector<int>& arr = choices[blah];

    // Now actually do the test
    // Start at each wormhole, and see if we get a loop
    bool found_ans = false;
    for (int i = 0; i < n; i++) {
      unordered_set<int> plunged;
      int me = i;

      bool exit = false;
      while (!exit) {
        if (plunged.count(me)) {
          found_ans = true;
          break;
        }

        plunged.insert(me);
        int next = arr[me];
        vector<tWormhole>& possibles = by_y[wormholes[next].y];

        int following = -1;
        for (int j = 0; j < possibles.size(); j++) {
          if (possibles[j].x > wormholes[next].x) {
            following = possibles[j].index;
            break;
          }
        }

        if (following == -1) {
          exit = true;
        } else {
          me = following;
        }
      }

      if (found_ans) {
        ans++;
        break;
      }
    }
  }

  fout << ans << endl;
  return 0;
}
