/*
ID: hogao81
PROG: stamps
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <set>
#include <vector>
#include <map>

using namespace std;

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

  // Copy set to an array
  int n_vals = vals.size();
  int arr[n_vals];
  int arr_i = 0;
  for (set<int>::iterator vals_it = vals.begin();
       vals_it != vals.end(); vals_it++, arr_i++) {
    arr[arr_i] = *vals_it;
  }

  // Dynamic programming
  #define MAX 10001

  // Only need to keep track of possible size of set
  int possible_sizes[MAX];
  memset(possible_sizes, 0, sizeof(int) * MAX);

  int current = 0, ans = 0;
  while(true) {
    int my_size = possible_sizes[current];

    if (current != 0 && my_size == 0) {
      // No value here so let's exit
      ans--;
      break;
    }

    // Limit size
    if (my_size >= k) goto end;

    for (int i = 0; i < n_vals; i++) {
      int my_val = arr[i];
      int next = (current + my_val) % MAX;
      int to_compare = possible_sizes[next];

      if (to_compare == 0 || my_size + 1 < to_compare) {
        possible_sizes[next] = my_size + 1;
      }
    }

   end:
    // Destroy the previous value (we don't need it anymore)
    possible_sizes[current] = 0;
    ans++;
    current = (current + 1) % MAX;
  }

  fout << ans << endl;

  return 0;
}
