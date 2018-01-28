#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const ll Mod=1e9+7;
const int N=50005;

int T;
ll n,A,B,f[N];
ll s[N][205],C[205][205];
void Stirling(){
	s[0][0]=1;
	for(int i=1;i<=50000;i++)
		for(int j=1;j<=200&&j<=i;j++)
			s[i][j]=(s[i-1][j-1]+s[i-1][j]*(i-1)%Mod)%Mod;
}
void Combination(){
	for(int i=0;i<=200;i++)C[i][0]=1;
	for(int i=1;i<=200;i++)
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
}
int main(){
    int i,j,k;
    scanf("%d",&T);
	Stirling();
	Combination();
    while(T--){
        scanf("%lld%lld%lld",&n,&A,&B);
        printf("%lld\n",s[n-1][A+B-2]*C[A+B-2][A-1]%Mod);
    }
}
