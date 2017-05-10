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
   while (true)
   {
      int n;
      cin >> n;
      if (n == 0)
         break;
      vi ns(n);
      int totalsum = 0;
      for (int i = 0; i < n; i++)
      {
         cin >> ns[i];
         totalsum += ns[i];
      }
      sort(ns.begin(), ns.end(), greater<int>());
      int sum = 0;
      bool possible = totalsum % 2 == 0;
      for (int k = 1; k <= n && possible; k++)
      {
         sum += ns[k - 1];
         int rsum = 0;
         for (int i = k; i < n; i++)
         {
            rsum += min(ns[i], k);
         }
         rsum += k * (k - 1);
         if (sum > rsum)
            possible = false;
      }
      if (possible)
         cout << "Possible" << endl;
      else
         cout << "Not possible" << endl;
   }
   return 0;
}
