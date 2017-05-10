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
   string line;
   getline(cin, line);
   for (int i = 0; i < ntc; i++)
   {
      graph = vector<vector<int> >(26);
      visited = vector<bool>(26);
      initSet(26);

      int e = 0;
      int v = 0;

      getline(cin, line);
      while (line[0] != '*')
      {
         int from = line[1] - 65;
         int to = line[3] - 65;
         graph[from].push_back(to);
         graph[to].push_back(from);
         e++;
         getline(cin, line);
      }

      getline(cin, line);
      v = line.length() / 2 + 1;
      leftover = 26 - v;

      int acorns = -leftover;
      for (int j = 0; j < graph.size(); j++)
      {
         if (graph[j].size() == 0)
            acorns++;
         
         for (int k = 0; k < graph[j].size(); k++)
         {
            unionSet(j, graph[j][k]);
         }
      }
      int disjoint = numDisjointSets() - leftover;
      int trees = v - e - acorns;
      printf("There are %d tree(s) and %d acorn(s).\n", disjoint - acorns, acorns);
   }
   return 0;
}
