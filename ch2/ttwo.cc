/*
ID: hogao81 
PROG: ttwo
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))

using namespace std;

struct tPos {
  int r, c, dir;
};

struct tCycle {
  int start, end, len;
  tPos pos;
};

void FindPaths(int pos[10][10][4], int obstacles[10][10], tCycle *cycle,
               tPos cur, int step) {
  //printf("%d %d %d %d\n", cur.r, cur.c, cur.dir, step);
  int r = cur.r, c = cur.c, dir = cur.dir;
  tPos next = cur;
  // check if going off board or facing obstacle
  bool turn = false;
  switch(dir) {
   case 0:
    if (r == 0 || obstacles[r-1][c]) turn = true;
    else (next.r)--;
    break;
   case 1:
    if (c == 9 || obstacles[r][c+1]) turn = true;
    else (next.c)++;
    break;
   case 2:
    if (r == 9 || obstacles[r+1][c]) turn = true;
    else (next.r)++;
    break;
   case 3:
    if (c == 0 || obstacles[r][c-1]) turn = true;
    else (next.c)--;
    break;
   default:
    ;
  }

  if (turn) next.dir = (next.dir + 1) % 4;
  if (pos[next.r][next.c][next.dir]) {
    // already did this so cycle!
    cycle->start = pos[next.r][next.c][next.dir];
    cycle->end = step + 1;
    cycle->pos = next;
    cycle->len = cycle->end - cycle->start;
    printf ("cycle: pos: %d %d, st/end/len: %d %d %d\n", 
            next.r, next.c, cycle->start, cycle->end, cycle->len);
  } else {
    pos[next.r][next.c][next.dir] = step + 1;
    FindPaths(pos, obstacles, cycle, next, step + 1);
  }
}

int main() {
  ofstream fout ("ttwo.out");
  ifstream fin ("ttwo.in");

  int obstacles[10][10];
  memset(obstacles, 0, sizeof(int)*10*10);

  // f for farmer, c for cow
  int f_pos[10][10][4]; // 0->3: N->W
  int c_pos[10][10][4];
  memset(f_pos, 0, sizeof(int)*10*10*4);
  memset(c_pos, 0, sizeof(int)*10*10*4);

  tPos f_start, c_start;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) {
      char c;
      fin >> c;
      if (c == 'F') {
        f_pos[i][j][0] = 1;
        f_start.r = i;
        f_start.c = j;
        f_start.dir = 0;
      }
      else if (c == 'C') {
        c_pos[i][j][0] = 1;
        c_start.r = i;
        c_start.c = j;
        c_start.dir = 0;
      }
      else if (c == '*') obstacles[i][j] = 1;
    }

  tCycle f_cycle, c_cycle;
  FindPaths(f_pos, obstacles, &f_cycle, f_start, 1);
  FindPaths(c_pos, obstacles, &c_cycle, c_start, 1);
  // guaranteeing that cycles

#define MAX_INT 10011
  int ans = MAX_INT;
  for (int i = 0; i < 10; i++)
    for (int j = 0; j < 10; j++) 
      for (int dir1 = 0; dir1 < 4; dir1++) {
        for (int dir2 = 0; dir2 < 4; dir2++) {
          if (f_pos[i][j][dir1] && c_pos[i][j][dir2]) {
            // find when they met
            int f_idx = f_pos[i][j][dir1], c_idx = c_pos[i][j][dir2];
            //printf ("pos: %d %d idx: %d %d %d\n", 
                    //i, j, f_idx, c_idx, f_idx-c_idx);
            if (f_idx == c_idx) {
              ans = MIN(ans, f_idx);
              continue;
            }
            if (f_idx < f_cycle.start && c_idx >= c_cycle.start) {
              if (f_idx > c_idx &&
                  (f_idx - c_idx) % c_cycle.len == 0) {
                ans = MIN(ans, f_idx);
                //printf ("  ans = %d\n", ans);
              }
              continue;
            } else if (f_idx >= f_cycle.start && c_idx < c_cycle.start) {
              if (c_idx > f_idx &&
                  (c_idx - f_idx) % f_cycle.len == 0) {
                ans = MIN(ans, c_idx);
                //printf ("  ans = %d\n", ans);
              }
              continue;
            } else if (f_idx >= f_cycle.start && c_idx >= c_cycle.start) {
              // both in cycle
              int cur, inc, mod, add;
              if (f_idx > c_idx) {
                cur = f_idx - c_idx;
                inc = f_cycle.len;
                mod = c_cycle.len;
                add = c_idx;
              } else {
                cur = c_idx - f_idx;
                inc = c_cycle.len;
                mod = f_cycle.len;
                add = f_idx;
              }
              while (cur < MAX_INT && cur % mod != 0) cur += inc;
              if (cur < MAX_INT) {
                ans = MIN(ans, cur + add);
                //printf ("  ans = %d\n", ans);
              }
            }
          }
        }
      }

  ans--;
  if (ans == MAX_INT - 1) ans = 0;
  fout << ans << endl;

  return 0;
}
