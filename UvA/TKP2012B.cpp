#include <vector>
#include <list>
#include <map>
#include <set>

#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <assert.h>

#define INF 1023123123
#define EPS 1e-11
#define LSOne(S) (S & (-S))

#define FORN(X,Y) for (int (X) = 0;(X) < (Y);++(X))
#define FORB(X,Y) for (int (X) = (Y);(X) >= 0;--(X))
#define REP(X,Y,Z) for (int (X) = (Y);(X) < (Z);++(X))
#define REPB(X,Y,Z) for (int (X) = (Y);(X) >= (Z);--(X))

#define SZ(Z) ((int)(Z).size())
#define ALL(W) (W).begin(), (W).end()
#define PB push_back

#define MP make_pair
#define A first
#define B second

#define FORIT(X,Y) for(typeof((Y).begin()) X = (Y).begin();X!=(Y).end();X++)

using namespace std;

typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

vi pset;
vi cset;
int ndisjoint;
void initSet(int N) { cset = vi(N); pset.assign(N, 0); ndisjoint = N; for (int i = 0; i < N; i++) { pset[i] = i; cset[i] = 1; }}
int findSet(int i) { return pset[i] == i ? i : pset[i] = (findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) { int pi = findSet(i); int pj = findSet(j); if (pi != pj) { pset[pi] = pj; ndisjoint--; cset[pj] += cset[pi]; }}
int numDisjointSets() { return ndisjoint; }
int sizeOfSet(int i) { return cset[findSet(i)]; }

bool matrix[50][50];
bool single[50];
int n, k, m;
int best = -1;

void rec(ll status, int maxdis, int current)
{
   if (current >= n)
   {
      //done
      if (maxdis > best)
         best = maxdis;
      return;
   }
   if (maxdis <= best)
      return;
   if ((status & (1LL << current)) == 0 && !single[current]) //undecided
   {
      status |= (1LL << current); // discard
      rec(status, maxdis - 1, current + 1);

      //status.set(current+51); //keep
      REP(i, current+1, n)
      {
         if (matrix[current][i] && (status & (1LL << i)) == 0)
         {
            status |= (1LL << i);
            maxdis--;
         }
      }
      rec(status, maxdis, current+1);
   }
   else
   {
      rec(status, maxdis, current+1);
   }
}

int main() {
   int ntc;
   scanf("%d", &ntc);
   FORN(kk, ntc)
   {

      scanf("%d %d %d", &n, &k, &m);
      memset(matrix, 0, sizeof(matrix));
      memset(single, true, sizeof(single));

      FORN(i, m)
      {
         int x, y;
         scanf("%d %d", &x, &y);
         x--;
         y--;
         matrix[x][y] = true;
         matrix[y][x] = true;
         single[x] = single[y] = false;
      }

      best = -1;
      rec(0, k, 0);
      if (best == -1)
      {
         printf("IMPOSSIBLE\n");
      }
      else
      {
         printf("%d\n", k - best);
      }
   }
}
