#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef double db;
const db eps=1e-9,Inf=1e5;
const int N=505;

struct Point{
	db x,y;
	Point(){}
	Point(db a,db b):x(a),y(b){}
}A[N],S[N],T[N];
bool operator < (const Point& lhs,const Point& rhs){
	return lhs.x<rhs.x||(lhs.x==rhs.x&&lhs.y<rhs.y);
}
Point operator + (const Point& lhs,const Point& rhs){
	return Point(lhs.x+rhs.x,lhs.y+rhs.y);
}
Point operator - (const Point& lhs,const Point& rhs){
	return Point(lhs.x-rhs.x,lhs.y-rhs.y);
}
Point operator * (db lambda,const Point& rhs){
	return Point(rhs.x*lambda,rhs.y*lambda);
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
	return lhs.p+((rhs.p-lhs.p)*rhs.v/(lhs.v*rhs.v))*lhs.v;
}

int n,tot;
void HI(const Line& x){
	int i,t=0;
	S[0]=S[tot];
	S[tot+1]=S[1];
	for(i=1;i<=tot;i++)
		if((S[i]-x.p)*x.v>=-eps){
			if((S[i-1]-x.p)*x.v<=-eps)T[++t]=Line(S[i-1],S[i]-S[i-1])*x;
			if((S[i+1]-x.p)*x.v<=-eps)T[++t]=Line(S[i+1],S[i+1]-S[i])*x;
		}else T[++t]=S[i];
	for(i=1;i<=t;i++)S[i]=T[i];
	tot=t;
//	for(i=1;i<=tot;i++)printf("%.3lf %.3lf\n",S[i].x,S[i].y);
//	puts("");
}
int main(){
	int i,j,k;
	db x,y;
	while(scanf("%d",&n)!=EOF&&n){
		for(i=1;i<=n;i++){
			scanf("%lf%lf",&x,&y);
			A[i]=Point(x,y);
		}
		tot=0;
		S[++tot]=Point(-Inf,-Inf);
		S[++tot]=Point(Inf,-Inf);
		S[++tot]=Point(Inf,Inf);
		S[++tot]=Point(-Inf,Inf);
		for(i=1;i<n;i++)HI(Line(A[i],A[i+1]-A[i]));
		HI(Line(A[n],A[1]-A[n]));
		if(tot)puts("1");
		else puts("0");
	}
}
