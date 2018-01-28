#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=1005;
int f[N][N],n,m,t,a[N],b[N],C,R;
int main(){
	int i,j,k;
	scanf("%d%d%d",&n,&m,&t);
	for(i=1;i<=t;i++)scanf("%d%d",&a[i],&b[i]);
	for(i=1;i<=t;i++)
		for(j=n;j>=a[i];j--)
			for(k=m;k>=b[i];k--)
				f[j][k]=max(f[j][k],f[j-a[i]][k-b[i]]+1);
	for(i=0;i<=n;i++)
		for(j=0;j<=m;j++)
			if(f[i][j]>C||(f[i][j]==C&&j<R))C=f[i][j],R=j;
	printf("%d %d",C,m-R);
}
