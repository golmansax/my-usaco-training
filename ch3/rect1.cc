/*
ID: hogao81
PROG: rect1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>

using namespace std;

struct tRect {
  int llx, lly, urx, ury, color;
  bool decrease;

  tRect(int llx = 0, int lly = 0, int urx = 0, int ury = 0, int color = 1,
      bool decrease = false) :
    llx(llx), lly(lly), urx(urx), ury(ury), color(color), decrease(decrease) {}
};

long long area(tRect rect) {
  long long area = (rect.urx - rect.llx) * (rect.ury - rect.lly);

  if (rect.decrease) return -1 * area;
  else return area;
}

void PrintRect(tRect rect) {
  printf("%d %d %d %d\n", rect.llx, rect.lly, rect.urx, rect.ury);
}

tRect *AddOverlap(tRect rect1, tRect rect2, vector<tRect>& overlaps) {
  // No overlap
  if (rect1.llx > rect2.urx || rect2.llx > rect1.urx ||
      rect1.lly > rect2.ury || rect2.lly > rect1.ury) return NULL;

  tRect overlap(
    max(rect1.llx, rect2.llx),
    max(rect1.lly, rect2.lly),
    min(rect1.urx, rect2.urx),
    min(rect1.ury, rect2.ury),
    1,
    !rect2.decrease
  );
  overlaps.push_back(overlap);
  //PrintRect(overlap);

  return &overlaps.back();
}

int main() {
  ofstream fout ("rect1.out");
  ifstream fin ("rect1.in");
  int a, b, n;
  fin >> a >> b >> n;

  tRect rects[n+1];
  map<int, int> count;

  // First rectangle is the background
  tRect first(0, 0, a, b, 1);
  rects[0] = first;

  for (int i = 1; i <= n; i++) {
    fin >> rects[i].llx >> rects[i].lly >> rects[i].urx >> rects[i].ury
        >> rects[i].color;
  }

  // Keep track over overlaps
  vector<tRect> overlaps;
  vector<tRect *> valid_rects;

  // Iterate through the rects backwards
  for (int i = n; i >= 0; i--) {
    tRect my_rect = rects[i];
    long long my_area = area(my_rect);
    //cout << my_area << endl;

    vector<tRect> my_overlaps;
    // Iterate through valid rects up to it to compute overlaps
    for (vector<tRect *>::iterator it = valid_rects.begin();
         it != valid_rects.end(); it++) {
      tRect *this_overlap = AddOverlap(my_rect, *(*it), my_overlaps);
      if (this_overlap) my_area += area(*this_overlap);
      //cout << "rect: " << my_area << endl;
    }

    // Now iterate through overlaps
    for (vector<tRect>::iterator it = overlaps.begin(); it != overlaps.end();
         it++) {
      tRect *this_overlap = AddOverlap(my_rect, *it, my_overlaps);
      if (this_overlap) my_area += area(*this_overlap);
      //cout << "overlap: " << my_area << endl;
    }

    //cout << i << ": " << my_area << endl;

    // If there is a result we care about
    if (my_area > 0) {
      overlaps.insert(overlaps.end(), my_overlaps.begin(), my_overlaps.end());
      valid_rects.push_back(&(rects[i]));
      count[my_rect.color] += my_area;
    }
    //cout << "num overlaps: " << overlaps.size() << endl;
  }

  for (map<int, int>::iterator it = count.begin(); it != count.end(); it++) {
   fout << it->first << " " << it->second << endl;
  }

  return 0;
}
