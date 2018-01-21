#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int N=105;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}
int n,m,step,tck,mxa,Ans,a[N],D[N][N],vis[N][N];
int tmp[30][N][N];
int cnt[N];
void dfs(int d,int tot){
	if(tck>=3e9)return;
	if(d==step){
		for(int i=1;i<=mxa;i++)tot-=a[i]*cnt[i];
		tck+=mxa+2;
		Ans=max(Ans,tot);
		return;
	}
	int i,j,k,u;
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			tmp[d][i][j]=vis[i][j];
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++){
			for(k=i;k<=j;k++)
				for(u=k;u<=j;u++)
					if(!vis[k][u])tot+=D[k][u],vis[k][u]=1;
			for(k=i;k<=j;k++)cnt[a[k]]++;
			tck+=(j-i+1)*(j-i+1)*4;
			dfs(d+1,tot);
			for(k=i;k<=j;k++)
				for(u=k;u<=j;u++)
					if(!tmp[d][k][u])vis[k][u]=0,tot-=D[k][u];
			for(k=i;k<=j;k++)cnt[a[k]]--;
			tck+=(j-i+1)*(j-i+1)*4;
		}
}
int main(){
	int i,j,k;
	n=_R(),m=_R();
	for(i=1;i<=n;i++)a[i]=_R(),mxa=max(mxa,a[i]);
	for(i=1;i<=n;i++)
		for(j=i;j<=n;j++)
			D[i][j]=_R();
	tck=1000000+n*n;
	while(tck<=3e7)dfs(0,0),step++;
	printf("%d",Ans);
}
