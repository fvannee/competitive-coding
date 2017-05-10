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

#include "almost_sorted.h"

#define MASTER_NODE 0

int main()
{
   cout.precision(12);
   int id = MyNodeId();
   int nn = NumberOfNodes();
   
   int start = NumberOfFiles() * id / nn;
   int end = NumberOfFiles() * (id + 1) / nn;

   int rs = max(0ll, start - MaxDistance());
   int re = min(NumberOfFiles(), end + MaxDistance());

   vector<ll> vals(re - rs);
   REP(i, rs, re)
      vals[i-rs] = Identifier(i);
   sort(vals.begin(), vals.end());
   ll cs = 0;
   REP(i, start, end)
      cs += (ll)((myint128)vals[i - rs] * (myint128)i % (1ll << 20));
   PutLL(0, cs);
   Send(0);
   if (id == MASTER_NODE) {
      cs = 0;
      FORN(i, nn)
      {
         Receive(i);
         ll nsc = GetLL(i);
         cs = (cs + nsc) % (1ll << 20);
      }
      cout << cs << endl;
   }
}
