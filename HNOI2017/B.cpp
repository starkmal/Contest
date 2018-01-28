#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue> 
using namespace std;
const int N=105;

int T,n,m,mc,a[N],w[N],f[N][N];
bool Dfs(int d,int r,int f,int l,int t){
	if(r<0)return 0;
	if(r==0)return 1;
	if(d==m)return 0;
	if(Dfs(d+1,r-1,f,l,t))return 1;
	if(!t)return 0;
	if(Dfs(d+1,r,f,l+1,t))return 1;
	if(Dfs(d+1,r,f*l,l,t))return 1;
	if(Dfs(d+1,r-f,1,0,t-1))return 1;
}
int main(){
	int i,j,k,t,x;
	scanf("%d%d%d",&n,&T,&mc);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=n;i++)scanf("%d",&w[i]);

	memset(f,-1,sizeof(f));
	f[0][mc]=0;
	for(i=0;i<n;i++)
		for(j=0;j<=mc;j++)
			if(f[i][j]!=-1&&j-a[i+1]>=0){
				f[i+1][j-a[i+1]]=max(f[i+1][j-a[i+1]],f[i][j]+1);
				k=min(mc,j+w[i+1]-a[i+1]);
				f[i+1][k]=max(f[i+1][k],f[i][j]);
			}
	for(j=0;j<=mc;j++)
		m=max(m,f[n][j]);
	if(m<1){
		for(i=1;i<=T;i++)puts("0");
		return 0;
	}
	while(T--){
		scanf("%d",&x);
		if(Dfs(0,x,1,0,2))puts("1");
		else puts("0");
	}
}
