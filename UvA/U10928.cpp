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
#define INT_MIN     (-2147483647 - 1) /* minimum (signed) int value */
#define INT_MAX       2147483647    /* maximum (signed) int value */

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
   for (int i = 0; i < ntc; i++)
   {
      int p;
      string line;
      cin >> p;
      getline(cin, line);
      vi mini;
      int min = INT_MAX;
      for (int i = 1; i <= p; i++)
      {
         getline(cin, line);
         stringstream s(line);
         int count = 0;
         while (!s.eof())
         {
            int k;
            s >> k;
            count++;
         }
         if (count < min)
         {
            min = count;
            mini.clear();
            mini.push_back(i);
         }
         else if (count == min)
         {
            mini.push_back(i);
         }
      }
      for (int j = 0; j < mini.size(); j++)
      {
         cout << mini[j];
         if (j != mini.size() - 1)
            cout << " ";
      }
      cout << endl;
   }

   return 0;
}
