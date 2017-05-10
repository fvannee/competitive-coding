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
#include <boost/lexical_cast.hpp>

#define INF 1023123123
#define EPS 1e-11
#define LSOne(S) (S & (-S))

#define M_PI           3.14159265358979323846  /* pi */

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

void print_case(int i)
{
   cout << "Case #" << i + 1 << ": ";
}

bool myfunction(pair<ll, pair<ll, int>> i, pair<ll, pair<ll, int>> j) { return (i>j); }

int main()
{
   cout.precision(12);
   int ntc;
   cin >> ntc;

   FORN(kk, ntc)
   {
      print_case(kk);
      int n, k;
      cin >> n >> k;
      vector<pair<ll, pair<ll, int>>> hs(n);
      vector<pair<ll, pair<ll, int>>> rs(n);
      vector<pair<ll, ll>> all(n);
      vi nn;
      FORN(i, n)
      {
         hs[i].second.second = i;
         rs[i].second.second = i;
         cin >> rs[i].first;
         cin >> hs[i].first;
         hs[i].second.first = rs[i].first;
         rs[i].second.first = hs[i].first;
         all[i].first = rs[i].first;
         all[i].second = hs[i].first;
         hs[i].first *= rs[i].first;
      }
      sort(hs.begin(), hs.end(), myfunction);
      sort(rs.begin(), rs.end(), myfunction);

      double maxArea = -1;
      FORN(i, n)
      {
         auto top = rs[i];
         int toChoose = k - 1;
         int hIndex = 0;
         double area = M_PI * top.first * top.first + 2 * M_PI * all[top.second.second].second * top.first;
         while (hIndex < n && toChoose > 0)
         {
            if (hs[hIndex].second.second != top.second.second && all[hs[hIndex].second.second].first <= top.first)
            {
               area += 2 * M_PI * hs[hIndex].first;
               toChoose--;
            }
            hIndex++;
         }
         if (toChoose == 0 && area > maxArea)
         {
            maxArea = area;
         }
      }

      cout << maxArea << endl;
   }
}
