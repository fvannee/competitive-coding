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
   while (!cin.eof())
   {
      getline(cin, in);
      int count = 0;
      bool wordStarted = false;
      for (string::iterator it = in.begin(); it != in.end(); it++)
      {
         bool isChar = isalpha(*it);
         if (!wordStarted && isChar)
         {
            wordStarted = true;
            count++;
         }
         else if (wordStarted && !isChar)
         {
            wordStarted = false;
         }
      }
      if (count != 0)
         cout << count << endl;
   }
   return 0;
}
