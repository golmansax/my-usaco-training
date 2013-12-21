/*
ID: hogao81
PROG: concom
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
  ofstream fout ("concom.out");
  ifstream fin ("concom.in");

  int n_triple;
  fin >> n_triple;

#define N 101

  int own[N][N], control[N][N];
  memset (own, 0, sizeof(int)*N*N);
  memset (control, 0, sizeof(int)*N*N);

  for (int i = 0; i < n_triple; i++) {
    int a, b, percent;
    fin >> a >> b >> percent;
    own[a][b] = percent;
  }

  // initial pass
  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++) {
      if (own[i][j] > 50) control[i][j] = 1;
    }
  for (int i = 1; i < N; i++) control[i][i] = 1;

  int changed = 1;
  while (changed) {
    changed = 0;
    for (int i = 1; i < N; i++) {
      for (int j = 1; j < N; j++) {
        if (control[i][j]) continue;
        int sum = 0;
        for (int k = 1; k < N; k++) {
          if (control[i][k]) sum += own[k][j];
        }
        if (sum > 50) {
          control[i][j] = 1;
          changed = 1;
        }
      }
    }
  }

  for (int i = 1; i < N; i++)
    for (int j = 1; j < N; j++)
      if (control[i][j] && i != j) fout << i << " " << j << endl;

  return 0;
}
