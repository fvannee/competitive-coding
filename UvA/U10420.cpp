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
   map<string, int> women;
   for (int i = 0; i < ntc; i++)
   {
      string word;
      cin >> word;
      women[word]++;
      getline(cin, word);
   }
   for (map<string, int>::iterator it = women.begin(); it != women.end(); it++)
   {
      cout << it->first << " " << it->second << endl;
   }
   return 0;
}
