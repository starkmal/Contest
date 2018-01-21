#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
const int N=1000005;

int T,st,ed;
bool vis[N];
typedef pair<int,int> pii;
queue<pii>q;
void Bfs(){
	memset(vis,0,sizeof(vis));
	while(q.size())q.pop();
	q.push(pii(st,0));
	vis[st]=1;
	int u,i;
	while(q.size()){
		pii tmp=q.front();
		q.pop();
		tmp.second++;
		for(i=0;i<4;i++){
			if(i==0)u=tmp.first+1;
			if(i==1)u=tmp.first-1;
			if(i==2)u=tmp.first*2;
			if(i==3){
				if(tmp.first&1)continue;
				u=tmp.first/2;
			}
			if(u>=1&&u<=N-5&&!vis[u]){
				vis[u]=1;
				if(u==ed){
					printf("%d\n",tmp.second<<1);
					return;
				}
				q.push(pii(u,tmp.second));
			}
		}
	}
}
int main(){
	int i,j,k;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&st,&ed);
		Bfs();
	}
}
