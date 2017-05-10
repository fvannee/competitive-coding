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
void initSet(int N) { cset = vi(N); pset.assign(N, 0); ndisjoint = N; for (int i = 0; i < N; i++) { pset[i] = i; cset[i] = 1; } }
int findSet(int i) { return pset[i] == i ? i : pset[i] = (findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) { int pi = findSet(i); int pj = findSet(j); if (pi != pj) { pset[pi] = pj; ndisjoint--; cset[pj] += cset[pi]; } }
int numDisjointSets() { return ndisjoint; }
int sizeOfSet(int i) { return cset[findSet(i)]; }

map<string, int> cars;
map<string, int> spycost, rlog;
int price[500], cost[500], cpm[500];

int main() {
   int ntc;
   scanf("%d\n", &ntc);
   FORN(kk, ntc)
   {
      int n, m;
      scanf("%d%d\n", &n, &m);
      cars.clear();
      rlog.clear();
      spycost.clear();
      FORN(i, n)
      {
         string s;
         cin >> s;
         scanf("%d%d%d\n", &price[i], &cost[i], &cpm[i]);
         cars[s] = i;
      }
      FORN(i, m)
      {
         int t;
         char ty;
         string name, car;
         cin >> t >> name >> ty;
         if (ty == 'p')
         {
            cin >> car;
            int cn = cars[car];
            if (rlog.count(name))
            {
               spycost[name] = -1;
            }
            else if (spycost[name] != -1)
            {
               rlog[name] = cn;
            }
         }
         else if (ty == 'r')
         {
            int time;
            cin >> time;
            if (rlog.count(name) && spycost[name] != -1)
            {
               int cn = rlog[name];
               spycost[name] += cost[cn] + cpm[cn] * time;
               rlog.erase(name);
            }
            else
            {
                spycost[name] = -1;
            }
         }
         else if (ty == 'a')
         {
            int severity;
            cin >> severity;
            if (rlog.count(name) && spycost[name] != -1)
            {
               int cn = rlog[name];
               spycost[name] += (int)ceil(price[cn] * (severity / 100.0));
            }
            else
            {
               spycost[name] = -1;
            }
         }
      }
      for (auto i = rlog.begin(); i != rlog.end(); i++)
      {
         spycost[i->first] = -1;
      }
      for (auto i = spycost.begin(); i != spycost.end(); i++)
      {
         if (i->second == -1)
         {
            cout << i->first << " INCONSISTENT" << endl;
         }
         else
         {
            cout << i->first << ' ' << i->second << endl;
         }
      }
   }
}
