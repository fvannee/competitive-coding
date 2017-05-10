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
      int lower[26] = {0};
      int upper[26] = {0};
      for (string::iterator it = in.begin(); it != in.end(); it++)
      {
         if (isupper(*it))
         {
            upper[*it - 65]++;
         }
         else if (islower(*it))
         {
            lower[*it - 97]++;
         }
      }
      vector<char> res;
      int m = 0;
      for (int i = 0; i < 26; i++)
      {
         if (upper[i] == m)
         {
            res.push_back(i + 65);
         }
         else if (upper[i] > m)
         {
            m = upper[i];
            res.clear();
            res.push_back(i + 65);
         }
      }

      for (int i = 0; i < 26; i++)
      {
         if (lower[i] == m)
         {
            res.push_back(i + 97);
         }
         else if (lower[i] > m)
         {
            m = lower[i];
            res.clear();
            res.push_back(i + 97);
         }
      }

      if (m > 0)
      {
         for (int i = 0; i < res.size(); i++)
         {
            cout << res[i];
         }
         cout << " " << m << endl;
      } 
   }
   return 0;
}
