/*
ID: hogao81
PROG: contact
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

struct tAns {
  int freq;
  string key;

  tAns(int my_freq, string my_key) : freq(my_freq), key(my_key) {}

  bool operator<(const tAns& other) const {
    if (freq != other.freq) return freq > other.freq;
    return key.size() < other.key.size();
  }
};

int main() {
  ofstream fout ("contact.out");
  ifstream fin ("contact.in");
  int a, b, n;
  fin >> a >> b >> n;

  // 80 per line + max 12
  char buffer[100] = "";
  string read;
  // Clear the first new line
  getline(fin, read);
  getline(fin, read);

  // Map that holds string -> frequency
  map<string, int> freq_map;

  while(!read.empty() || strlen(buffer) != 0) {
    if (!read.empty()) strcpy(buffer + strlen(buffer), read.c_str());

    // Let's iterate until we get b away from the end
    char *ptr = buffer;

    int outer_len = (strlen(buffer) >= b) ? (strlen(buffer) - b) :
      strlen(buffer);

    for (int i = 0; i <= outer_len; i++, ptr++) {
      char temp[20] = "";
      int max_len = min(b, (int) strlen(ptr));
      strncpy(temp, ptr, max_len);
      temp[max_len] = '\0';

      for (int j = max_len; j >= a; j--) {
        temp[j] = '\0';
        string key(temp);
        freq_map[temp]++;
      }
    }

    // Now copy over the end of the string
    if (b >= strlen(buffer)) buffer[0] = '\0';
    else strcpy(buffer, ptr);

    // If read not empty, more values to grab possibly
    if (!read.empty()) {
      read.clear();
      getline(fin, read);
    }
  }

  // Now that we have a map, let's put it into a vector, and sort it
  vector<tAns> sorted;
  for (map<string, int>::iterator it = freq_map.begin();
       it != freq_map.end(); it++) {
    tAns temp(it->second, it->first);
    sorted.push_back(temp);
  }

  stable_sort(sorted.begin(), sorted.end());

  int prev_freq = -1;
  int n_current = 0;
  bool first = true;
  for (vector<tAns>::iterator it = sorted.begin();
       it != sorted.end(); it++) {
    if (it->freq != prev_freq) {
      if (n <= 0) {
        break;
      }

      if (first) first = false;
      else fout << endl;

      n--;
      fout << it->freq << endl;
      prev_freq = it->freq;
      fout << it->key;
      n_current = 1;
    }
    else {
      if (n_current == 6) {
        fout << endl;
        fout << it->key;
        n_current = 1;
      }
      else {
        fout << " " << it->key;
        n_current++;
      }
    }
  }

  fout << endl;

  return 0;
}
