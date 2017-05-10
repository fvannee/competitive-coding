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
      int n, c;
      cin >> n >> c;
      initSet(30);
      vector<vi> graph(30);
      if (cin.eof())
         break;
      string line;
      getline(cin, line);
      getline(cin, line);
      int i1 = line[0] - 65;
      for (int i = 1; i <= 2; i++)
      {
         unionSet(i1, line[i] - 65);
      }
      for (int i = 0; i < c; i++)
      {
         getline(cin, line);
         int from = line[0] - 65;
         int to = line[1] - 65;
         graph[from].push_back(to);
         graph[to].push_back(from);
      }
      bool progress = true;
      while (progress)
      {
         progress = false;
         for (int i = 0; i < graph.size(); i++)
         {

         }
      }
   }
   return 0;
}
