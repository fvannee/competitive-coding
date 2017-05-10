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

int items[100];
int extra[100];
int sums[100];
int dp[100][400001];
int n;

int rec(int cur, int weight)
{
   if ((cur == n && weight > 0) || sums[cur] * 2 < weight)
      return INF;
   if (weight <= 0)
      return 0;
   if (dp[cur][weight] != -1)
      return dp[cur][weight];
   int take = rec(cur + 1, weight - extra[cur]);
   if (take == INF)
      return take;
   int leave = rec(cur + 1, weight);
   int res = min(take + items[cur], leave);
   dp[cur][weight] = res;
   return res;
}

int calc_cm(const vi& begin, const vi& end, const vi& period, int n, int t)
{
   int cm = 0;
   for (int i = 0; i < n; i++)
   {
      int time = min(t + 1, end[i]) - begin[i];
      if (time > 0)
      {
         cm += (int)ceil(time / (double)period[i]);
      }
   }
   return cm;
}

int main2()
{
   int n;
   cin >> n;
   vi begin(n), end(n), period(n);
   for (int i = 0; i < n; i++)
   {
      cin >> begin[i] >> end[i] >> period[i];
   }

   int b = 0;
   int max_el = *max_element(end.begin(), end.end());
   int e = max_el;
   while (b < e)
   {
      int mid = (b + e) / 2;
      int cm = calc_cm(begin, end, period, n, mid);
      if (cm < 99)
      {
         b = mid + 1;
      }
      else
      {
         e = mid;
      }
   }
   cout << (b >= max_el ? -1 : b) << endl;
   return 0;
}

void printBoard(int row, int diag1, int diag2)
{

}

int eightQueens(int n, int row, int diag1, int diag2)
{
   if (n == 0)
   {
      printBoard(row, diag1, diag2);
      return 1;
   }
   int sum = 0;
   for (int i = 0; i < 8; i++)
   {
      bool possible = (row & (1 << i)) == 0 && (diag1 & (1 << i)) == 0 && (diag2 & (1 << i)) == 0;
      if (possible)
      {
         sum += eightQueens(n - 1, row | (1 << i), (diag1 | (1 << i)) << 1, (diag2 | (1 << i)) >> 1);
      }
   }
   return sum;
}

int main3()
{
   int a = eightQueens(8, 0, 0, 0);
   cout << a << endl;
}

int main1() {
   int ntc;
   scanf("%d\n", &ntc);
   FORN(kk, ntc)
   {
      int e;
      cin >> n >> e;
      FORN(i, n)
      {
         cin >> items[i];
         extra[i] = items[i] * 2;
      }
      sort(&items[0], &items[n], less<int>());
      sort(&extra[0], &extra[n], less<int>());
      int sum = 0;
      FORB(i, n - 1)
      {
         sum += items[i];
         sums[i] = sum;
      }

      memset(dp, -1, sizeof(dp));
      int ans = rec(0, e);
      if (ans == INF)
         cout << "FULL" << endl;
      else
         cout << ans << endl;

   }
   return 0;
}
