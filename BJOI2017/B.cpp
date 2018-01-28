#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=200005,Inf=1e9;
const ll Infl=9e18;

int n,m,L,R;
ll a[N];
typedef pair<int,int> pii;
typedef vector<pii>::iterator vi;
vector<pii>G[N];

#define nd now->second
#define FOR(x) for(vi now=G[x].begin();now!=G[x].end();now++)
int Minn,Rt,sz[N];
bool Vis[N];
void Getsz(int x,int fa){
	sz[x]=1;
	FOR(x)if(nd!=fa&&!Vis[nd])
		Getsz(nd,x),sz[x]+=sz[nd];
}
void GetG(int x,int tot,int fa){
	int Maxx=tot-sz[x];
	FOR(x)if(nd!=fa&&!Vis[nd])
		GetG(nd,tot,x),Maxx=max(Maxx,sz[nd]);
	if(Maxx<Minn)Minn=Maxx,Rt=x;
}
void GetRt(int x){
	Minn=Inf;
	Getsz(x,0);
	GetG(x,sz[x],0);
}

ll Max1[N],Max2[N];
int h2,t2,s[N];
int hd,tl,q[N],Dep[N],Last[N],Fa[N];
ll Dis[N],ans=-Infl;
void GetAns(int x){
	int MaxLen=0,MaxRt=0,Cl=0,i,j,k,u,v;
	sort(G[x].begin(),G[x].end());
	FOR(x)if(!Vis[nd]){
		if(now->first!=Cl){
			for(i=MaxLen+1;i<=MaxRt;i++)Max1[i]=-Infl;
			for(i=1;i<=MaxRt;i++)Max1[i]=max(Max1[i],Max2[i]);
			Cl=now->first;
			MaxLen=max(MaxLen,MaxRt);
			MaxRt=0;
		}
		
		hd=tl=1;
		q[1]=nd,Fa[nd]=x,Last[nd]=now->first;
		Dis[nd]=a[now->first],Dep[nd]=1;
		while(hd<=tl){
			u=q[hd++];
			for(vi it=G[u].begin();it!=G[u].end();it++)
				if(Fa[u]!=it->second&&!Vis[it->second]){
					v=it->second;
					Fa[v]=u;
					Dep[v]=Dep[u]+1;
					Dis[v]=Dis[u];
					if(it->first!=Last[u])
						Dis[v]+=a[it->first];
					Last[v]=it->first;
					q[++tl]=v;
				}
		}
		
		//中间段不同
		h2=1,t2=0,v=MaxLen;		//当前路径长度递增，v从大到小
		for(i=1;i<=tl;i++){
			u=q[i];
			while(v>=0&&v+Dep[u]>=L){
				while(h2<=t2&&Max1[s[t2]]<=Max1[v])t2--;
				s[++t2]=v;
				v--;
			}
			while(h2<=t2&&s[h2]+Dep[u]>R)h2++;
			if(h2<=t2)ans=max(ans,Dis[u]+Max1[s[h2]]);
		}
		//中间段相同
		h2=1,t2=0,v=MaxRt;
		for(i=1;i<=tl;i++){
			u=q[i];
			while(v>0&&v+Dep[u]>=L){
				while(h2<=t2&&Max2[s[t2]]<=Max2[v])t2--;
				s[++t2]=v;
				v--;
			}
			while(h2<=t2&&s[h2]+Dep[u]>R)h2++;
			if(h2<=t2)ans=max(ans,Dis[u]+Max2[s[h2]]-a[Cl]);
		}
		for(i=MaxRt+1;i<=Dep[q[tl]];i++)Max2[i]=-Infl;
		for(i=1;i<=tl;i++)Max2[Dep[q[i]]]=max(Max2[Dep[q[i]]],Dis[q[i]]);
		MaxRt=max(MaxRt,Dep[q[tl]]);
	}
}
void DC(int x){
	Vis[x]=1;
	GetAns(x);
	FOR(x)if(!Vis[nd]){
		GetRt(nd);
		DC(Rt);
	}
}
int main(){
	int i,j,k,x,y;
	scanf("%d%d%d%d",&n,&m,&L,&R);
	for(i=1;i<=m;i++)scanf("%lld",&a[i]);
	for(i=1;i<n;i++){
		scanf("%d%d%d",&x,&y,&k);
		G[x].push_back(pii(k,y));
		G[y].push_back(pii(k,x));
	}
	GetRt(1);
	DC(Rt);
	printf("%lld",ans);
}
