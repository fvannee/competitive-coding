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

#include "again.h"

#define MASTER_NODE 0
#define SENDING_DONE -1
#define LARGE_PRIME 1000000007

int main()
{
   cout.precision(12);

   ll N = GetN();
   int id = MyNodeId();
   int numnodes = NumberOfNodes();
   {
      int a = 0;
      int b = 0;
      for (int i = id; i < N; i += numnodes)
      {
         a += GetA(i);
         b += GetB(i);
         a %= LARGE_PRIME;
         b %= LARGE_PRIME;
      }
      PutInt(0, a);
      PutInt(0, b);
      Send(MASTER_NODE);
   }
   if (MyNodeId() == MASTER_NODE) {
      vi as(numnodes);
      vi bs(numnodes);
      int totalA = 0, totalB = 0;
      ll exclude = 0;
      FORN(i, numnodes)
      {
         Receive(i);
         as[i] = GetInt(i);
         bs[i] = GetInt(i);
      }
      FORN(i, numnodes)
      {
         totalA += as[i];
         totalA %= LARGE_PRIME;
         totalB += bs[i];
         totalB %= LARGE_PRIME;
         exclude += (ll)as[i] * bs[(numnodes - i) % numnodes];
         exclude %= LARGE_PRIME;
      }

      ll result = ((ll)totalA * totalB - exclude) % LARGE_PRIME;
      if (result < 0) result += LARGE_PRIME;
      printf("%lld\n", result);
   }
}
