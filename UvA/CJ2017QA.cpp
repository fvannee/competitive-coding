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

int main()
{
   int ntc;
   cin >> ntc;

   FORN(kk, ntc)
   {
      print_case(kk);
      bool str[2000] = {};
      char c;
      string word;
      cin >> word;
      int ci = word.size();
      FORN(i, word.size())
      {
         str[i] = word[i] == '+';
      }

      int k;
      cin >> k;

      int flips = 0;
      FORN(i, ci - k + 1)
      {
         if (!str[i])
         {
            FORN(j, k)
            {
               str[i + j] = !str[i + j];
            }
            flips++;
         }
      }
      bool ok = true;
      REP(i, ci - k + 1, ci)
      {
         ok &= str[i];
      }
      if (ok)
         cout << flips << endl;
      else
         cout << "IMPOSSIBLE" << endl;
   }
}
