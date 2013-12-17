/*
ID: hogao81 
PROG: agrinet
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

int main() {
  ofstream fout ("agrinet.out");
  ifstream fin ("agrinet.in");

  int n;
  fin >> n;

  int weight[n][n];
  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) fin >> weight[i][j];

  int dist[n];
#define MAX_DIST 2000000
  bool intree[n];
  int source[n];
  for (int i = 0; i < n; i++) {
    dist[i] = MAX_DIST;
    intree[i] = false;
    source[i] = -1;
  }

  int sz = 1, ans = 0;
  intree[0] = true;

  for (int j = 0; j < n; j++)
    if (weight[0][j]) {
      dist[j] = weight[0][j];
      source[j] = 0;
    }

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
  while (sz < n) {
    int min_val = MAX_DIST, min_idx = -1;
    for (int j = 0; j < n; j++)
      if (!intree[j] && dist[j] < min_val) {
        min_val = dist[j];
        min_idx = j;
      }
    
    assert(dist[min_idx] != MAX_DIST);

    sz++;
    ans += dist[min_idx];
    intree[min_idx] = true;

    for (int j = 0; j < n; j++)
      if (weight[min_idx][j] && weight[min_idx][j] < dist[j]) {
        dist[j] = weight[min_idx][j];
        source[j] = min_idx;
      }
  }

  fout << ans << endl;
  
  return 0;
}
