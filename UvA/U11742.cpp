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

// Segment Tree Library: The segment tree is stored like a heap array
void st_build(vi &t, const vi &A, int vertex, int L, int R) {
   if (L == R) // as L == R, either one is fine
      t[vertex] = L; // store the index
   else { // recursively compute the values in the left and right subtrees
      int nL = 2 * vertex, nR = 2 * vertex + 1;
      st_build(t, A, nL, L , (L + R) / 2); // this is O(n log n)
      st_build(t, A, nR, (L + R) / 2 + 1, R ); // similar analysis as
      int lContent = t[nL] , rContent = t[nR]; // with merge sort
      int lValue = A[lContent], rValue = A[rContent];
      t[vertex] = (lValue <= rValue) ? lContent : rContent;
   } }

void st_create(vi &t, const vi &A) { // if original array size is N,
   // the required segment tree array length is 2*2^(floor(log2(N)) + 1);
   int len = (int)(2 * pow(2.0, floor((log((double)A.size()) / log(2.0)) + 1)));
   t.assign(len, 0); // create vector with length ‘len’ and fill it with zeroes
   st_build(t, A, 1, 0, (int)A.size() - 1); // recursively build the segment tree
}

int st_rmq(vi &t, const vi &A, int vertex, int L, int R, int i, int j) {
   if (i > R || j < L) return -1; // current segment outside query range
   if (L >= i && R <= j) return t[vertex]; // current segment inside query range
   // compute the minimum position in the left and right part of the interval
   int p1 = st_rmq(t, A, 2 * vertex , L , (L + R) / 2, i, j);
   int p2 = st_rmq(t, A, 2 * vertex + 1, (L + R) / 2 + 1, R , i, j);
   // return the position where the overall minimum is
   if (p1 == -1) return p2; // if we try to access segment outside query
   if (p2 == -1) return p1; // same as above
   return (A[p1] <= A[p2]) ? p1 : p2; }

int st_rmq(vi &t, const vi& A, int i, int j) { // overloading, simpler arguments
   return st_rmq(t, A, 1, 0, (int)A.size() - 1, i, j); }

int st_index(vi &t, vi &A, int vertex, int L, int R, int i, int j)
{
   if (i > R || j < L) return -1; // current segment outside query range
   if (L >= i && R <= j) return vertex; // current segment inside query range
   // compute the minimum position in the left and right part of the interval
   int p1 = st_index(t, A, 2 * vertex , L , (L + R) / 2, i, j);
   int p2 = st_index(t, A, 2 * vertex + 1, (L + R) / 2 + 1, R , i, j);
   // return the position where the overall minimum is
   if (p1 == -1) return p2; // if we try to access segment outside query
   if (p2 == -1) return p1; // same as above
   return -1;
}

void st_update(vi &t, vi &A, int index, int value, bool min)
{
   A[index] = value;
   int treeIndex = st_index(t, A, 1, 0, (int)A.size() - 1, index, index);
   int parent = treeIndex/2;
   while (parent >= 1)
   {
      int i1 = t[2*parent], i2 = t[2*parent+1];
      if (i2 == 0 || (A[i1] <= A[i2]) == min)
      {
         t[parent] = i1;
      }
      else
      {
         t[parent] = i2;
      }
      treeIndex = parent;
      parent /= 2;
   }
}

void ft_create(vi &t, int size) { t.assign(size + 1, 0); }

void ft_modify(vi &t, int index, int diff) { for (; index < t.size(); index += LSOne(index)) t[index] += diff; }

int ft_rmq(vi &t, int right) {
   int sum = 0;
   for (; right > 0; right -= LSOne(right))
      sum += t[right];
   return sum; }

int ft_rmq(vi &t, int left, int right) {
   if (left == 1)
      return ft_rmq(t, right);
   else
      return ft_rmq(t, right) - ft_rmq(t, left - 1); }

int ft_firstcum(vi &t, int cumulative)
{
   int low = 0;
   int diff = 1;
   int next = -1;
   while (true)
   {
      next = low + diff;
      if (next >= t.size() || t[next] >= cumulative)
      {
         if (diff == 1)
            break;
         low += diff/2;
         diff = 1;
      }
      else
      {
         diff *= 2;
      }
   }
   return next >= t.size() ? -1 : next; // offset
}

int a[20];
int b[20];
int c[20];
int perm[8];
int pos[8];

int main() {
   while(true)
   {
      int n, m;
      cin >> n >> m;
      if (n == 0 && m == 0)
         break;

      for (int i = 0; i < m; i++)
      {
         cin >> a[i] >> b[i] >> c[i];
      }
      
      for (int i = 0; i < n; i++)
         perm[i] = i;

      int numvalid = 0;
      do
      {
         for (int i = 0; i < n; i++)
         {
            pos[perm[i]] = i;
         }
         bool valid = true;
         for (int i = 0; i < m && valid; i++)
         {
            int diff = abs(pos[a[i]] - pos[b[i]]);
            if (c[i] < 0)
            {
               valid = diff >= -c[i];
            }
            else
            {
               valid = diff <= c[i];
            }
         }
         if (valid)
            numvalid++;
      } while (next_permutation(perm, perm + n));
      cout << numvalid << endl;
   }
}
