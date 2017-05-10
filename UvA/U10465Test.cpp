//
//  main.cpp
//  uva
//
//  Created by Ties de Kock on 5/24/13.
//  Copyright (c) 2013 Ties de Kock. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <algorithm>

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

using namespace std;

#define idx(x, y) ((m*y) + x)

typedef pair<int, int> int_t2;

int main(int argc, const char * argv[])
{
   int m, n, t;
    while (cin >> m >> n >> t) {
        
        
        vector<int_t2> subSums(t + 1);
        
        subSums[0] = int_t2(0, 0);
        
        // start from t=1 (!), include t_t
        for (int i=1; i <= t; i++) {
            // min (t-m, t-n | equal beer)
            bool valid_m = false, valid_n = false;
            int_t2 tm, tn;
            
            if (i - m >= 0) {
                valid_m = true;
                tm = subSums[i - m];
            }
            if (i - n >= 0) {
                valid_n = true;
                tn = subSums[i - n];
            }
            
            if (valid_m && valid_n) {
                // min (beer)
                if (tm.second == tn.second) {
                    if (tm.first > tn.first) {
                        subSums[i] = int_t2(tm.first + 1, tm.second);
                    } else {
                        subSums[i] = int_t2(tn.first + 1, tn.second);
                    }
                } else if (tm.second < tn.second) { // pick tn
                    subSums[i] = int_t2(tm.first + 1, tm.second);
                } else { // pick tm
                    subSums[i] = int_t2(tn.first + 1, tn.second);
                }
            } else {
                // 1 van de twee valid of linear scan
                
                if (valid_m) {
                    subSums[i] = int_t2(tm.first + 1, tm.second);
                } else if (valid_n) {
                    subSums[i] = int_t2(tn.first + 1, tn.second);
                } else {
                    // last + 1 + beer
                    int_t2 back = subSums[i-1];
                    
                    subSums[i] = int_t2(back.first, back.second + 1);
                }
            }
        }
        
        int_t2 res = subSums.back();
        
        // 0 bier: aantal burgers
        if (res.second == 0) {
            cout << res.first << endl;
        } else {
            cout << res.first << " " << res.second << endl;
        }
    }
    
    return 0;
}
