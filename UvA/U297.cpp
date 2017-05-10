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

int cur1, cur2;
string t1, t2;

bool isLeaf(char c)
{
   return c == 'e' || c == 'f';
}

int add_trees(int block_size)
{
   char c1 = t1[cur1];
   char c2 = t2[cur2];
   int c1incr = 0, c2incr = 0;
   if (isLeaf(c1) && isLeaf(c2))
   {
      if (c1 == 'e' && c2 == 'e')
         return 0;
      else
         return block_size;
   }
   if (!isLeaf(c1))
   {
      c1incr = 1;
   }
   if (!isLeaf(c2))
   {
      c2incr = 1;
   }
   int sum = 0;
   for (int i = 0; i < 4; i++)
   {
      cur1 += c1incr;
      cur2 += c2incr;
      sum += add_trees(block_size / 4);
   }
   return sum;
}

int main() {
   int ntc;
   cin >> ntc;
   for (int kk = 0; kk < ntc; kk++)
   {
      cin >> t1 >> t2;
      cur1 = cur2 = 0;
      int res = add_trees(1024);
      cout << "There are " << res << " black pixels." << endl;
   }
   return 0;
}
