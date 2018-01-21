#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=1000005;

ll n,p,k,m,r,C,Ans;
ll ksm(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%p)
		if(b&1)ans=ans*a%p;
	return ans;
}
int main(){
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	ll i,j,k,x,y;
	scanf("%lld%lld%lld%lld",&n,&p,&k,&r);
	m=n*k;
	if(m>N){
		puts("byebye");
		return 0;
	}
	C=1;
	for(i=1;i<=r;i++)C=C*(m-i)%p*ksm(i+1,p-2)%p;
	for(i=r;i<=m;i++){
		if((i-r)%k==0)Ans=(Ans+C)%p;
		C=C*(m-i)%p*ksm(i+1,p-2)%p;
	}
	printf("%lld",Ans);
}
