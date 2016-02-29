#include<iostream>
#include<string.h>
typedef struct{
    int arr[255];
    int s;
}martrix;

martrix chengfa(martrix A,martrix B){
    int cw,jw,a[255],b[255],c[255],d[255],ds,T,cc,ca,cb,i,j,k,p;
    martrix shu;
    ca=A.s;cb=B.s;
    for(i=1;i<=A.s;i++)
        a[i]=A.arr[i];
    for(i=1;i<=B.s;i++)
        b[i]=B.arr[i];
    memset(c,0,sizeof(c));
    memset(d,0,sizeof(d));
    
    cw=1;
    for(i=1;i<=cb;i++){
        jw=0;
        for(j=1;j<=ca;j++){
            d[j]=(a[j]*b[i]+jw)%10000;
            jw=(a[j]*b[i]+jw)/10000;
        }
        if(jw!=0){
            d[j]=jw;
            ds=j;
        }
        else ds=j-1;
        jw=0;
        for(k=cw,p=1;p<=ds;p++,k++){
            T=d[p]+c[k]+jw;
            c[k]=T%10000;
            jw=T/10000;
        }
        if(jw!=0){
            c[k]=jw;
            cc=k;
        }
        else cc=k-1;
        cw++;
    }
    shu.s=cc;
    for(i=1;i<=cc;i++)
        shu.arr[i]=c[i];
    return shu;
}
int main(){
    char s1[255],s2[255];
    int n,i,j,k,L,xs,f;
    memset(s1,'\0',sizeof(s1));
    memset(s2,'\0',sizeof(s2));
    while(scanf("%s%d",s1,&n)!=EOF){
        L=strlen(s1);
        for(i=0;i<L;i++){
            if(s1[i]=='.')
                break;
        }
        if(i>=L){
            s1[L++]='.';
            s1[L]='\0';
        }
        for(i=0;i<L;i++){
            if(s1[i]!='0'||s1[i]=='.')
                break;
        }
        
        for(j=L-1;j>=0;j--){
            if(s1[j]!='0'||s1[j]=='.')
                break;
        }
                
        xs=0;f=1;
        for(k=0;i<=j;i++){
            if(s1[i]!='.'&&f){
                xs++;
            }
            else
                f=0;
            s2[k++]=s1[i];
        }
        s2[k]='\0';
        
        xs=strlen(s2)-xs-1;
        xs=xs*n;
        
        int a[255],t[255],c;
        martrix g,h;
        L=strlen(s2);
        for(i=L-1,k=1;i>=0;i--){
            if(s2[i]!='.'){
                a[k++]=s2[i]-48;
            }
        }

        for(k=1,i=1;(i+4)<=L-1;i+=4)
            t[k++]=a[i]+a[i+1]*10+a[i+2]*100+a[i+3]*1000;
        c=L-i;
        if(c!=0){
            if(c==1) t[k]=a[i];
            if(c==2) t[k]=a[i]+a[i+1]*10;
            if(c==3) t[k]=a[i]+a[i+1]*10+a[i+2]*100;
            if(c==4) t[k]=a[i]+a[i+1]*10+a[i+2]*100+a[i+3]*1000;
            g.s=k;    
        }
        else g.s=k-1;    
        for(i=1;i<=g.s;i++)
            g.arr[i]=t[i];
        h=g;
        for(i=1;i<n;i++)
            g=chengfa(g,h);
        
        
        char ch[255]={'\0'};
        sprintf(ch,"%d",g.arr[g.s]);
        for(i=g.s-1;i>=1;i--){
            if(g.arr[i]<10) sprintf(ch,"%s000%d",ch,g.arr[i]);
            else if(g.arr[i]<100) sprintf(ch,"%s00%d",ch,g.arr[i]);
            else if(g.arr[i]<1000) sprintf(ch,"%s0%d",ch,g.arr[i]);
            else sprintf(ch,"%s%d",ch,g.arr[i]);
        }
    
        
        if((int)strlen(ch)>xs){
            for(k=0;k<(int)strlen(ch);k++){
                if((int)strlen(ch)-k==xs)
                    printf(".");
                printf("%c",ch[k]);
            }
        }
        else{
            printf(".");
            for(i=1;i<=xs-(int)strlen(ch);i++)
                printf("0");
            for(i=0;i<(int)strlen(ch);i++)
                printf("%c",ch[i]);
        }
        
        printf("\n");
        memset(s1,'\0',sizeof(s1));
        memset(s2,'\0',sizeof(s2));
    }
}
