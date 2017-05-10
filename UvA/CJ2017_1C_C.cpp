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

#define M_PI           3.14159265358979323846  /* pi */

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

bool almost_equal(double a, double b)
{
   return abs(a - b) < EPS;
}

double calc_failure(vector<double> vc)
{
   double prob = 1.0;
   FORN(i, vc.size())
   {
      prob *= vc[i];
   }
   return prob;
}

vi failureTable(51);

int targetNumSuccesses = 0;
vector<double> successChances(50);
int numEvents = 50;
int totalNumEvents = 50;

void resetFailureTable()
{
   FORN(i, failureTable.size())
      failureTable[i] = 0;
}

void reverseSubList(vi& list, int front, int back)
{
   if (front > back)
      swap(front, back);
   reverse(list.begin() + front, list.begin() + back + 1);
}

void calcu()
{
   double numEventProbability = 0;
   double totalProbability = 0;
   bool exhausted = false;

   for (numEvents = 1; numEvents <= (totalNumEvents - targetNumSuccesses); numEvents++)
   {
      resetFailureTable();
      FORN(i, numEvents)
         failureTable[i] = 1;

      while (!exhausted)
      {
         double eventChainProbability = 1;
         REP(subEvent, 1, numEvents + 1)
         {
            if (failureTable[subEvent - 1])
               eventChainProbability = eventChainProbability*(1 - successChances[subEvent - 1]);
            else
               eventChainProbability = eventChainProbability*(successChances[subEvent - 1]);
         }
         numEventProbability = numEventProbability + eventChainProbability;

         for (int i = totalNumEvents - 1; i >= 0; i--)
         {
            if (failureTable[i] && !failureTable[i + 1])
            {
               int rightmost;
               for (int j = totalNumEvents - 1; j >= 0; j--) {
                  if (!failureTable[j]) {
                     rightmost = j; break;
                  }
               }

               failureTable[i] = false;
               failureTable[rightmost] = true;
               reverseSubList(failureTable, i + 1, totalNumEvents - 1);
               break;
            }
            else if (i == 1)
               exhausted = true;
         }
      }

      exhausted = false;
      printf("Odds of being exactly %d failures: %.2f", numEvents, numEventProbability);
      totalProbability = totalProbability + numEventProbability;
      numEventProbability = 0;
   }

   printf("Odds of at least %d successes: %f", targetNumSuccesses, 1 - totalProbability);
}

int main()
{
   /*numEvents = 2;
   totalNumEvents = 2;
   targetNumSuccesses = 1;
   successChances[0] = 0.4000;
   successChances[1] = 0.6000;
   calcu();*/

   cout.precision(12);
   int ntc;
   cin >> ntc;

   FORN(kk, ntc)
   {
      print_case(kk);
      int n, k;
      cin >> n >> k;
      double units;
      cin >> units;
      vector<double> cores(n + 1);
      cores[n] = 1.0;
      FORN(i, n)
      {
         cin >> cores[i];
      }

      sort(cores.begin(), cores.end());

      FORN(i, n)
      {
         int nrcoresequal = 1;
         REP(j, 1, n)
         {
            if (!almost_equal(cores[i], cores[j]))
            {
               break;
            }
            nrcoresequal++;
         }
         double nextcore = cores[nrcoresequal];
         double diff = nextcore - cores[0];
         double tospend = min(units, nrcoresequal * diff);
         FORN(j, nrcoresequal)
         {
            cores[j] += tospend / nrcoresequal;
         }
         units -= tospend;
      }

      cout << calc_failure(cores) << endl;
   }
}
