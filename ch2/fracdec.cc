/*
ID: hogao81
PROG: fracdec
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

using namespace std;

int main() {
  ofstream fout ("fracdec.out");
  ifstream fin ("fracdec.in");

  int n, d;
  fin >> n >> d;

  vector<int> bef, aft;

  while (n >= d) {
    bef.push_back(n / d);
    n = n % d;
  }
  stringstream ss;
  if (bef.empty()) ss << '0';
  else {
    for (vector<int>::iterator it = bef.begin();
         it != bef.end();
         it++)
      ss << *it;
  }
  ss << '.';

  // ends when remainder and val is the same
  int place[10][d];
  memset(place, 0, sizeof(int) * 10 * d);

  int len = 0, val = (n * 10) / d;
  n = (n * 10) % d;
  //printf ("%d %d\n", val, n);
  while (n != 0 && place[val][n] == 0) {
    place[val][n] = ++len;
    aft.push_back(val);

    val = (n * 10) / d;
    n = (n * 10) % d;
    //printf ("%d %d\n", val, n);
  }

  //printf("%d %d %d %d\n", val, n, aft.size(), place[val][n]);
  
  if (n == 0) {
    aft.push_back(val);
    for (vector<int>::iterator it = aft.begin();
         it != aft.end();
         it++)
      ss << *it;
  }
  else {
    vector<int>::iterator it = aft.begin();
    for (int i = 0; i < place[val][n]-1; i++)
      ss << *(it++);
    ss << '(';
    for (; it != aft.end() ; it++)
      ss << *it;
    ss << ')';
  }

#define STR_MAX 100000
  char ans[STR_MAX];
  strncpy(ans, ss.str().c_str(), STR_MAX);
  while (strlen(ans) > 76) {
    char tmp[80];
    strncpy(tmp, ans, 76);
    tmp[76] = '\0';
    fout << tmp << endl;
    strncpy(ans, &(ans[76]), STR_MAX);
  }
  fout << ans << endl;

  return 0;
}
