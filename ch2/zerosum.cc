/*
ID: hogao81
PROG: zerosum
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

long long pow (int x, int n) {
  long long ans = 1;
  for (int i = 0; i < n; i++) ans *= x;
  return ans;
}

int main() {
  ofstream fout ("zerosum.out");
  ifstream fin ("zerosum.in");

  int n;
  fin >> n;

  long long end = pow (3, n-1);
  short sign[n-1]; 
  // 0 - 'sp'
  // 1 - '+'
  // 2 - '-'

  for (long long i = 0; i < end; i++) {
    long long tmp_i = i;
    for (int j = n-2; j >= 0; j--) {
      sign[j] = (short) (tmp_i % 3);
      tmp_i /= 3;
    }

    long long cur = 0;
    long long next = 1;
    int idx = 1;
    int prev_op = 1; // previous is an add
    while (idx < n) {
      switch (sign[idx-1]) {
        case 0:
          next = next * 10 + (idx+1);
          break;
        case 1:
          cur += next * prev_op;
          prev_op = 1;
          next = (idx+1);
          break;
        case 2:
          cur += next * prev_op;
          prev_op = -1;
          next = (idx+1);
        default:
          break;
      }
      idx++;
    }
    cur = cur + next * prev_op;

    if (cur == 0) {
      //printf ("Here! %lld\n", cur);
      for (int j = 0; j < n; j++) {
        fout << (j+1);
        if (j != n-1) 
          switch (sign[j]) {
            case 0: fout << ' '; break;
            case 1: fout << '+'; break;
            case 2: fout << '-'; break;
            default: break;
          }
        else fout << endl;
      }
    }
  }

  return 0;
}
