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
#include <message.h>

#define INF 1023123123
#define EPS 1e-11
#define LSOne(S) (S & (-S))

#define M_PI 3.14159265358979323846  /* pi */

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
#ifdef FLORIS_DEBUG
#include <boost/multiprecision/cpp_int.hpp>
typedef boost::multiprecision::int128_t myint128;
#else
typedef __int128 myint128;
#endif

bool almost_equal(double a, double b)
{
   return abs(a - b) < EPS;
}

#include "asteroids.h"

#define MASTER_NODE 0

int main()
{
   cout.precision(12);
   int id = MyNodeId();
   int nn = NumberOfNodes();

   int w = GetWidth();
   int th = GetHeight();
   int hs = th * id / nn;
   int he = th * (id + 1) / nn;
   int h = he - hs;

   vector<vector<vector<ll>>> grid(w, vector<vector<ll>>(2, vector<ll>(2)));
   FORN(x, w)
   {
      char pos = GetPosition(hs, x);
      ll val = pos == '#' ? -INF : pos - 48;
      grid[x][1-hs%2][0] = val;
   }
   int dy = 0;
   FORN(i, 2 * h)
   {
      int y = hs + i / 2;
      dy = y % 2;

      /*if (i % 2 != 0)
         cout << "R ";
      else
         cout << "U ";*/

      FORN(x, w)
      {
         char pos = GetPosition(y, x);
         ll val = pos == '#' ? -INF : pos - 48;
         if (i % 2 != 0)
         {
            // right
            grid[x][dy][1] = max({ grid[x][dy][0], x-1 >= 0 ? grid[x-1][dy][0] + val : -INF, x+1 < w ? grid[x+1][dy][0] + val : -INF });
            /*if (grid[x][dy][1] < 0)
               cout << "### ";
            else
               cout << setfill('0') << setw(3) << grid[x][dy][1] << ' ';*/
         }
         else
         {
            // up
            grid[x][dy][0] = grid[x][1 - dy][1] + val;
            /*if (grid[x][dy][0] < 0)
               cout << "### ";
            else
               cout << setfill('0') << setw(3) << grid[x][dy][0] << ' ';*/
         }
      }
      //cout << endl;
   }
   int last_y = dy;
   int m = -1;
   FORN(i, w)
   {
      if (grid[i][last_y][1] > m)
      {
         m = grid[i][last_y][1];
      }
   }
   if (id == MASTER_NODE) {
      cout << m << endl;
   }
}
