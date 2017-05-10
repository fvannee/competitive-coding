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
   string in;
   bool first = true;
   while (true)
   {
      getline(cin, in, '"');
      cout << in;
      if (!cin.eof())
         cout << (first ? "``" : "''");
      else
         break;
      first = !first;
   }
   return 0;
}
