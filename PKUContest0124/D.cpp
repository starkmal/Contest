#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100005;

int Tote,Last[N],Next[N],End[N];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int T,n;
ll R,I,Size[N],Sum[N],Ans[N];
void Dfs1(int x,int fa){
	Size[x]=1;
	for(int i=Last[x],u;i;i=Next[i])
		if((u=End[i])!=fa){
			Dfs1(u,x);
			Size[x]+=Size[u];
			Sum[x]+=R*Size[u]+Sum[u];
		}
}
void Dfs2(int x,int fa,ll d){
	Ans[x]=d+Sum[x];
	for(int i=Last[x],u;i;i=Next[i])
		if((u=End[i])!=fa)
			Dfs2(u,x,d+Sum[x]-Sum[u]+(n-2*Size[u])*R);
}
int main(){
	int i,j,k,x,y;
	scanf("%d",&T);
	while(T--){
		scanf("%d%lld%lld",&n,&I,&R);
		for(i=1;i<n;i++){
			scanf("%d%d",&x,&y);
			Ins(x,y),Ins(y,x);
		}
		Dfs1(1,0);
		Dfs2(1,0,0);
		ll ans=9e18;
		for(i=1;i<=n;i++)ans=min(ans,Ans[i]);
		printf("%I64d\n",ans*I*I);
		for(i=1;i<=n;i++)
			if(Ans[i]==ans)printf("%d ",i);
		puts("");
		if(T)puts("");
		Tote=0;
		for(i=1;i<=n;i++)Last[i]=Sum[i]=Size[i]=Ans[i]=0;
	}
}
