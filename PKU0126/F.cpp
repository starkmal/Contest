#include<stdio.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
const int N=1000005;
const ll Infl=4e18;

int Q,n,m;

int Tote,Last[N],Next[N],End[N];
ll Len[N];
void Ins(int x,int y,ll z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}
int Tote2,Last2[N],Next2[N],End2[N];
ll Len2[N];
void Ins2(int x,int y,ll z){
	End2[++Tote2]=y;
	Len2[Tote2]=z;
	Next2[Tote2]=Last2[x];
	Last2[x]=Tote2;
}
queue<int>q;
ll Dis[N];
bool Vis[N];
ll Dijstra(){
	int i,x,u;
	for(i=1;i<=n;i++)Dis[i]=Infl,Vis[i]=0;
	q.push(1),Vis[1]=1,Dis[1]=0;
	while(!q.empty()){
		x=q.front(),q.pop(),Vis[x]=0;
		for(i=Last[x];i;i=Next[i])
			if(Dis[u=End[i]]>Dis[x]+Len[i]){
				Dis[u]=Dis[x]+Len[i];
				if(!Vis[u])Vis[u]=1,q.push(u);
			}
	}
	ll rt=0;
	for(i=1;i<=n;i++)rt+=Dis[i];
	return rt;
}
ll spfa(){
	int i,x,u;
	for(i=1;i<=n;i++)Dis[i]=Infl,Vis[i]=0;
	q.push(1),Vis[1]=1,Dis[1]=0;
	while(!q.empty()){
		x=q.front(),q.pop(),Vis[x]=0;
		for(i=Last2[x];i;i=Next2[i])
			if(Dis[u=End2[i]]>Dis[x]+Len2[i]){
				Dis[u]=Dis[x]+Len2[i];
				if(!Vis[u])Vis[u]=1,q.push(u);
			}
	}
	ll rt=0;
	for(i=1;i<=n;i++)rt+=Dis[i];
	return rt;
}
int main(){
	int i,j,k,x,y;ll z;
	scanf("%d",&Q);
	while(Q--){
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++){
			scanf("%d%d%lld",&x,&y,&z);
			Ins(x,y,z);
			Ins2(y,x,z);
		}
		printf("%lld\n",Dijstra()+spfa());
		Tote=Tote2=0;
		for(i=1;i<=n;i++)Last[i]=Last2[i]=0;
	}
}
