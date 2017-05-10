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

vector<vector<int> > graph;
vector<bool> visited;
int leftover;

vi pset;
vi cset;
int ndisjoint;
void initSet(int N) { cset = vi(N); pset.assign(N, 0); ndisjoint = N; for (int i = 0; i < N; i++) { pset[i] = i; cset[i] = 1; }}
int findSet(int i) { return pset[i] == i ? i : pset[i] = (findSet(pset[i])); }
bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
void unionSet(int i, int j) { int pi = findSet(i); int pj = findSet(j); if (pi != pj) { pset[pi] = pj; ndisjoint--; cset[pj] += cset[pi]; }}
int numDisjointSets() { return ndisjoint; }
int sizeOfSet(int i) { return cset[findSet(i)]; }

vector<vi> matrix;
vi depends;
vi taken;
map<char, int> mapping;
map<int, char> mappingback;
vi trace;

bool backtrack(int n)
{
   bool res = false;
   if (n == 0)
   {
      res = true;
      FORN(i, trace.size())
      {
         printf("%c", mappingback[trace[i]]);
         if (i != trace.size() - 1)
            printf(" ");
      }
      printf("\n");
   }
   else
   {
      FORN(i, matrix.size())
      {
         if (!depends[i] && !taken[i])
         {
            taken[i] = 1;
            FORN(j, matrix.size())
            {
               if (matrix[i][j] == 1)
                  depends[j]--;
            }

            trace.push_back(i);
            res |= backtrack(n - 1);
            trace.pop_back();

            taken[i] = 0;
            FORN(j, matrix.size())
            {
               if (matrix[i][j] == 1)
                  depends[j]++;
            }
         }
      }
   }
   return res;
}

int main() {
   int ntc;
   string line;
   scanf("%d", &ntc);
   getline(cin, line);
   FORN(kk, ntc)
   {
      getline(cin, line);
      getline(cin, line);
      int count = 0;
      for (int i = 0; i < line.length(); i+=2)
      {
         mapping[line[i]] = count;
         mappingback[count] = line[i];
         count++;
      }
      depends.clear();
      taken.clear();
      matrix.clear();
      FORN(i, count)
      {
         matrix.push_back(vi());
         matrix[i].assign(count, 0);
      }
      depends.assign(count, 0);
      taken.assign(count, 0);
      getline(cin, line);
      for (int i = 0; i < line.length(); i+=4)
      {
         matrix[mapping[line[i]]][mapping[line[i + 2]]] = 1;
         depends[mapping[line[i + 2]]]++;
      }

      bool succ = backtrack(count);
      if (!succ)
         printf("NO\n");

      if (kk != ntc - 1)
         printf("\n");
   }
}
