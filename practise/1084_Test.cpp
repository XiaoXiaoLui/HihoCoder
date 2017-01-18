#include<cstdio>
#include<cstring>
#include<algorithm>
#include <sys/time.h>
using namespace std;
const int Maxn=200005;
char  s[Maxn];
int n,sa[Maxn],h[Maxn],t1[Maxn],t2[Maxn],ra[Maxn],c[Maxn];
int d[Maxn][20];
/*
sa[i]：后缀数组里第i个是几号后缀
h[i]:后缀数组里第i个与前一个的最长公共前缀
ra[i]:sa[i]的逆数组，代表i号后缀排名第几
使用时要在结束加一个字符，且这个字符应表示0
*/
int ch[300];
bool cmp(int *y,int i,int k)
{
   return y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k];
}
void getsa()
{
   int m=30;
   int *x=t1,*y=t2;
   for(int i=0;i<m;i++)c[i]=0;
   for(int i=0;i<n;i++)c[x[i]=ch[s[i]]]++;
   for(int i=1;i<m;i++)c[i]+=c[i-1];
   for(int i=n-1;i>=0;i--)sa[--c[ch[s[i]]]]=i;
   for(int k=1;k<n;k<<=1)
   {
       int p=0;
       for(int i=n-k;i<n;i++)y[p++]=i;
       for(int i=0;i<n;i++)
            if(sa[i]>=k)
                y[p++]=sa[i]-k;
        for(int i=0;i<m;i++)c[i]=0;
        for(int i=0;i<n;i++)c[x[y[i]]]++;
        for(int i=1;i<m;i++)c[i]+=c[i-1];
        for(int i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(int i=1;i<n;i++)
           x[sa[i]]=cmp(y,i,k)?p-1:p++;
        if(p==n)break;
        m=p;
   }
}
void geth()
{
     for(int i=0;i<n;i++)ra[sa[i]]=i;
     int k=0;
     for(int i=0;i<n-1;i++)
     {
         if(k)k--;
         int j=sa[ra[i]-1];
         while(s[i+k]==s[j+k])k++;
         h[ra[i]]=k;
     }
     for(int i=0;i<n;i++)d[i][0]=h[i];
     for(int j=1;(1<<j)<=n;j++)
        for(int i=0;i+(1<<j)-1<n;i++)
           d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);
}
int ls1,ls2,K;
int getrmq(int l,int r)
{
   if(l>r)swap(l,r);
   l++;
   int k=0;
   while((1<<k+1)<=r-l+1)k++;
   return min(d[l][k],d[r-(1<<k)+1][k]);
}
bool check(int loc)
{
   if(loc+ls2-1>=ls1)return false;
   int l=loc,r=ls1+1;
   for(int t=K;t>=0;t--)
   {
      int tt=getrmq(ra[l],ra[r]);
      l+=tt;r+=tt;
      if(r>=n-1)return true;
      l++;r++;
   }
   return false;
}
void solve()
{
    int ans=0;
    for(int i=0;i<ls1;i++)
       if(check(i))
          ans++;
    printf("%d\n",ans);
}

/*
cabcbc
bc
1
*/
int main()
{
	freopen("1.txt", "r", stdin);
	timeval startTime, endTime;
	gettimeofday(&startTime, 0);
	
	
    ch['A']=0;
    for(int i='a';i<='z';i++)ch[i]=i-'a'+1;
    ch['#']=28;
    while(scanf("%s",s)!=EOF)
    {
       n=strlen(s);
       ls1=n;
       s[n++]='#';
       scanf("%s",s+n);
       n=strlen(s);
       s[n++]='A';
       scanf("%d",&K);
       ls2=n-ls1-2;
       getsa();
       geth();
       //for(int i=0;i<n;i++)printf("%d ",sa[i]);
       solve();
    }
	
	gettimeofday(&endTime, 0);
	double useTime = 1e6 * (endTime.tv_sec - startTime.tv_sec) + endTime.tv_usec - startTime.tv_usec;
	useTime /= 1e3;
	
	printf("TIME:%.0lf\n", useTime);
    return 0;
}
