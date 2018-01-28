#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
const int N=4005;

int T,n,m;
bool Vis[N][N];
char Map[N][N];

struct Node{int x,y;};
queue<Node>q;
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
void Bfs(Node st){
	q.push(st);
	Vis[st.x][st.y]=1;
	char reg=Map[st.x][st.y];
	int tx,ty,i;
	Node tmp;
	while(!q.empty()){
		tmp=q.front(),q.pop();
		for(i=0;i<4;i++){
			tx=tmp.x+dx[i],ty=tmp.y+dy[i];
			if(tx>0&&tx<=n&&ty>0&&ty<=m&&!Vis[tx][ty]&&Map[tx][ty]==reg){
				Vis[tx][ty]=1;
				q.push((Node){tx,ty});
			}
		}
	}
}
int main(){
	int i,j,k,ans,tot;
	scanf("%d",&T);
	while(T--){
		memset(Vis,0,sizeof(Vis));
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)scanf("%s",Map[i]+1);
		ans=tot=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++)
				if(Map[i][j]=='A')ans=1;
				else if(Map[i][j]=='B')tot=1;
				//if((Map[i][j]=='A'||Map[i][j]=='B')&&!Vis[i][j])
					//ans++,Bfs((Node){i,j});
		printf("%d\n",ans+tot);
	}
}
