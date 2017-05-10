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

#define FORN(X,Y) for (int (X) = 0;(X) < (Y);++(X))
#define FORB(X,Y) for (int (X) = (Y);(X) >= 0;--(X))
#define REP(X,Y,Z) for (int (X) = (Y);(X) < (Z);++(X))
#define REPB(X,Y,Z) for (int (X) = (Y);(X) >= (Z);--(X))

#define SZ(Z) ((int)(Z).size())
#define ALL(W) (W).begin(), (W).end()
#define PB push_back

#define MP make_pair
#define A first
#define B second

#define FORIT(X,Y) for(typeof((Y).begin()) X = (Y).begin();X!=(Y).end();X++)

using namespace std;

typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef vector<ii> vii;

void print_case(int i)
{
   cout << "Case #" << i + 1 << ": ";
}

pair<ll, ll> decompose(ll num)
{
   pair<ll, ll> p;
   p.first = num % 2 == 0 ? num / 2 - 1 : num / 2;
   p.second = num / 2;
   return p;
}

int main()
{
   int ntc;
   cin >> ntc;

   FORN(kk, ntc)
   {
      print_case(kk);
      ll n, k;
      cin >> n >> k;
      map<ll, ll, std::greater<ll>> tree;
      tree[n] = 1;

      while (k > 1)
      {
         auto start = tree.begin();
         auto decomposed = decompose(start->first);
         ll todo = min(k - 1, start->second);
         tree[decomposed.first] += todo;
         tree[decomposed.second] += todo;
         start->second -= todo;
         if (start->second == 0)
            tree.erase(start);
         k -= todo;
      }
      auto ans = decompose(tree.begin()->first);
      cout << ans.second << ' ' << ans.first << endl;
   }
}
