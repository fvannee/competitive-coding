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

int compare_ii(ii i, ii j)
{
   if (i.first == j.first && i.second == j.second)
      return 0;
   else if (i.first > j.first || i.second > j.second)
      return 1;
   else 
      return -1;
}

int in_range(ii i, ii j, ii L, ii R)
{
   if (L.first > j.first || L.second > j.second || R.first < i.first || R.second < i.second)
      return 1;
   if (i.first <= L.first && R.first <= j.first && i.second <= L.second && R.second <= j.second)
      return -1;
   return 0;
}

ii min_el(vector<ii> &t, const vector<vi> &A, ii n1Content, ii n2Content, ii n3Content, ii n4Content, bool min )
{
   ii vs[4];
   vs[0] = n1Content;
   vs[1] = n2Content;
   vs[2] = n3Content;
   vs[3] = n4Content;
   vector<ii> toSort;
   for (int i = 0; i < 4; i++)
   {
      if (vs[i].first != -1)
         toSort.push_back(ii(A[vs[i].first][vs[i].second], i));
   }
   if (min)
      sort(toSort.begin(), toSort.end());
   else
      sort(toSort.begin(), toSort.end(), greater<ii>());

   if (toSort.size() == 0)
      return ii(-1, -1);
   return vs[toSort[0].second];
}

// Segment Tree Library: The segment tree is stored like a heap array
void st_build2(vector<ii> &t, const vector<vi> &A, int vertex, ii L, ii R, bool min) {
   if (compare_ii(L, R) > 0)
      t[vertex] = ii(-1, -1);
   else if (L == R) // as L == R, either one is fine
      t[vertex] = L; // store the index
   else { // recursively compute the values in the left and right subtrees
      int n1 = 4 * vertex + 1, n2 = 4 * vertex + 2, n3 = 4 * vertex + 3, n4 = 4 * vertex + 4;
      int mid1 = (L.first + R.first) / 2;
      int mid2 = (L.second + R.second) / 2;
      st_build2(t, A, n1, ii(L.first, L.second), ii(mid1, mid2), min); // this is O(n log n)
      st_build2(t, A, n2, ii(mid1 + 1, mid2 + 1), ii(R.first, R.second), min); // this is O(n log n)
      st_build2(t, A, n3, ii(L.first, mid2 + 1), ii(mid1, R.second), min); // this is O(n log n)
      st_build2(t, A, n4, ii(mid1 + 1, L.second), ii(R.first, mid2), min); // this is O(n log n)
      ii n1Content = t[n1] , n2Content = t[n2], n3Content = t[n3], n4Content = t[n4];
      
      ii min_ = min_el(t, A, n1Content, n2Content, n3Content, n4Content, min);
      t[vertex] = min_;
   } }

void st_create2(vector<ii> &t, const vector<vi> &A, bool min) { // if original array size is N,
   // the required segment tree array length is 2*2^(floor(log2(N)) + 1);
   int len = (int)(4 * pow(2.0, floor((log((double)A.size()*A.size()) / log(2.0)) + 1))) + 1;
   t.assign(len, ii(-1, -1)); // create vector with length ‘len’ and fill it with zeroes
   st_build2(t, A, 0, ii(0,0), ii((int)A.size() - 1, (int)A.size() - 1), min); // recursively build the segment tree
}

ii st_rmq2(vector<ii> &t, const vector<vi> &A, int vertex, ii L, ii R, ii i, ii j, bool min) {
   int ran = in_range(i, j, L, R);
   if (ran == 1) return ii(-1,-1); // current segment outside query range
   if (ran == -1) return t[vertex]; // current segment inside query range

   int n1 = 4 * vertex + 1, n2 = 4 * vertex + 2, n3 = 4 * vertex + 3, n4 = 4 * vertex + 4;
   int mid1 = (L.first + R.first) / 2;
   int mid2 = (L.second + R.second) / 2;
   ii p1 = st_rmq2(t, A, n1, ii(L.first, L.second), ii(mid1, mid2), i, j, min); // this is O(n log n)
   ii p2 = st_rmq2(t, A, n2, ii(mid1 + 1, mid2 + 1), ii(R.first, R.second), i, j, min); // this is O(n log n)
   ii p3 = st_rmq2(t, A, n3, ii(L.first, mid2 + 1), ii(mid1, R.second), i, j, min); // this is O(n log n)
   ii p4 = st_rmq2(t, A, n4, ii(mid1 + 1, L.second), ii(R.first, mid2), i, j, min); // this is O(n log n)

   return min_el(t, A, p1, p2, p3, p4, min);
}

ii st_rmq2(vector<ii> &t, const vector<vi> &A, ii i, ii j, bool min) { // overloading, simpler arguments
   return st_rmq2(t, A, 0, ii(0,0), ii((int)A.size() - 1, (int)A.size() - 1), i, j, min); }

int st_index(vector<ii> &t, vector<vi> &A, int vertex, ii L, ii R, ii i, ii j)
{
   int ran = in_range(i, j, L, R);
   if (ran == 1) return -1; // current segment outside query range
   if (ran == -1) return vertex; // current segment inside query range

   int n1 = 4 * vertex + 1, n2 = 4 * vertex + 2, n3 = 4 * vertex + 3, n4 = 4 * vertex + 4;
   int mid1 = (L.first + R.first) / 2;
   int mid2 = (L.second + R.second) / 2;
   int p1 = st_index(t, A, n1, ii(L.first, L.second), ii(mid1, mid2), i, j ); // this is O(n log n)
   if (p1 != -1)
      return p1;
   int p2 = st_index(t, A, n2, ii(mid1 + 1, mid2 + 1), ii(R.first, R.second), i, j ); // this is O(n log n)
   if (p2 != -1)
      return p2;
   int p3 = st_index(t, A, n3, ii(L.first, mid2 + 1), ii(mid1, R.second), i, j ); // this is O(n log n)
   if (p3 != -1)
      return p3;
   int p4 = st_index(t, A, n4, ii(mid1 + 1, L.second), ii(R.first, mid2), i, j ); // this is O(n log n)
   if (p4 != -1)
      return p4;
   return -1;
}

void st_update(vector<ii> &t, vector<vi> &A, ii index, int value, bool min)
{
   A[index.first][index.second] = value;
   int depth = (int)floor((log((double)A.size()*A.size()) / log(2.0)));
   int treeIndex = st_index(t, A, 0, ii(0,0), ii((int)A.size() - 1, (int)A.size() - 1), index, index);
   //int treeIndex2 = t.size() - 1;
   //while (index != t[treeIndex2])
   //   treeIndex2--;

   int parent = (treeIndex-1)/4;
   while (treeIndex > 0)
   {
      ii min1 = min_el(t, A, t[4*parent+1], t[4*parent+2], t[4*parent+3], t[4*parent+4], min);
      t[parent] = min1;
      treeIndex = parent;
      parent = (treeIndex-1)/4;
   }
}

int main() {
   int n;
   cin >> n >> n;
   vector<vi> matrix(n);
   vector<ii> minHeap;
   vector<ii> maxHeap;
   for (int i = 0; i < n; i++)
   {
      for (int j = 0; j < n; j++)
      {
         int val;
         cin >> val;
         matrix[i].push_back(val);
      }
   }
   int q;
   cin >> q;
   st_create2(minHeap, matrix, true);
   st_create2(maxHeap, matrix, false);
   for (int i = 0; i < q; i++)
   {
      char t;
      cin >> t;
      if (t == 'q')
      {
         int lx, ly, rx, ry;
         cin >> lx >> ly >> rx >> ry;
         ii ansmin = st_rmq2(minHeap, matrix, ii(lx - 1, ly - 1), ii(rx - 1, ry - 1), true);
         ii ansmax = st_rmq2(maxHeap, matrix, ii(lx - 1, ly - 1), ii(rx - 1, ry - 1), false);
         cout << matrix[ansmax.first][ansmax.second] << " " << matrix[ansmin.first][ansmin.second] << endl;
      }
      else
      {
         int x, y, val;
         cin >> x >> y >> val;
         st_update(minHeap, matrix, ii(x-1,y-1), val, true);
         st_update(maxHeap, matrix, ii(x-1,y-1), val, false);
      }
   }
   return 0;
}
