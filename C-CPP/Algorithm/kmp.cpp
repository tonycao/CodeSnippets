#include <iostream>
#include <string>

using namespace std;

void get_nextval(const char *T, int next[])
{
       // 求模式串T的next函数值并存入数组 next。
 int j = 0, k = -1;
 next[0] = -1;
  while ( T[j] != '\0' )
   {
  if (k == -1 || T[j] == T[k])
  {
   ++j; ++k;
   if (T[j]!=T[k])
    next[j] = k;
  else
    next[j] = next[k];
    }// if
    else
        k = next[k];
    }// while
    ////这里是我加的显示部分
       for(int i=0;i<j;i++)
       {
         cout<<next[i]<<" ";
       }
       cout<<endl;
}// get_nextval　

//另一种写法，也差不多。
void getNext(const char* pattern,int next[])
{
 next[0]=   -1;
 int k=-1,j=0;
 while(pattern[j] != '\0')
 {
  if(k!= -1 && pattern[k]!= pattern[j] )
   k=next[k];
 ++j;++k;
 if(pattern[k]== pattern[j])
   next[j]=next[k];
 else
   next[j]=k;
}
       ////这里是我加的显示部分
for(int i=0;i<j;i++)
{
  cout<<next[i]<<" ";
}
cout<<endl;
}


int KMP(const char *Text,const char* Pattern) //const 表示函数内部不会改变这个参数的值。
{
       if( !Text||!Pattern|| Pattern[0]=='\0' || Text[0]=='\0' )//
              return -1;//空指针或空串，返回-1。
            int len=0;
            const char * c=Pattern;
       while(*c++!='\0')//移动指针比移动下标快。
       {
              ++len;//字符串长度。
            }
            int *next=new int[len+1];
       get_nextval(Pattern,next);//求Pattern的next函数值

       int index=0,i=0,j=0;
       while(Text[i]!='\0' && Pattern[j]!='\0' )
       {
        if(Text[i]== Pattern[j])
        {
                     ++i;// 继续比较后继字符
                     ++j;
                   }
                   else
                   {
                     index += j-next[j];
                     if(next[j]!=-1)
                            j=next[j];// 模式串向右移动
                          else
                          {
                            j=0;
                            ++i;
                          }
                        }
       }//while

       delete []next;
       if(Pattern[j]=='\0')
              return index;// 匹配成功
            else
              return -1;
          }


int main()//abCabCad
{
 char* text = "bababCabCadcaabcaababcbaaaabaaacababcaabc";
 //char* pattern = "adCadCad";
 char* pattern = "aaaaaaaaaab";
 int sz = strlen(pattern);
 int *n = new int[sz];
 getNext(pattern,n);
 get_nextval(pattern,n);
 cout<<KMP(text,pattern)<<endl;
 return 0;
}
