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
      int n;
      cin >> n;
      initSet(n);
      int success = 0;
      int unsuccess = 0;
      string line;
      getline(cin, line);
      getline(cin, line);
      while (line.length() > 0)
      {
         stringstream ss(line);
         char c;
         int pc1, pc2;
         ss >> c >> pc1 >> pc2;
         if (c == 'c')
         {
            unionSet(pc1 - 1, pc2 - 1);
         }
         else if (c == 'q')
         {
            if (isSameSet(pc1 - 1, pc2 - 1))
               success++;
            else
               unsuccess++;
         }
         getline(cin, line);
      }
      cout << success << "," << unsuccess << endl;
      if (kk != ntc - 1)
         cout << endl;
   }
   return 0;
}
