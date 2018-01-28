#include<stdio.h>
#include<algorithm>
#include<stack>
#include<set>
using namespace std;
typedef long long ll;
const int N=2000005,M=N<<3;
const ll Mod=1e9+7;

int n;
ll X[N],R[N];

int Tote,Last[N],Next[M],End[M];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int Totn,Root,f[N],g[N];
int Son[N][2];
void Build(int &p,int l,int r){
	if(l<r){
		p=++Totn;
		g[p]=l,f[p]=r;
		int mid=l+r>>1;
		Build(Son[p][0],l,mid);
		Build(Son[p][1],mid+1,r);
		Ins(p,Son[p][0]);
		Ins(p,Son[p][1]);
	}else p=l,g[p]=f[p]=l;
}
void Link(int p,int l,int r,int x,int y,int k){
	if(x<=l&&r<=y){Ins(k,p);return;}
	int mid=l+r>>1;
	if(l<=y&&mid>=x)Link(Son[p][0],l,mid,x,y,k);
	if(mid<y&&r>=x)Link(Son[p][1],mid+1,r,x,y,k);
}

stack<int>s;
set<int>G[N];
int vtt,scc,Instack[N],Dfn[N],Low[N],Id[N],Min[N],Max[N];
void Tarjan(int x){
	Dfn[x]=Low[x]=++vtt;
	s.push(x),Instack[x]=1;
	int i,u;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		if(!Dfn[u])Tarjan(u),Low[x]=min(Low[x],Low[u]);
		else if(Instack[u])Low[x]=min(Low[x],Dfn[u]);
	}
	if(Low[x]==Dfn[x]){
		scc++;Min[scc]=n,Max[scc]=0;
		do{
			u=s.top(),s.pop();
			Instack[u]=0;
			Id[u]=scc;
			Min[scc]=min(Min[scc],g[u]);
			Max[scc]=max(Max[scc],f[u]);
		}while(u!=x);
	}
}
int d[N],Top[N];
typedef set<int>::iterator sit;
void DP(){
	int i,j,u,tot=0;
	while(!s.empty())s.pop();
	for(i=1;i<=scc;i++)
		for(sit it=G[i].begin();it!=G[i].end();it++)
			d[*it]++;
	for(i=1;i<=scc;i++)
		if(!d[i])s.push(i);
	while(!s.empty()){
		u=s.top(),s.pop();
		Top[++tot]=u;
		for(sit it=G[u].begin();it!=G[u].end();it++){
			d[*it]--;
			if(!d[*it])s.push(*it);
		}
	}
	for(i=scc;i>=1;i--){
		u=Top[i];
		f[u]=Max[u],g[u]=Min[u];
		for(sit it=G[u].begin();it!=G[u].end();it++)
			f[u]=max(f[u],f[*it]),g[u]=min(g[u],g[*it]);
	}
}
int main(){
	int i,j,k,x,y;
	scanf("%d",&n);
	Totn=n;
	for(i=1;i<=n;i++)scanf("%lld%lld",&X[i],&R[i]);
	Build(Root,1,n);
	for(i=1;i<=n;i++){
		x=lower_bound(X+1,X+1+n,X[i]-R[i])-X;
		y=upper_bound(X+1,X+1+n,X[i]+R[i])-X-1;
		if(x<i)Link(Root,1,n,x,i-1,i);
		if(y>i)Link(Root,1,n,i+1,y,i);
	}
	for(i=1;i<=Totn;i++)if(!Dfn[i])Tarjan(i);
	for(i=1;i<=Totn;i++)
		for(j=Last[i];j;j=Next[j])
			if(Id[i]!=Id[End[j]])
				G[Id[i]].insert(Id[End[j]]);
	DP();
	ll ans=0;
	for(i=1;i<=n;i++)ans=(ans+(ll)(f[Id[i]]-g[Id[i]]+1)*i%Mod)%Mod;
	printf("%lld",ans);
}
