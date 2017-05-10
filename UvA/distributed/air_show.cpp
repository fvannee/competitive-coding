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

bool almost_equal(double a, double b)
{
   return abs(a - b) < EPS;
}

#include "air_show.h"

#define MASTER_NODE 0

struct point { int x, y, z; };

void extract(ll d, point& p)
{
   p.z = d & ((1ll << 20) - 1);
   p.y = (d >> 20) & ((1ll << 20) - 1);
   p.x = (d >> 40) & ((1ll << 20) - 1);
}

int main()
{
   cout.precision(12);
   int id = MyNodeId();
   int nn = NumberOfNodes();
   int hnn = nn / 2;
   int hid = id % hnn;
   int part = id / hnn;
   int other = 1 - part;

   int segments = GetNumSegments();
   int transitions = segments - 1;
   int start = transitions / hnn * hid;
   int end = transitions / hnn * (hid + 1);
   REP(i, start+1, end+1)
   {
      point p1;
      ll t = GetTime(part, i);
      extract(GetPosition(part, i), p1);

      int best = -1;
      int l = 0, r = segments;
      while (l <= r)
      {
         int mid = l + (r - l) / 2;
         ll t2 = GetTime(other, mid);
         if (t2 <= t)
         {
            best = mid;
            l = mid + 1;
         }
         else
         {
            r = mid - 1;
         }
      }
   }

   if (id == MASTER_NODE) {
      
   }
}
