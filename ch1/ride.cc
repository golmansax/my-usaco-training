/*
ID: hogao81
PROG: test
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int value(string s) {
  char c_str[] = s.c_str();
  char *ptr = c_str;

  int ans = 1;

  while (*ptr != NULL) {
    ans = (ans * (int)(*ptr - 'A')) % 47;
  }
}

int main() {
  ofstream fout ("test.out");
  ifstream fin ("test.in");

  string one, two;

  fin >> one >> two;

  c

  return 0;
}
