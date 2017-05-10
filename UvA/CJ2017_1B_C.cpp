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

double best(vector<double>& mem, vi& dist, vi& h_speeds, vi& h_dists, int horse, int city)
{
   if (city == dist.size())
      return 0;

   h_dists[city] -= dist[city];
   double o1 = mem[city];
   if (o1 <= 0)
      o1 = mem[city] = dist[city] / (double)h_speeds[city] + best(mem, dist, h_speeds, h_dists, city, city + 1);
   double o2 = 10e20;
   h_dists[city] += dist[city];
   if (h_dists[horse] > dist[city])
   {
      h_dists[horse] -= dist[city];
      o2 = dist[city] / (double)h_speeds[horse] + best(mem, dist, h_speeds, h_dists, horse, city + 1);
      h_dists[horse] += dist[city];
   }
   return min(o1, o2);
}

int main()
{
   cout.precision(12);
   int ntc;
   cin >> ntc;

   FORN(kk, ntc)
   {
      print_case(kk);
      int n, q;
      cin >> n >> q;
      vi speeds(n), distances(n);
      FORN(i, n)
      {
         cin >> distances[i] >> speeds[i];
      }
      vector<vector<ll>> mat(n, vector<ll>(n));
      FORN(i, n)
      {
         FORN(j, n)
         {
            cin >> mat[i][j];
            if (mat[i][j] == -1)
               mat[i][j] = (ll)10e13;
         }
      }
      vector<ii> qs(q);
      FORN(i, q)
      {
         cin >> qs[i].first >> qs[i].second;
      }

      FORN(k, n) FORN(i, n)
      {
         FORN(j, n)
         {
            mat[i][j] = min(mat[i][j], mat[i][k] + mat[k][j]);
         }
      }
      FORN(i, n) FORN(j, n)
      {
         if (mat[i][j] > distances[i])
            mat[i][j] = -1;
      }
      vector<vector<double>> mat2(n, vector<double>(n, -1));
      FORN(i, n) FORN(j, n)
      {
         mat2[i][j] = mat[i][j] != -1 ? mat[i][j] / (double)speeds[i] : 10e15;
      }

      FORN(k, n) FORN(i, n)
      {
         FORN(j, n)
         {
            mat2[i][j] = min(mat2[i][j], mat2[i][k] + mat2[k][j]);
         }
      }
      FORN(i, q)
      {
         double time = mat2[qs[i].first - 1][qs[i].second - 1];
         cout << time << ' ';
      }
      cout << endl;
   }
}
