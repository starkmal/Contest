#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=55;

int n,m;
ll f[N][N],g[N],Ans;
int main(){
	int i,j,k,o;
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[0][0]=1;
		for(i=1;i<=n;i++)
			for(j=i;j<=n;j++)
				for(k=1;k<=m;k++)
					f[j][k]+=f[j-i][k-1];
		g[0]=1;
		for(i=1;i<=n;i++)
			for(j=n;j>=i;j--)
				g[j]+=g[j-i];
		printf("%lld\n%lld\n%lld\n",f[n][m],g[n],g[n]);
	}
}
