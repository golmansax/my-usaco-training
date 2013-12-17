/*
ID: hogao81
PROG: inflate
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

struct tCat {
  long long val;
  int time;
};
bool my_cmp(tCat a, tCat b) {
  return a.time < b.time;
}

int main() {
  ofstream fout("inflate.out");
  ifstream fin("inflate.in");
  int m, n;
  fin >> m >> n;

  // simple dyn programming
  long long dyn[m + 1];
  memset(dyn, 0, sizeof(long long) * (m + 1));

  tCat cats[n];
  // lets defaults for dyn
  for (int i = 0; i < n; i++) {
    fin >> cats[i].val >> cats[i].time;
    if (cats[i].time > m || (dyn[cats[i].time] != 0 && dyn[cats[i].time] > cats[i].val)) {
      n--; i--;
    }
    dyn[cats[i].time] = cats[i].val;
  }
  sort(cats, cats + n, my_cmp);

  long long max = 0;
  for (int i = 1; i <= m; i++) {
    if (dyn[i] == 0) continue;
    //cout << i << ": " << dyn[i] << endl;
    if (dyn[i] > max) max = dyn[i];

    for (int j = 0; j < n; j++) {
      if (i + cats[j].time <= m) {// && dyn[i + cats[j].time] < dyn[i] + val[j])
        long long tmp = dyn[i] + cats[j].val;
        dyn[i + cats[j].time] = MAX(dyn[i + cats[j].time], tmp);
      }
      else break;
    }
  }
  fout << max << endl;

  return 0;
}
