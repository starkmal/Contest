#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<vector>
using namespace std;
typedef long long ll;
const int N=10005;

int Tote,Last[N],Next[N<<1],End[N<<1],Len[N<<1];
void Ins(int x,int y,int z){
	End[++Tote]=y;
	Len[Tote]=z;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

int T,n,k,Size[N];
ll sum,ans,f[N][22],Sum[N];
void DP(int x,int fa){
	Size[x]=1;
	int i,j,u,y;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		if(u==fa)continue;
		DP(u,x);
		Size[x]+=Size[u];
		Sum[x]+=Sum[u]+Len[i];

		for(j=k;j>=1;j--){
			if(j>=Size[u])f[x][j]=max(f[x][j],f[x][j-Size[u]]+Len[i]);
			for(y=1;y<=j;y++)
				f[x][j]=max(f[x][j],f[x][j-y]+f[u][y]);
		}
	}
	ans=max(ans,f[x][k]);
	if(n-Size[x]<=k)ans=max(ans,f[x][k-n+Size[x]]+sum-Sum[x]);
}
int main(){
	int i,j,x,y,z;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&k);
		sum=0;
		for(i=1;i<n;i++){
			scanf("%d%d%d",&x,&y,&z);
			x++,y++;
			Ins(x,y,z),Ins(y,x,z);
			sum+=z;
		}
		ans=0;
		DP(1,0);
		printf("%lld\n",sum*2-ans*2);
		Tote=0;
		for(i=1;i<=n;i++){
			Last[i]=0;
			Size[i]=0;
			Sum[i]=0;
			for(j=1;j<=k;j++)f[i][j]=0;
		}
	}
}
