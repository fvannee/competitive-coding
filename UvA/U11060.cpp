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

vector<string> names;
map<string, int> numbers;
vector<vi> graph;

int main() {
   int n, m, kk = 1;
   while (cin >> n)
   {
      names = vector<string>(n);
      numbers.clear();
      graph.clear();
      FORN(i, n)
      {
         graph.push_back(vi(n));
         cin >> names[i];
         numbers[names[i]] = i;
      }
      cin >> m;
      FORN(i, m)
      {
         string b1, b2;
         cin >> b1 >> b2;
         graph[numbers[b1]][numbers[b2]] = 1;
      }

      priority_queue<int> q;
      FORN(i, n)
      {
         bool canadd = true;
         FORN(j, n)
         {
            canadd = graph[j][i] == 0;
            if (!canadd)
               break;
         }
         if (canadd)
            q.push(-i);
      }
      vi trace;
      while (q.size() > 0)
      {
         int el = -q.top();
         q.pop();
         trace.push_back(el);
         FORN(i, n)
         {
            if (graph[el][i] == 1)
            {
               graph[el][i] = 0;
               bool canadd = true;
               FORN(j, n)
               {
                  if (graph[j][i] == 1)
                  {
                     canadd = false;
                     break;
                  }
               }
               if (canadd)
                  q.push(-i);
            }
         }
      }
      cout << "Case #" << kk << ": Dilbert should drink beverages in this order: ";
      FORN(i, n)
      {
         cout << names[trace[i]];
         if (i != n - 1)
            cout << " ";
      }
      cout << "." << endl << endl;
      kk++;
   }
}
