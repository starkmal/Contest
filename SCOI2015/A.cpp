#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=505,M=200005;

int n,m,K,A[N][N];
int S,T,Tote=1,Last[N<<1],Next[M],End[M],V[M];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	V[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;

	End[++Tote]=x;
	V[Tote]=0;
	Next[Tote]=Last[y];
	Last[y]=Tote;
}
int Dis[N],Cnt[N];
int Sap(int x,int flow){
	if(x==T)return flow;
	int d=0,tmp,u,i;
	for(i=Last[x];i;i=Next[i])
		if(V[i]&&Dis[x]==Dis[u=End[i]]+1){
			tmp=Sap(u,min(V[i],flow-d));
			d+=tmp,V[i]-=tmp,V[i^1]+=tmp;
			if(d==flow||Dis[S]>=T)return d;
		}
	if(Dis[S]>=T)return d;
	if(--Cnt[Dis[x]]==0)Dis[S]=T;
	Cnt[++Dis[x]]++;
	return d;
}
bool Check(int x){
	register int i,j,k,tot=0;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(A[i][j]<=x)Ins(i,j+n,1);
	for(i=1;i<=n;i++)Ins(S,i,1);
	for(i=1;i<=m;i++)Ins(i+n,T,1);
	while(Dis[S]<T)tot+=Sap(S,1e9);
	printf("%d %d\n",Tote,tot);
	Tote=1;
	for(i=1;i<=T;i++)Last[i]=Dis[i]=Cnt[i]=0;
	return tot>=n-K+1;
}
int main(){
	freopen("dataA/matrix5.in","r",stdin);
	register int i,j,k;
	int L=1,R=0,Mid,Ans=0;
	scanf("%d%d%d",&n,&m,&K);
	S=n+m+1,T=S+1;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%d",&A[i][j]),R=max(R,A[i][j]);
	while(L<=R){
		Mid=(long long)(L+R)>>1;
		if(Check(Mid))Ans=Mid,R=Mid-1;
		else L=Mid+1;
	}
	printf("%d",Ans);
}
