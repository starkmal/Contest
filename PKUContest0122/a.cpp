#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=100005;

struct Point{
	int x,y;
	Point(){}
	Point(ll a,ll b):x(a),y(b){}
};
bool operator < (const Point& lhs,const Point& rhs){
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
Point operator + (const Point& lhs,const Point& rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator - (const Point& lhs,const Point& rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
ll operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}

int n,tot;
Point A[N],S[N];
void Graham(){
	sort(A+1,A+1+n);
	int i,t;
	for(i=1;i<=n;i++){
		while(tot>1&&(S[tot]-S[tot-1])*(A[i]-S[tot-1])<=0)tot--;
		S[++tot]=A[i];
	}
	t=tot;
	for(i=n-1;i;i--){
		while(tot>t&&(S[tot]-S[tot-1])*(A[i]-S[tot-1])<=0)tot--;
		S[++tot]=A[i];
	}
}
ll dis(const Point& a,const Point& b){
	return ((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
void RC(){
	ll ans=0;
	int i,j;
	S[tot+1]=S[1];
//	for(i=1,j=2;i<=tot;i++){
//		while(j%tot+1!=i&&(S[i+1]-S[i])*(S[j+1]-S[i])>(S[i+1]-S[i])*(S[j]-S[i]))
//			j=j%tot+1;
//		ans=max(ans,dis(S[i],S[j]));
//	}
	for(i=1;i<=tot;i++)
		for(j=i+1;j<=tot;j++)
			ans=max(ans,dis(S[i],S[j]));
	printf("%lld",ans);
}
int main(){
	int i,j,k;
	ll x,y;
	scanf("%d",&n);
	for(i=1;i<=n;i++)scanf("%lld%lld",&x,&y),A[i]=Point(x,y);
	Graham();
	RC();
}
