/*
ID: hogao81
PROG: skidesign
LANG: C++11
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main() {
  ofstream fout ("skidesign.out");
  ifstream fin ("skidesign.in");
  int n;
  vector<int> heights;
  fin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    fin >> x;
    heights.push_back(x);
  }

  sort(heights.begin(), heights.end());

  int ans = -1;
  for (int i = 0; i <= 100 - 17; i++) {
    int my_ans = 0;

    for (int j = 0; j < n; j++) {
      if (heights[j] < i) {
        my_ans += (i - heights[j]) * (i - heights[j]);
      } else if (heights[j] > i + 17) {
        my_ans += (heights[j] - (i + 17)) * (heights[j] - (i + 17));
      }
    }

    if (ans == -1 || my_ans < ans) {
      cout << "CHANGE for " << i << endl;
      ans = my_ans;
    }
  }

  fout << ans << endl;

  return 0;
}
