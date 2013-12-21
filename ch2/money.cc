/*
ID: hogao81
PROG: money
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
  ofstream fout ("money.out");
  ifstream fin ("money.in");

  int v, n;
  fin >> v >> n;

  long long coin[v];
  for (int i = 0; i < v; i++) fin >> coin[i];

  long long ans[n+1], ans2[n+1];
  memset (ans, 0, (n+1)*sizeof(long long));
  memset (ans2, 0, (n+1)*sizeof(long long));

  ans[0] = 1;
  ans2[0] = 1;
  for (int j = 0; j < v; j++) {
    for (int i = 0; i < n+1; i++) {
      if (ans[i]) {
        for (int k = coin[j]; k < n+1; k+= coin[j]) {
          if (i + k <= n) {
            ans2[i + k] += ans[i];
          }
        }
      }
    }
    memcpy (ans, ans2, (n+1)*sizeof(long long));
    //for (int i = 0; i < n+1; i++) cout << coin[j] << " " << ans[i] << endl;
  }
  //for (int i = 0; i < n+1; i++) cout << ans[i] << endl;
  fout << ans[n] << endl;

  return 0;
}
