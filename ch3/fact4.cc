/*
ID: hogao81
PROG: fact4
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
  ofstream fout ("fact4.out");
  ifstream fin ("fact4.in");
  int a;
  fin >> a;

  long long x = 1;
  int ans;
  for (int i = 2; i < 4230; i++) {
    if (i > a) {
      ans = x % 10;
      break;
    }

    x *= i;
    while (x % 10 == 0) {
      x /= 10;
    }

    x = x % 10000;
  }

  fout << ans << endl;
  return 0;
}
