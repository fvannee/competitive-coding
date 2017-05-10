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
typedef vector<int> vint;

int main() {
   int ntc;
   cin >> ntc;
   for (int i = 0; i < ntc; i++)
   {
      int f;
      cin >> f;
      double budget = 0.0;
      for (int j = 0; j < f; j++)
      {
         int size, animals, friendliness;
         cin >> size >> animals >> friendliness;
         double avg = ((double)size) / animals;
         budget += avg * friendliness * animals;
      }
      cout << (int)budget << endl;
   }
   return 0;
}
