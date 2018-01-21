#include<stdio.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200005,Inf=1e9;

int n,m,Minn,Maxx,a[N],b[N];
ll A,B,C,Sum[N];
ll Cal(int hi){
	int t=upper_bound(b+1,b+1+m,hi)-b;
	ll f=Sum[m]-Sum[t-1]-(ll)(m-t+1)*hi;
	ll g=(ll)(t-1)*hi-Sum[t-1];
	ll cost=0;
	if(A<B){
		if(f<g)cost+=A*f;		//右边要减少的比左边能增加的少
		else cost+=A*g+B*(f-g);
	}
	else cost+=B*f;
	for(int i=1;i<=n;i++)
		if(hi>a[i])cost+=(hi-a[i])*C;
	return cost;
}
int main(){
	freopen("exam.in","r",stdin);
	freopen("exam.out","w",stdout);
	int i,j,k,x,y,z;
	scanf("%lld%lld%lld",&A,&B,&C);
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&a[i]),Minn=min(Minn,a[i]);
	for(i=1;i<=m;i++){
		scanf("%d",&b[i]);
		Maxx=max(Maxx,b[i]);
	}
	sort(b+1,b+1+m);
	for(i=1;i<=m;i++)Sum[i]=Sum[i-1]+b[i];
	int L=1,R=Maxx,LMid,RMid;
	while(L<=R){
		if(R-L<=6){
			ll t=Cal(L);
			for(i=L;i<=R;i++)
				if(Cal(i)<t)L=i,t=Cal(i);
			break;
		}
		LMid=L+(R-L)/3;
		RMid=R-(R-L)/3;
		if(Cal(LMid)<Cal(RMid))R=RMid;
		else L=LMid;
	}
	printf("%lld",Cal(L));
}
