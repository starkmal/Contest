#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=55;

ll n,x,y,m;

//Matrix
typedef long long Matrix[N][N];
Matrix st,tmp,ans,src;
void MMul(Matrix a,Matrix b,Matrix dest){
	memset(src,0,sizeof(src));
	for(int i=1;i<=y;i++)
		for(int j=1;j<=y;j++)
			for(int k=1;k<=y;k++)
				src[i][j]=(src[i][j]+a[i][k]*b[k][j]%m)%m;
	memcpy(dest,src,sizeof(src));
}
void MKsm(Matrix a,ll b){
	for(int i=1;i<=y;i++)ans[i][i]=1;
	for(;b;b>>=1,MMul(a,a,a))if(b&1)MMul(ans,a,ans);
}
ll C[N][N];
int main(){
	int i,j;
	scanf("%lld%lld%lld",&n,&x,&m);
	y=x+1;
	for(i=0;i<=x;i++)C[i][0]=1;
	for(i=1;i<=x;i++)
		for(j=1;j<=i;j++)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%m;
	for(j=1;j<=y;j++)
		for(i=j;i<=y;i++)
			tmp[i][j]=C[x-j+1][i-j]*x%m;
	y++;
	tmp[1][y]=1,tmp[y][y]=1;
	for(i=1;i<y;i++)st[1][i]=x;st[1][y]=0;
	MKsm(tmp,n);
	MMul(st,ans,st);
	printf("%lld",st[1][y]);
}