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
      int C = 0;
      int J = 1;
      int ac, aj;
      cin >> ac >> aj;
      vector<pair<int, pair<int, int>>> ranges(ac + aj);
      int used_c = 0;
      int used_j = 0;
      FORN(i, ac)
      {
         cin >> ranges[i].first >> ranges[i].second.first;
         ranges[i].second.second = C;
         used_c += ranges[i].second.first - ranges[i].first;
      }
      REP(i, ac, ac + aj)
      {
         cin >> ranges[i].first >> ranges[i].second.first;
         ranges[i].second.second = J;
         used_j += ranges[i].second.first - ranges[i].first;
      }
      sort(ranges.begin(), ranges.end());
      vector<ii> open_ranges_c;
      vector<ii> open_ranges_j;
      int clashes = 0;
      FORN(i, ranges.size())
      {
         auto cur = ranges[i];
         auto prev = i == 0 ? ranges[ranges.size() - 1] : ranges[i - 1];
         if (prev.second.second == cur.second.second)
         {
            int duration = cur.first - prev.second.first;
            if (duration < 0)
               duration += 24 * 60;
            if (prev.second.second == C)
               open_ranges_c.push_back(ii(duration, prev.second.first));
            else
               open_ranges_j.push_back(ii(duration, prev.second.first));
         }
         else
         {
            clashes++;
         }
      }
      sort(open_ranges_c.begin(), open_ranges_c.end());
      sort(open_ranges_j.begin(), open_ranges_j.end());
      int free_c = 720 - used_c;
      int free_j = 720 - used_j;

      FORN(i, open_ranges_c.size())
      {
         auto pp = open_ranges_c[i];
         if (pp.first <= free_c)
         {
            free_c -= pp.first;
         }
         else
         {
            clashes += 2;
         }
      }
      FORN(i, open_ranges_j.size())
      {
         auto pp = open_ranges_j[i];
         if (pp.first <= free_j)
         {
            free_j -= pp.first;
         }
         else
         {
            clashes += 2;
         }
      }
      cout << clashes << endl;
   }
}
