#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const db eps=1e-9;const int N=3005;

struct Point{
	db x,y;
	Point(){}
	Point(db a,db b):x(a),y(b){}
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
Point operator * (db a,const Point& rhs){
	return Point(rhs.x*a,rhs.y*a);
}
db operator * (const Point& lhs,const Point& rhs){
	return lhs.x*rhs.y-lhs.y*rhs.x;
}

struct Line{
	Point p,v;
	Line(){}
	Line(Point a,Point b):p(a),v(b){}
};
Point operator * (const Line& lhs,const Line& rhs){
	return lhs.p+(rhs.p-lhs.p)*rhs.v/(lhs.v*rhs.v)*lhs.v;
}

int q,n,tot;
Point A[N],S[N],T[N];
void HI(const Line& x){
	S[0]=S[tot];
	S[tot+1]=S[1];
	int t=0,i;
	for(i=1;i<=tot;i++)
		if((S[i]-x.p)*x.v>=-eps){
			if((S[i-1]-x.p)*x.v<=-eps)T[++t]=Line(S[i-1],S[i]-S[i-1])*x;
			if((S[i+1]-x.p)*x.v<=-eps)T[++t]=Line(S[i],S[i+1]-S[i])*x;
		}else T[++t]=S[i];
	for(i=1;i<=t;i++)S[i]=T[i];
	tot=t;
}
int main(){
	int i,j,k;
	scanf("%d",&q);
	while(q--){
		tot=0;
		S[++tot]=Point(-1e6,-1e6);
		S[++tot]=Point(1e6,-1e6);
		S[++tot]=Point(1e6,1e6);
		S[++tot]=Point(-1e6,1e6);
		db x,y,ans=0.0;
		scanf("%d",&n);
		for(i=1;i<=n;i++)scanf("%lf%lf",&x,&y),A[i]=Point(x,y);
		for(i=1;i<n;i++)HI(Line(A[i],A[i]-A[i+1]));
		HI(Line(A[n],A[n]-A[1]));
		S[0]=S[tot];
		for(i=0;i<tot;i++)
			ans+=S[i]*S[i+1];
		printf("%.2lf\n",ans/2);
	}
}
