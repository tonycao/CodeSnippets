#include<iostream.h>   
      #include<search.h>   
      short r,c,n,max,dx,dy,len,cx,cy,i,j;   
      struct Point{   
          short x,y;   
      }p[5000];   
      bool table[5000][5000];   
      int com(const void *a,const void *b)   
      {   
           if(((Point*)a)->x>((Point*)b)->x)return 1;   
           if(((Point*)a)->x<((Point*)b)->x)return -1;   
           return ((Point*)a)->y-((Point*)b)->y;   
      }   
      void main()   
      {   
          cin>>r>>c>>n;   
          for(i=0;i<n;i++)   
          {   
              cin>>p[i].x>>p[i].y;   
              p[i].x--;p[i].y--;   
              table[p[i].x][p[i].y]=true;   
          }   
          qsort(p,n,sizeof(Point),com);   
          for(i=0;i<n;i++)   
              for(j=i+1;j<n;j++)   
              {   
                  dx=p[j].x-p[i].x;   
                  dy=p[j].y-p[i].y;   
                  cx=p[i].x-dx;cy=p[i].y-dy;   
                  if(cx>=0&&cy>=0&&cy<c)continue;   
                  if(dx && dx*max>r)continue;   
                  if(dy && (dy*max>c || -dy*max>c))continue;   

                  cx=p[j].x+dx;cy=p[j].y+dy;   
                  len=2;   
                  while(cy>=0&&cx<r&&cy<c)   
                  {   
                      if(!table[cx][cy])goto next;   
                      len++;   
                      cx+=dx;cy+=dy;   
                  }   
                  if(len>=3&&len>max)max=len;               
      next:;   
              }   
          cout<<max<<endl;   
      }   