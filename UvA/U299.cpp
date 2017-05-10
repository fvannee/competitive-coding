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

int bubble_sort(vector<int> ns)
{
	int count = 0;
	for (int i = 0; i < ns.size(); i++)
	{
		for (int j = 0; j < ns.size() - 1; j++)
		{
			if (ns[j] > ns[j + 1])
			{
				swap(ns[j], ns[j + 1]);
				count++;
			}
		}
	}
	return count;
}

int main() {
  int ntc;
  cin >> ntc;
  for (int i = 0; i < ntc; i++)
  {
	  int n;
	  cin >> n;
	  vector<int> ns(n);
	  for (int j = 0; j < n; j++)
	  {
		  cin >> ns[j];
	  }
	  int ans = bubble_sort(ns);
	  printf("Optimal train swapping takes %d swaps.\n", ans);
  }
  return 0;
}
