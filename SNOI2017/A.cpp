#include<stdio.h>
#include<string.h>
#include<algorithm>
typedef long long ll;
const ll Mod=1e9+7;
const int N=15;

ll n,K;

typedef long long  Matrix[N][N];
Matrix st,tmp,ans,src;
void MMul(Matrix A,Matrix B){
	memset(src,0,sizeof(src));
	for(int i=1;i<=K;i++)
		for(int j=1;j<=K;j++)
			for(int k=1;k<=K;k++)
				src[i][j]=(src[i][j]+A[i][k]*B[k][j]%Mod)%Mod;
	memcpy(A,src,sizeof(src));
}
void MKsm(Matrix A,ll b){
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=K;i++)ans[i][i]=1;
	for(;b;b>>=1,MMul(A,A))
		if(b&1)MMul(ans,A);
}
ll C[N][N];
int main(){
	ll i,j,k;
	scanf("%lld%lld",&n,&K);
	for(i=0;i<=K;i++)C[i][0]=1;
	for(i=1;i<=K;i++)
		for(j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
	K+=2;
	for(j=2;j<=K;j++)
		for(i=j;i<=K;i++)
			tmp[i][j]=C[K-j][i-j];
	tmp[1][1]=2;
	for(i=2;i<=K;i++)tmp[i][1]=tmp[i][2];
	K++,tmp[1][K]=1;
	for(i=2;i<=K;i++)tmp[i][K]=tmp[i][1];
	for(i=1;i<=K;i++)st[1][i]=1;
	MKsm(tmp,n-1);
	MMul(st,ans);
	printf("%lld",st[1][K]);
}

