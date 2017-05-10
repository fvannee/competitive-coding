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
#include <boost/lexical_cast.hpp>

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

bool clashes(char c, char d)
{
   return c == d ||
      (c == 'O' && (d == 'R' || d == 'Y')) ||
      (c == 'G' && (d == 'B' || d == 'Y')) ||
      (c == 'V' && (d == 'R' || d == 'B')) ||
      (d == 'O' && (c == 'R' || c == 'Y')) ||
      (d == 'G' && (c == 'B' || c == 'Y')) ||
      (d == 'V' && (c == 'R' || c == 'B')) ||
      (d == 'V' && c == 'O') ||
      (d == 'O' && c == 'G') ||
      (d == 'V' && c == 'G') ||
      (c == 'V' && d == 'O') ||
      (c == 'O' && d == 'G') ||
      (c == 'V' && d == 'G');
}

string expand(char c)
{
   if (c == 'O') return "RY";
   if (c == 'V') return "RB";
   if (c == 'G') return "BY";
   return boost::lexical_cast<string>(c);
}

int to_index(char c)
{
   if (c == 'R') return 0;
   if (c == 'B') return 1;
   if (c == 'Y') return 2;
   return -1;
}

int main()
{
   cout.precision(12);
   int ntc;
   cin >> ntc;

   FORN(kk, ntc)
   {
      print_case(kk);
      int n;
      cin >> n;
      vector<char> stalls(n, '_');
      vector<pair<int, char>> horses(6);
      vector<pair<int, char>> feat(3);
      feat[0].second = 'R';
      feat[1].second = 'B';
      feat[2].second = 'Y';
      string names = "ROYGBV";
      FORN(i, 6)
      {
         cin >> horses[i].first;
         horses[i].second = names[i];
         string s = expand(names[i]);
         FORN(j, s.length())
         {
            feat[to_index(s[j])].first += horses[i].first;
         }
      }
      bool possible = true;

      auto m = max_element(feat.begin(), feat.end());
      int toAdd = to_index(m->second);
      int realAdd = -1;
      int realAddCnt = -1;
      FORN(j, 6)
      {
         if (clashes(feat[toAdd].second, horses[j].second) && horses[j].first > 0)
         {
            string s = expand(horses[j].second);
            int total = 0;
            FORN(k, s.length())
            {
               total += feat[to_index(s[k])].first;
            }
            if (total > realAddCnt)
            {
               realAdd = j;
               realAddCnt = total;
            }
         }
      }

      stalls[0] = horses[realAdd].second;
      horses[realAdd].first--;
      string s = expand(horses[realAdd].second);
      FORN(k, s.length())
      {
         feat[to_index(s[k])].first--;
      }

      REP(i, 1, n - 1)
      {
         int toAdd = -1;
         int toAddCnt = -1;
         FORN(j, 3)
         {
            if ((feat[j].first > toAddCnt || (feat[j].first == toAddCnt && clashes(feat[j].second, stalls[0]))) &&
               !clashes(feat[j].second, stalls[i - 1]))
            {
               toAdd = j;
               toAddCnt = feat[j].first;
            }
         }

         if (toAdd == -1)
         {
            possible = false;
            break;
         }
         else
         {
            int realAdd = -1;
            int realAddCnt = -1;
            FORN(j, 6)
            {
               if (clashes(feat[toAdd].second, horses[j].second) && horses[j].first > 0 && !clashes(horses[j].second, stalls[i - 1]))
               {
                  string s = expand(horses[j].second);
                  int total = 0;
                  FORN(k, s.length())
                  {
                     total += feat[to_index(s[k])].first;
                  }
                  if (total > realAddCnt)
                  {
                     realAdd = j;
                     realAddCnt = total;
                  }
               }
            }
            if (realAdd != -1)
            {
               stalls[i] = horses[realAdd].second;
               horses[realAdd].first--;
               string s = expand(horses[realAdd].second);
               FORN(k, s.length())
               {
                  feat[to_index(s[k])].first--;
               }
            }
            else
            {
               possible = false;
               break;
            }
         }
      }

      if (possible)
      {
         m = max_element(horses.begin(), horses.end());
         if (!clashes(stalls[n - 2], m->second) && !clashes(stalls[0], m->second))
         {
            stalls[n - 1] = m->second;
            m->first--;
         }
         else
         {
            possible = false;
         }
      }

      if (possible)
      {
         FORN(i, n)
         {
            cout << stalls[i];
         }
         cout << endl;
      }
      else
      {
         cout << "IMPOSSIBLE" << endl;
      }
   }
}
