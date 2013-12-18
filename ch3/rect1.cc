/*
ID: hogao81
PROG: rect1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

#define BASE 10001

typedef short tUnit;

struct tRect {
  tUnit llx, lly, urx, ury, color;
  bool decrease;

  tRect(tUnit llx = 0, tUnit lly = 0, tUnit urx = 0, tUnit ury = 0,
      tUnit color = 1, bool decrease = false) :
    llx(llx), lly(lly), urx(urx), ury(ury), color(color), decrease(decrease) {}

  long long hash() const {
    return ((long long) llx + (long long)lly * BASE +
        (long long)urx * BASE * BASE +
        (long long)ury * BASE * BASE * BASE) * (decrease ? 1 : -1);
  }

  void print() const {
    printf("%d %d %d %d %d\n", llx, lly, urx, ury, (short)decrease);
  }

  bool operator<(tRect other) const {
    return hash() < other.hash();
  }
};

long long area(tRect& rect) {
  long long area = (rect.urx - rect.llx) * (rect.ury - rect.lly);

  if (rect.decrease) return -1 * area;
  else return area;
}

tRect opposite(tRect& rect) {
  tRect opposite(rect.llx, rect.lly, rect.urx, rect.ury, rect.color, !rect.decrease);
  return opposite;
}

void AddOverlap(tRect& rect1, tRect rect2, int n_rects, map<tRect, int>& overlaps,
    long long *my_area) {

  // No overlap
  if (rect1.llx > rect2.urx || rect2.llx > rect1.urx ||
      rect1.lly > rect2.ury || rect2.lly > rect1.ury) return;

  tRect overlap(
    max(rect1.llx, rect2.llx),
    max(rect1.lly, rect2.lly),
    min(rect1.urx, rect2.urx),
    min(rect1.ury, rect2.ury),
    1,
    !rect2.decrease
  );

  int after = overlaps[overlap] + n_rects;
  *my_area += area(overlap);
  //cout << " *** overlap " << overlaps[overlap] << ", " << n_rects << endl;
  //overlap.print();
  overlaps[overlap] = after;
  //cout << " *** result " << overlaps[overlap] << endl;
}

int main() {
  ofstream fout ("rect1.out");
  ifstream fin ("rect1.in");
  tUnit a, b, n;
  fin >> a >> b >> n;

  tRect rects[n+1];
  map<tUnit, long long> count;

  // First rectangle is the background
  tRect first(0, 0, a, b, 1);
  rects[0] = first;

  for (int i = 1; i <= n; i++) {
    fin >> rects[i].llx >> rects[i].lly >> rects[i].urx >> rects[i].ury
        >> rects[i].color;
  }

  // Keep track over overlaps
  map<tRect, int> overlaps;
  vector<tRect *> valid_rects;

  // Iterate through the rects backwards
  for (int i = n; i >= 0; i--) {
    tRect& my_rect = rects[i];
    long long my_area = area(my_rect);
    //cout << "my area: " << my_area << endl;
    //printf("Processing rect %d, num overlaps %d\n", i, overlaps.size());

    map<tRect, int> my_overlaps;

    // Iterate through valid rects up to it to compute overlaps
    for (vector<tRect *>::iterator it = valid_rects.begin();
         it != valid_rects.end(); it++) {
      AddOverlap(my_rect, *(*it), 1, my_overlaps, &my_area);
    }

    // Now iterate through overlaps
    for (map<tRect, int>::iterator it = overlaps.begin(); it != overlaps.end(); it++) {
      AddOverlap(my_rect, it->first, it->second, my_overlaps, &my_area);
    }

    //cout << i << ": " << my_area << endl;

    // If there is a result we care about
    if (my_area > 0) {
      for (map<tRect, int>::iterator it = my_overlaps.begin();
           it != my_overlaps.end(); it++) {

        tRect me = it->first;
        tRect opp = opposite(me);
        if (overlaps.find(opp) != overlaps.end()) {
          int diff = min(overlaps[opp], it->second);
          overlaps[opp] -= diff;
          if (overlaps[opp] == 0) overlaps.erase(opp);
          overlaps[me] += (it->second - diff);
          if (overlaps[me] == 0) overlaps.erase(me);
        }
        else overlaps[me] += it->second;
      }
      valid_rects.push_back(&(rects[i]));
      count[my_rect.color] += my_area;
    }
  }

  /*
  set<tRect> dups;
  for (vector<tRect>::iterator it = overlaps.begin(); it != overlaps.end(); it++) {
    dups.insert(*it);
  }
  */

  for (map<tUnit, long long>::iterator it = count.begin(); it != count.end(); it++) {
   fout << it->first << " " << it->second << endl;
  }

  return 0;
}
