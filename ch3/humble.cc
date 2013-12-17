/*
ID: hogao81
PROG: humble
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <set>

using namespace std;

int main() {
  ofstream fout ("humble.out");
  ifstream fin ("humble.in");
  int k, n;
  fin >> k >> n;

  set<long long> seen;
  long long init[k];
  for (int i = 0; i < k; i++) {
    fin >> init[i];
    seen.insert(init[i]);
  }
  cout << "Read input fine" << endl;

  long long ans;
  while (true) {
    set<long long>::iterator top = seen.begin();
    long long me = *top;
    n--;

    if (me < 0) {
      ans = me;
      cout << "negative number result, error" << endl;
      break;
    }

    if (n == 0) {
      ans = me;
      break;
    }

    // Remove the first element
    seen.erase(top);

    int size = seen.size();
    long long max = (size > 0) ? *(seen.rbegin()) : 0;

    // Only go through initial primes
    for (int i = 0; i < k; i++) {
      long long reply = init[i] * me;
      if (reply >= me &&
          !(size >= n && reply > max)) seen.insert(init[i] * me);
    }

    //cout << "Num elts in seen: " << seen.size() << endl;
    while (seen.size() > n) {
      long long last = *(seen.rbegin());
      //cout << "  Erasing " << last << endl;
      seen.erase(seen.find(last));
    }

/*
    // Erase up to the num elts we need
    if (seen.size() > n) {
      seen.erase(seen.begin() + n, seen.end());
    }
    */
  }

  fout << ans << endl;

  return 0;
}
