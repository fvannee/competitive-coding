#include <stdio.h>
#include <string.h>

#include <vector>
#include <string>
#include <algorithm>

class EllysSortingTrimmer
{
public:
   std::string getMin(std::string S, int L)
   {
      
      int start = S.size() - L;
      while (start >= 0)
      {
         std::sort(S.begin() + start, S.begin() + start + L);
         start--;
      }
      return S.substr(0, L);
   }
};

void disp(char* str)
{
   printf("'%s'\r\n", str);
   return;
}

void vuln_func(char* arg)
{
   void(*ptr)(char*);
   char buf[128];

   ptr = (void(*)(char*))disp;

   printf("%p\n", ptr);
   printf("%p\n", buf);

   printf("%p\n", &ptr);
   printf("%p\n", buf);


   strcpy(buf, arg);
   ptr(buf);
   return;
}

using namespace std;

int missingno(const vector<int>& vi)
{
   int c = 0;
   for (int i = 0; i < vi.size(); i++)
   {
      c ^= vi[i];
   }
   return c;
}

int main() {

   vector<int> vi;
   for (int i = 0; i < 20; i++)
   {
      vi.push_back(i);
   }
   int a = missingno(vi);

   return 0;
}
