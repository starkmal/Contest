#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#define int long long 
using namespace std;
const int Inf=1e9;
inline int _R(){
	int d=0;bool b=1;char t=getchar();
	while(!isdigit(t))b=t=='-'?0:1,t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return b?d:-d;
}

int T,n,t;
struct Node{
	int x,y,z,cost[5];
}A[11];
int ans,vis[11];
bool Judge(int i,int j,int k){
	Node a,b;
	a.x=A[j].x-A[i].x,a.y=A[j].y-A[i].y,a.z=A[j].z-A[i].z;
	b.x=A[k].x-A[j].x,b.y=A[k].y-A[j].y,b.z=A[k].z-A[j].z;
	return (a.x*a.x*b.x*b.x+a.y*a.y*b.y*b.y+a.z*a.z*b.z*b.z)/
			((a.x*a.x+a.y*a.y+a.z*a.z)*(b.x*b.x+b.y*b.y+b.z*b.z))==1;
}
void Dfs(int d,int x){
	if(d>t){
		for(register int i=1;i<=n;i++)
			if(!vis[i])return;
		ans=max(ans,x);
	}
	for(register int i=1;i<=n;i++)if(!vis[i]){
		vis[i]=d;
		Dfs(d+1,x+A[i].cost[d]);
		vis[i]=0;
	}
	for(register int i=1;i<=n;i++)if(!vis[i])
		for(register int j=1;j<=n;j++)if(!vis[j]){
			register int tmp=x;
			for(register int k=1;k<=n;k++)if(!vis[k])
				if(Judge(i,j,k))tmp+=A[k].cost[d],vis[k]=d;
			Dfs(d+1,tmp);
			for(register int k=1;k<=n;k++)
				if(vis[k]==d)vis[k]=0;
		}
}
main(){
	int i,j,k;
	T=_R();
	while(T--){
		n=_R(),t=_R();
		for(i=1;i<=n;i++)
			A[i].x=_R(),A[i].y=_R(),A[i].z=_R();
		for(i=1;i<=n;j++)
			for(j=1;j<=t;j++)
				A[i].cost[j]=_R();
		ans=-Inf;
		Dfs(1,0);
		if(ans==-Inf)puts("-1");
		else printf("%lld\n",ans);
	}
}
