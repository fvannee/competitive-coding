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

bitset<2001> bs;
vi primes;

void sieve(int max)
{
   primes.clear();
   bs.set();
   bs[0] = 0;
   bs[1] = 0;
   for (int i = 2; i <= max; i++)
   {
      if (bs[i])
      {
         for (int j = i * i; j <= max; j+=i)
         {
            bs[j] = 0;
         }
         primes.push_back(i);
      }
   }
}

int mem[1121][1121][15]; // cur, n, k

int solve(int cur, int n, int k)
{
   if (n == 0 && k == 0)
      return 1;
   if (k == 0 || n <= 0 || cur >= primes.size())
      return 0;
   if (mem[cur][n][k] == -1)
      mem[cur][n][k] = solve(cur + 1, n - primes[cur], k - 1) + solve(cur + 1, n, k);
   return mem[cur][n][k];
}

int main() {
   sieve(2000);
   memset(mem, -1, sizeof(mem));
   while (true)
   {
      int n, k;
      cin >> n >> k;
      if (n == 0 && k == 0)
         break;

      int res = solve(0, n, k);
      cout << res << endl;
   }
}
