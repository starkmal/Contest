#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<map>
using namespace std;
const int N=105;
inline int _R(){
	int d=0;bool b=1;char t=getchar();
	while(!isdigit(t))b=t=='-'?0:1,t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return b?d:-d;
}

int n,m,t,a[N];
map<int,int>In[N],Out[N];
typedef map<int,int>::iterator mi;
bool Check(int x){
	for(mi it=In[x].begin();it!=In[x].end();it++)
		if(a[it->first]<it->second)return 0;
	return 1;
}
bool Work(){
	for(int i=1;i<=m;i++){
		if(!Check(i))continue;
		for(mi it=In[i].begin();it!=In[i].end();it++)
			a[it->first]-=it->second;
		for(mi it=Out[i].begin();it!=Out[i].end();it++)
			a[it->first]+=it->second;
		return 1;
	}
	return 0;
}
int main(){
	int i,j=0,k,x,y;
	while((n=_R())!=0){
		j++;
		for(i=1;i<=n;i++)a[i]=_R();
		m=_R();
		for(i=1;i<=m;i++){
			In[i].clear();
			Out[i].clear();
			while((x=_R())!=0)
				if(x<0)In[i][-x]++;
				else Out[i][x]++;
		}
		t=_R();

		printf("Case %d: ",j);
		for(k=0;k<t;k++)
			if(!Work())break;
		if(k>=t)printf("still live after %d transitions\n",t);
		else printf("dead after %d transitions\n",k);
		printf("Places with tokens:");
		for(i=1;i<=n;i++)
			if(a[i])printf(" %d (%d)",i,a[i]);
		puts("");
		puts(""); 
	}
}
