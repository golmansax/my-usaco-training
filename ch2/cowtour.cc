/*
ID: hogao81 
PROG: cowtour
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <iomanip>
#include <cstring>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))
#define SQR(X) ((X) * (X))
#define INF 1000000000

using namespace std;

double dist(double pt1[2], double pt2[2]) {
  return sqrt(SQR(pt1[0] - pt2[0]) + SQR(pt1[1] - pt2[1]));
}

int main() {
  ofstream fout ("cowtour.out");
  ifstream fin ("cowtour.in");

  int n;
  fin >> n;

  double pt[n][2];
  for (int i = 0; i < n; i++) fin >> pt[i][0] >> pt[i][1];

  double adj[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      char c;
      fin >> c;
      //printf ("%c", c);
      if (c == '1') adj[i][j] = dist(pt[i], pt[j]);
      else adj[i][j] = INF;
    }
    //printf ("\n");
  }

/*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++)
      if (i == 104) printf("%.2f\n", i, adj[i][j]);
  }*/

  // floyd warshall
  for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    if (i != j) adj[i][j] = MIN(adj[i][j], adj[i][k] + adj[k][j]);

  for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
    if (adj[i][j] == INF) adj[i][j] = 0;

/*
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) printf("%.2f ", adj[i][j]);
    printf("\n");
  }*/
  
  double max_adj[n];
  double ans_no = 0;
  for (int i = 0; i < n; i++) {
    max_adj[i] = 0;
    for (int j = 0; j < n; j++) {
      max_adj[i] = MAX(max_adj[i], adj[i][j]);
    }
    ans_no = MAX(ans_no, max_adj[i]);
    //printf("%03d %.2f\n", i, max_adj[i]);
  }

  // figure out partitions
  //set<int> visited;
  //visited.clear();
  double ans_add = INF;
  for (int i = 0; i < n; i++) {
    //if (visited.count(i)) continue;
    //visited.insert(i);
    for (int j = 0; j < n; j++) {
      if (!adj[i][j] && i != j) {
        double cmp = max_adj[i] + max_adj[j] + dist(pt[i], pt[j]);
        ans_add = MIN(ans_add, cmp);
      }
    }
  }
  
  double ans = MAX(ans_no, ans_add);

  char ans_str[10000];
  sprintf(ans_str, "%.6f", ans);
  fout << ans_str << endl;

  return 0;
}
