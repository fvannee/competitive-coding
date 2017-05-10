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

vector<vector<int> > graph;
vector<bool> visited;
int leftover;

vi pset;
vi cset;
int ndisjoint;
void initSet(int N) { cset = vi(N); pset.assign(N, 0); ndisjoint = N; for (int i = 0; i < N; i++) { pset[i] = i; cset[i] = 1; }}
int findSet(int i) { return pset[i] == i ? i : pset[i] = (findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) { int pi = findSet(i); int pj = findSet(j); if (pi != pj) { pset[pi] = pj; ndisjoint--; cset[pj] += cset[pi]; }}
int numDisjointSets() { return ndisjoint; }
int sizeOfSet(int i) { return cset[findSet(i)]; }

int dfs(vector<vector<char> >& grid, int x, int y, char land)
{
   if (x < 0 || x >= grid.size() || y < 0 || y >= grid[0].size() || grid[x][y] != land)
      return 0;
   grid[x][y] = land + 1;
   int size = 1;
   size += dfs(grid, x + 1, y, land);
   size += dfs(grid, x - 1, y, land);
   size += dfs(grid, x, (y + 1) % grid[x].size(), land);
   size += dfs(grid, x, y == 0 ? grid[x].size() - 1 : y - 1, land);

   //size += dfs(grid, x - 1, (y + 1) % grid[x].size());
   //size += dfs(grid, x + 1, y == 0 ? grid[x].size() - 1 : y - 1);
   //size += dfs(grid, x + 1, (y + 1) % grid[x].size());
   //size += dfs(grid, x - 1, y == 0 ? grid[x].size() - 1 : y - 1);
   return size;
}

int main() {
   int x, y;
   while (cin >> x >> y)
   {
      vector<vector<char> > grid(x);
      cin.ignore();
      FORN(i, x)
      {
         string line;
         getline(cin, line);
         FORN(j, y)
         {
            grid[i].push_back(line[j]);
         }
      }
      int kx, ky;
      cin >> kx >> ky;

      char land = grid[kx][ky];

      dfs(grid, kx, ky, land);

      int ans = 0;
      FORN(i, x) FORN(j, y)
      {
         ans = max(ans, dfs(grid, i, j, land));
      }
      cout << ans << endl;
   }
}
