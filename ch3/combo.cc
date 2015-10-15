/*
ID: hogao81
PROG: combo
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <set>

using namespace std;

int mod(int x, int n) {
  return (x + n) % n;
}

int main() {
  ofstream fout ("combo.out");
  ifstream fin ("combo.in");

  long long n;
  fin >> n;
  set<long long> solutions;

  for (int i = 0; i < 2; i++) {
    int x, y, z;
    fin >> x >> y >> z;
    x--;
    y--;
    z--;

    for (int x_c = -2; x_c <= 2; x_c++) {
      int x_t = mod(x + x_c, n);
      for (int y_c = -2; y_c <= 2; y_c++) {
        int y_t = mod(y + y_c, n);
        for (int z_c = -2; z_c <= 2; z_c++) {
          int z_t = mod(z + z_c, n);
          // cout << x_t << " " << y_t << " " << z_t << endl;

          long long solution = x_t + n * y_t + n * n * z_t;
          solutions.insert(solution);
        }
      }
    }
  }

  fout << solutions.size() << endl;
  return 0;
}
