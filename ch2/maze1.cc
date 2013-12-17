/*
ID: hogao81 
PROG: maze1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

using namespace std;

struct tPt {
  int r, c;
};

struct tQElt{
  tPt pt;
  int prev;
};

void MkPt(tPt *pt, int r, int c) {
  pt->r = r;
  pt->c = c;
}

void SetStart(tPt start[2], int r, int c) {
  //printf ("Start: %d %d\n", r, c);
  if (start[0].r == -1) MkPt(start, r, c);
  else MkPt(start + 1, r, c);
}

void PushQ(tQElt **q, tPt pt, int dist) {
  (*q)->pt = pt;
  (*q)->prev = dist;
  (*q)++;
}

void PushQ(tQElt **q, int r, int c, int dist) {
  (*q)->pt.r = r;
  (*q)->pt.c = c;
  (*q)->prev = dist;
  (*q)++;
}

int main() {
  ofstream fout("maze1.out");
  ifstream fin("maze1.in");
  int w, h;
  fin >> w >> h;

  // horizontal and vertical walls
  bool hor_wall[h + 1][w], ver_wall[h][w + 1];
  memset(hor_wall, 0, sizeof(bool) * (h + 1) * w);
  memset(ver_wall, 0, sizeof(bool) * h * (w + 1));
  tPt start[2];
  MkPt(start, -1, -1);
  MkPt(start + 1, -1, -1);

  char line[2 * w + 1];
#define MAX_STR 1000
  fin.getline(line, MAX_STR);
  for (int i = 0; i < 2 * h + 1; i++) {
    fin.getline(line, MAX_STR);
    cout << "Line: " << line << endl;
    for (int j = 0; j < 2 * w + 1; j++) {
      char c = line[j];

      // check for start
      if (i == 0 && c == ' ') {
        SetStart(start, 0, (j - 1) / 2);
        c = '-';
      }
      else if (i == 2 * h && c == ' ') {
        SetStart(start, h - 1, (j - 1) / 2);
        c = '-';
      }
      else if (j == 0 && c == ' ') {
        SetStart(start, (i - 1) / 2, 0);
        c = '|';
      }
      else if (j == 2 * w && c == ' ') {
        SetStart(start, (i - 1) / 2, w - 1);
        c = '|';
      }

      // put in walls
      if ((i - 1) % 2 == 0) {
        // vert wall
        if (j % 2 == 0 && c == '|') ver_wall[(i - 1) / 2][j / 2] = true;
      }
      else if ((j - 1) % 2 == 0) {
        // horiz wall
        if (i % 2 == 0 && c == '-') hor_wall[i / 2][(j - 1) / 2] = true;
      }
    }
  }

  // breadth first search to find distance
  int dist[h][w];
  for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) dist[i][j] = 100000;

  tQElt q[h * w * 2];
  memset(q, 0, sizeof(tQElt) * h * w);

  tQElt *cur = q, *end = q;
  PushQ(&end, start[0], 1);
  if (start[0].r != start[1].r || start[0].c != start[1].c) 
    PushQ(&end, start[1], 1);

  int ans = 0;

  while (cur < end) {
    tPt pt = cur->pt;
    int r = pt.r, c = pt.c;
    int my_dist = cur->prev;
    printf ("%d %d %d\n", r, c, my_dist);
    if (my_dist >= dist[r][c]) {
      cur++;
      continue;
    }
    dist[r][c] = my_dist;
    ans = MAX(ans, my_dist);

    // try to go to all four sides
    // first horizontally
    if (!ver_wall[r][c]) {
      // left
      if (my_dist + 1 < dist[r][c - 1])
        PushQ(&end, r, c - 1, my_dist + 1);
    }
    if (!ver_wall[r][c + 1]) {
      // right
      if (my_dist + 1 < dist[r][c + 1]) PushQ(&end, r, c + 1, my_dist + 1);
    }
    if (!hor_wall[r][c]) {
      // up
      if (my_dist + 1 < dist[r - 1][c]) PushQ(&end, r - 1, c, my_dist + 1);
    }
    if (!hor_wall[r + 1][c]) {
      // down
      if (my_dist + 1 < dist[r + 1][c]) PushQ(&end, r + 1, c, my_dist + 1);
    }

    cur++;
  }
  fout << ans << endl;

  return 0;
}
