#include<stdio.h>
#include<ctype.h>
#include<algorithm>
typedef long long ll;
using namespace std;
const int N=20005;
const ll Mod=1000000007LL;
inline ll _R(){
	ll d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

ll ksm(ll a,ll b){
	ll ans=1;
	for(;b;b>>=1,a=a*a%Mod)
		if(b&1)ans=ans*a%Mod;
	return ans;
}
int T;
ll n,m,r[N],t[N],st,mul,add,term,ans,g;
int main(){
	ll i,j,k,x,y,z,d;
	T=_R();
	while(T--){
		n=_R(),m=_R(),st=((_R()+_R())%Mod+Mod)%Mod;
		for(i=1;i<=m;i++){
			x=_R(),y=_R(),z=_R(),d=_R();
			t[i]=(x-y+d-z+Mod)%Mod;
			r[i]=(x+y+d+z+1)%Mod;
		}
		mul=1;
		for(i=1;i<=m;i++)mul=mul*r[i]%Mod;
		add=0;
		for(i=1;i<=m;i++)add=(add+mul*ksm(r[i],Mod-2)%Mod*t[i]%Mod)%Mod;
		term=n/m;
		ans=0;
		ans=ksm(mul,term-1)*(mul*st%Mod+term*add%Mod)%Mod;
		g=ksm(mul,term);
		for(i=1;i<=n%m;i++){
			ans=(g*t[i]%Mod+ans*r[i]%Mod)%Mod;
			g=g*r[i]%Mod;
		}
		//ans=(ksm(mul,term)*st%Mod+add*(ksm(mul,term)-1+Mod)%Mod*ksm((mul-1+Mod)%Mod,Mod-2)%Mod)%Mod;
		//for(i=1;i<=n%m;i++)ans=(ans*mul%Mod+add)%Mod;
		printf("%lld\n",ans);
	}
}
