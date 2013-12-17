/*
ID: hogao81 
PROG: comehome
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>

using namespace std;

int main() {
  map<char, int> c2i;
  char i2c[52];

  for (int i = 0; i < 26; i++) {
    c2i[(char)(i + 'A')] = i;
    i2c[i] = (char)(i + 'A');
    c2i[(char)(i + 'a')] = i + 26;
    i2c[i + 26] = (char)(i + 'a');
  }


  ofstream fout ("comehome.out");
  ifstream fin ("comehome.in");

  int n_p;
  fin >> n_p;

#define N 52
#define INF 100000000
#define MIN(X, Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X, Y) ((X) > (Y) ? (X) : (Y))

  int adj[N][N];

  for (int i = 0; i < N; i++) for (int j = 0; j < N; j++)
    adj[i][j] = INF;

  for (int i = 0; i < n_p; i++) {
    char here, dest;
    int dist;
    fin >> here >> dest >> dist;
    if (here == dest) continue;
    int idx1 = c2i[here], idx2 = c2i[dest];

    adj[idx1][idx2] = MIN(adj[idx1][idx2], dist);
    adj[idx2][idx1] = adj[idx1][idx2];
  }

  // floyd warshall
  for (int k = 0; k < N; k++) for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) {
    if (i != j) adj[i][j] = MIN(adj[i][j], adj[i][k] + adj[k][j]);
  }

  /*
  for (int i = 0; i < N; i++) {
    printf("%c: ", i + 'A');
    for (int j = 0; j < N; j++) printf("%d ", adj[i][j] == INF ? 0 : adj[i][j]);
    printf("\n");
  }
*/
  int ans_idx, ans_dist = INF;
  for (int i = 0; i < 25; i++)
    if (ans_dist > adj[i][25]) {
      ans_dist = adj[i][25];
      ans_idx = i;
    }

  fout << i2c[ans_idx] << " " << ans_dist << endl;

  return 0;
}
