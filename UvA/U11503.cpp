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
      int friendships;
      cin >> friendships;
      map<string, int> mapping;
      initSet(2 * friendships + 1);
      int start = 1;
      for (int i = 0; i < friendships; i++)
      {
         string n1, n2;
         cin >> n1 >> n2;
         int n11 = mapping[n1];
         int n21 = mapping[n2];
         if (n11 == 0)
         {
            n11 = mapping[n1] = start;
            start++;
         }
         if (n21 == 0)
         {
            n21 = mapping[n2] = start;
            start++;
         }
         unionSet(n11, n21);
         cout << sizeOfSet(n11) << endl;
      }
   }
   return 0;
}
