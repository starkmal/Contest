#include<stdio.h>
#include<ctype.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=1000005,Inf=1e9;
inline int _R(){
	int d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<3)+(d<<1)+t-'0';
	return d;
}

typedef pair<int,int> pii;
typedef vector<pii> vp;
typedef vp::iterator vi;

int n,T;
vp G[N];
int Dis[N];
bool Vis[N];
queue<int>q;
void spfa(){
	int i,x,u;
	for(i=1;i<=n;i++)Dis[i]=Inf,Vis[i]=0;
	Dis[1]=0,q.push(1);
	while(!q.empty()){
		x=q.front(),q.pop();
		Vis[x]=0;
		for(vi it=G[x].begin();it!=G[x].end();it++)
			if(Dis[it->first]>Dis[x]+it->second){
				Dis[it->first]=Dis[x]+it->second;
				if(!Vis[it->first])
					Vis[it->first]=1,
					q.push(it->first);
			}
	}
}
void Clear(){
	for(int i=1;i<=n;i++)vector<pii>().swap(G[i]);
}
int main(){
	int i,j,k,w,d;
	T=_R();
	while(T--){
		n=_R(),k=_R();
		Clear();
		for(i=1;i<=n;i++){
			w=i%10+1,d=10-w;
			for(j=1;j<=d;j++){
				G[i].push_back(pii(k%n+1,w));
				k=k*233%n;
			}
			G[i].push_back(pii(i%n+1,w));
		}
		spfa();
		printf("%d\n",Dis[n]);
	}
}
