#include<stdio.h>
#include<algorithm>
#include<queue>
#include<string.h>
using namespace std;
const int N=5505,M=N<<3,Inf=1e9;

int Tote=1,Last[N],Next[M],End[M],V[M],Len[M],From[M];
void Ins(int x,int y,int z,int d){
	End[++Tote]=y;
	From[Tote]=x;
	V[Tote]=z;
	Len[Tote]=d;
	Next[Tote]=Last[x];
	Last[x]=Tote;

	End[++Tote]=x;
	From[Tote]=y;
	Len[Tote]=-d;
	Next[Tote]=Last[y];
	Last[y]=Tote;
}
int n,K,S,T;
queue<int>q;
int Dis[N],Vis[N],Path[N];
bool Spfa(){
	int x,u,i;
	memset(Dis,0x3f,sizeof(Dis));
	memset(Vis,0,sizeof(Vis));
	q.push(S),Dis[S]=0;
	while(!q.empty()){
		x=q.front(),q.pop();
		Vis[x]=0;
		for(i=Last[x];i;i=Next[i])
			if(V[i]&&Dis[u=End[i]]>Dis[x]+Len[i]){
				Dis[u]=Dis[x]+Len[i];
				Path[u]=i;
				if(!Vis[u])Vis[u]=1,q.push(u);
			}
	}
	return Dis[T]<Inf;
}
int Ans,MaxFlow;
void AddFlow(){
	int i,u,flow=Inf,cost=0;
	for(i=T;i!=S;i=From[u]){
		u=Path[i];
		flow=min(flow,V[u]);
		cost+=Len[u];
	}
	Ans+=cost;
	MaxFlow+=flow;
	for(i=T;i!=S;i=From[u]){
		u=Path[i];
		V[u]-=flow,V[u^1]+=flow;
	}
}
int main(){
	int i,j,k,x;
	scanf("%d%d",&n,&K);
	S=n*n*2+1,T=S+1;
	Ins(S,1,K,0);
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++){
			scanf("%d",&x);
			k=(i-1)*n+j;
			Ins(k,k+n*n,1,-x);
			Ins(k,k+n*n,Inf,0);
			int tx=i+1,ty=j;
			if(tx<=n&&ty<=n)Ins(k+n*n,(tx-1)*n+ty,Inf,0);
			tx=i,ty=j+1;
			if(tx<=n&&ty<=n)Ins(k+n*n,(tx-1)*n+ty,Inf,0);
		}
	Ins(n*n*2,T,K,0);
	while(Spfa())AddFlow();
	printf("%d",-Ans);
}
