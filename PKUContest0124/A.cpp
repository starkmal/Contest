#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<queue>
using namespace std;

int T,n=10,m=15;
bool Vis[11][16],Mark[11][16];
char Map[11][16],tmp[11][16];
struct Cor{
	int x,y;
	Cor(){}
	Cor(int a,int b):x(a),y(b){}
};
void Shift(){
	int i,j,tl;
	memset(tmp,0,sizeof(tmp));
	for(j=1;j<=m&&Map[n][j];j++){
		tl=n;
		for(i=n;i>=1&&Map[i][j];i--)
			if(!Vis[i][j])
				tmp[tl--][j]=Map[i][j];
	}
	memset(Map,0,sizeof(Map));
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			Map[i][j]=tmp[i][j];
	memset(tmp,0,sizeof(tmp));
	tl=0;
	for(j=1;j<=m;j++)
		if(Map[n][j]){
			tl++;
			for(i=1;i<=n;i++)
				tmp[i][tl]=Map[i][j];
		}
	memset(Map,0,sizeof(Map));
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			Map[i][j]=tmp[i][j];
}
int dx[4]={0,0,-1,1},dy[4]={1,-1,0,0};
bool Ok(Cor it){
	return it.x>=1&&it.y>=1&&it.x<=n&&it.y<=m&&Map[it.x][it.y];
}
int Bfs(Cor st){
	char t=Map[st.x][st.y];
	queue<Cor>q;
	q.push(st),Mark[st.x][st.y]=1;
	Cor tmp,nxt;
	int i,tot=1;
	while(!q.empty()){
		tmp=q.front();q.pop();
		for(i=0;i<4;i++){
			nxt.x=tmp.x+dx[i],nxt.y=tmp.y+dy[i];
			if(Ok(nxt)&&!Mark[nxt.x][nxt.y]&&Map[nxt.x][nxt.y]==t){
				q.push(nxt);
				tot++;
				Mark[nxt.x][nxt.y]=1;
			}
		}
	}
	return tot;
}
int bfs2(Cor st){
	memset(Vis,0,sizeof(Vis));
	char t=Map[st.x][st.y];
	queue<Cor>q;
	q.push(st),Vis[st.x][st.y]=1;
	Cor tmp,nxt;
	int i,tot=1;
	while(!q.empty()){
		tmp=q.front();q.pop();
		for(i=0;i<4;i++){
			nxt.x=tmp.x+dx[i],nxt.y=tmp.y+dy[i];
			if(Ok(nxt)&&!Vis[nxt.x][nxt.y]&&Map[nxt.x][nxt.y]==t){
				Vis[nxt.x][nxt.y]=1;
				tot++;
				q.push(nxt);
			}
		}
	}
	return tot;
}
Cor Work(){
	memset(Mark,0,sizeof(Mark));
	int i,j,k,Maxx=0,t;
	Cor rt,tmp;
	for(j=1;j<=m&&Map[n][j];j++)
		for(i=n;i>=1&&Map[i][j];i--)
			if(!Mark[i][j]){
				tmp=Cor(i,j);
				t=Bfs(tmp);
				if(t>Maxx)Maxx=t,rt=tmp;
			}
	if(Maxx>1)return rt;
	else return Cor(-1,-1);
}
int main(){
	int i,j,k,tm=0,ck,ans,tot;
	scanf("%d",&T);
	while(T--){
		tm++;
		memset(Vis,0,sizeof(Vis));
		for(i=1;i<=n;i++)
			scanf("%s",Map[i]+1);
		printf("Game %d:\n\n",tm);
		ans=0,tot=n*m,ck=0;
		while(1){
			ck++;
			Cor st=Work();
			if(st.x==-1)break;
			char ky=Map[st.x][st.y];
			k=bfs2(st);
			ans+=(k-2)*(k-2);
			tot-=k;
			printf("Move %d at (%d,%d): removed %d balls of color %c, got %d points.\n",ck,n-st.x+1,st.y,k,ky,(k-2)*(k-2));
			Shift();
		}
		if(!tot)ans+=1000;
		printf("Final score: %d, with %d balls remaining.\n",ans,tot);
		if(T)puts("");
	}
}
