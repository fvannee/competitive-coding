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

int main() {
   int ntc;
   cin >> ntc;
   for (int kk = 0; kk < ntc; kk++)
   {
      int n, m;
      cin >> n >> m;
      vector<vi> matrix(n);
      vector<vi> matrix2(n);
      vi sums(m);
      for (int i = 0; i < n; i++)
      {
         matrix2[i].assign(n, 0);
         for (int j = 0; j < m; j++)
         {
            int val;
            cin >> val;
            sums[j] += val;
            matrix[i].push_back(val);
         }
      }

      bool possible = true;
      for (int i = 0; i < m && possible; i++)
      {
         possible &= sums[i] == 2;
         int first = -1;
         for (int j = 0; j < n && possible; j++)
         {
            if (matrix[j][i] == 1)
            {
               if (first == -1)
               {
                  first = j;
               }
               else
               {
                  if (matrix2[j][first] != 0 || matrix2[first][j] != 0)
                  {
                     possible = false;
                  }
                  matrix2[j][first] = 1;
                  matrix2[first][j] = 1;
               }
            }
         }
      }

      if (possible)
         cout << "Yes" << endl;
      else
         cout << "No" << endl;
   }
   return 0;
}
