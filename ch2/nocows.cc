/*
ID: hogao81
PROG: nocows
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

int main() {
  ofstream fout ("nocows.out");
  ifstream fin ("nocows.in");

  int n, k;
  fin >> n >> k;

  if (n % 2 == 0) {
    fout << 0 << endl;
    return 0;
  }

  long long ans[n/2+1][k+1];
  memset (ans, 0, sizeof(long long)*(n/2+1)*(k+1));
  ans[0][1] = 1;
  
  for (int i = 1; i < n/2+1; i++) {
    for (int cow = 0; cow <= (i-1)/2; cow++) {
      // cow in 1 tree, i-1 - cow in other tree
      for (int j = 1; j < k; j++) {
        if (cow*2 == i-1) {
          long long sum = 0;
          for (int l = 0; l < j; l++) {
            sum += ans[cow][l];
          }
          long long add = ans[cow][j]*sum*2;
          add += ans[cow][j]*ans[cow][j];
          ans[i][j+1] += add;
          ans[i][j+1] %= 9901;
        } else {
          long long sum1 = 0;
          long long sum2 = 0;
          for (int l = 0; l < j; l++) {
            sum1 += ans[cow][l];
            sum2 += ans[i-1-cow][l];
          }
          long long add = ans[cow][j]*sum2 + ans[i-1-cow][j]*sum1;
          add += ans[cow][j]*ans[i-1-cow][j];
          ans[i][j+1] += 2*add;
          ans[i][j+1] %= 9901;
        }
      }
    }
  }
  /*
  for (int i = 0; i < n/2+1; i++) {
    for (int j = 0; j <= k; j++) cout << ans[i][j] << " ";
    cout << endl;
  }*/
  fout << ans[n/2][k] % 9901 << endl;

  return 0;
}
