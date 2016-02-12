// #include <iostream>
// //#include <conio.h>

// using namespace std;

// class Solution {
// public:
// bool isMultiple (string s){
//     int N=s.size();
//     if(N<4) return false;
//     int len=1;
//     int start=0;
//     for(int i=1;i<N;++i){
//         if(s[start]==s[i]){
//             start++;
//             if(start>=len) start=0;
//         }
//         else{
//             len++;
//             i=len-1; // start from len
//             start=0;
//         }
//         if(len>N/2) return false;
//     }
//     return len!=1 && (N % len == 0);
// }
// };

// int main() {
//     Solution sol;
//     cout<<sol.isMultiple("abcabcabc")<<"     "<<"1"<<endl;
//     cout<<sol.isMultiple("bcdbcdbcde")<<"     "<<"0"<<endl;
//     cout<<sol.isMultiple("abcdabcd" )<<"     "<<"1"<<endl;
//     cout<<sol.isMultiple("xyz")<<"     "<<"0"<<endl;
//     cout<<sol.isMultiple("aaaaaaaaaa")<<"     "<<"0"<<endl;
//     //getch();
//     return 0;
// }

#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;
int main(int argc, char* argv[])
{
cout<<"Please input a string"<<endl;

string InputStr;

cin>>InputStr;



string subStr;
int i = InputStr.length()-1;
while(i>0)
{
  subStr=InputStr.substr(i);

  for(int j=i-1;j>=0;j--)
   {
     if(InputStr[j]!=subStr[(j%subStr.length())])
         {
        i=j;
                break;
         }
    if(j==0)
      {
        //Done should be a true if size is bigger than 2 and less than half
        if((subStr.size()>=2)&&(subStr.size()<InputStr.size()/2+1))
          {
             cout<<"Yes true"<<endl;
             return 0;
          }
    else
      {
           cout<<"No false"<<endl;
             return 0;
      }

      }
   }

}

cout<<"No false"<<endl;
return 0;
}
