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

void dfs(vector<vi>& grid, int x, int y, int cur)
{
   if (x < 0 || x >= grid.size() || y < 0 || y >= grid[x].size() || grid[x][y] != cur)
      return;
   grid[x][y] = -1;
   dfs(grid, x - 1, y, cur);
   dfs(grid, x + 1, y, cur);
   dfs(grid, x, y + 1, cur);
   dfs(grid, x, y - 1, cur);
}

int main() {
   while (true)
   {
      int n;
      cin >> n;
      cin.ignore();
      if (n == 0)
         break;
      vector<vi> grid(n);
      vector<bool> had;
      had.assign(n, false);

      FORN(i, n)
      {
         grid[i].assign(n, n - 1);
      }
      FORN(i, n - 1)
      {
         string line;
         getline(cin, line);
         stringstream ss(line);
         int x, y;
         while (ss >> x >> y)
         {
            grid[x - 1][y - 1] = i;
         }
      }

      bool succ = true;
      FORN(x, n) FORN(y, n)
      {
         if (grid[x][y] != -1 && had[grid[x][y]])
            succ = false;
         else if (grid[x][y] != -1)
         {
            int cur = grid[x][y];
            dfs(grid, x, y, cur);
            had[cur] = true;
         }
      }
      cout << (succ ? "good" : "wrong") << endl;
   }
}
