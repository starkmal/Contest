#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=100005;

int n,m,S,T;
ll a[N];
struct Query{
	int y,m,d,c,s,t;
	friend bool operator < (const Query& lhs,const Query& rhs){
		if(lhs.y!=rhs.y)return lhs.y<rhs.y;
		if(lhs.m!=rhs.m)return lhs.m<rhs.m;
		if(lhs.d!=rhs.d)return lhs.d<rhs.d;
		return lhs.c<rhs.c;
	}
}Q[N];
int cal(Query tmp){
	if(tmp.m==1||tmp.m==3||tmp.m==5||tmp.m==7||tmp.m==8||tmp.m==10||tmp.m==12)
		return 31;
	if(tmp.m==4||tmp.m==6||tmp.m==9||tmp.m==11)
		return 30;
	if(tmp.y%400==0)return 29;
	if(tmp.y%100==0)return 28;
	if(tmp.y%4==0)return 29;
	return 28;
}
void Work(){
	Query tmp;
	tmp.y=2000,tmp.m=1,tmp.d=1,tmp.c=0;
	int t=1,tim=1,lim;
	while(t<=n){
		while(tmp<Q[t]){
			tmp.c++;
			if(tmp.c>23)tmp.c=0,tmp.d++;
			lim=cal(tmp);
			if(tmp.d>lim)tmp.d=1,tmp.m++;
			if(tmp.m>12)tmp.m=1,tmp.y++;
			tim++;
		}
		Q[t].s=tim,t++;
	}
}
ll cal2(int i,int j){
	return a[i]+(j-i)*T;
}
void DP(){
	int i,j,k,v=1;
	ll ans=0;
	deque<int>q;
	for(i=1;i<=n;i++){
		while(v<=Q[i].s){
			while(!q.empty()&&cal2(q.back(),Q[i].s)>cal2(v,Q[i].s))q.pop_back();
			q.push_back(v);
			v++;
		}
		while(!q.empty()&&Q[i].s-q.front()>S)q.pop_front();
		ans+=Q[i].t*cal2(q.front(),Q[i].s);
	}
	printf("%lld\n",ans);
}
int main(){
	int i,j,k;
	char month[12];
	while(scanf("%d%d",&n,&m)!=EOF&&n&&m){
		for(i=1;i<=n;i++){
			scanf("%s%d%d%d%d",month,&Q[i].d,&Q[i].y,&Q[i].c,&Q[i].t);
			if(strcmp(month,"Jan")==0)Q[i].m=1;
			if(strcmp(month,"Feb")==0)Q[i].m=2;
			if(strcmp(month,"Mar")==0)Q[i].m=3;
			if(strcmp(month,"Apr")==0)Q[i].m=4;
			if(strcmp(month,"May")==0)Q[i].m=5;
			if(strcmp(month,"Jun")==0)Q[i].m=6;
			if(strcmp(month,"Jul")==0)Q[i].m=7;
			if(strcmp(month,"Aug")==0)Q[i].m=8;
			if(strcmp(month,"Sep")==0)Q[i].m=9;
			if(strcmp(month,"Oct")==0)Q[i].m=10;
			if(strcmp(month,"Nov")==0)Q[i].m=11;
			if(strcmp(month,"Dec")==0)Q[i].m=12;
		}
		scanf("%d%d",&S,&T);
		memset(a,0,sizeof(a));
		for(i=1;i<=m;i++)scanf("%lld",&a[i]);
		sort(Q+1,Q+1+n);
		Work();
//		for(i=1;i<=n;i++)printf("%d",Q[i].s);
		DP();
	}
}
