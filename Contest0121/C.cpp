#include<stdio.h>
#include<algorithm>
#include<string.h>
using namespace std;
const int N=1005;

int T,n,m,t;
char Map[N][N],str[N*10];

struct Data{
	int x,y,d,v;
	void print(){
		printf("%d %d %d %d",y-1,x-1,d,v);
	}
};
pair<Data,int>S[N*10];
int tot,maxv;
int dx[9]={-1,-1,0,1,1,1,0,-1},dy[9]={0,1,1,1,0,-1,-1,-1};
void buff(){
	for(int i=1;i<=tot;i++){
		printf("crossing startline: ");
		S[i].first.print();
		printf(" %d\n",S[i].second);
	}	
}
void Work(Data now){
	int i,j,k,tx,ty,flag;
	tot=0;
	for(i=1;i<=strlen(str+1);i++){
		if(str[i]=='a'&&now.v<maxv)now.v++;
		else if(str[i]=='b'&&now.v>0)now.v--;
		else if(str[i]=='r')now.d=(now.d+9)%8;
		else if(str[i]=='l')now.d=(now.d+7)%8;

		flag=0;
		for(j=1;j<=now.v;j++){
			tx=now.x+dx[now.d],ty=now.y+dy[now.d];
			now.x=tx,now.y=ty;
			if(Map[tx][ty]=='.')flag=1;
			else if(Map[tx][ty]=='W'){
				now.print();
				puts(" crashed");
				buff();
				return;
			}
			else if(Map[tx][ty]=='s'){
				S[++tot].first=now;
				S[tot].second=i-1;
			}
		}
		if(flag)now.v=1;
	}
	now.print();puts("");
	buff();
}
int main(){
	int i,j,k,x,y,d;
	scanf("%d",&T);
	for(k=1;k<=T;k++){
		printf("Scenario #%d:\n",k);
		scanf("%d%d",&m,&n);
		for(i=1;i<=n;i++)
			scanf("%s",Map[i]+1);
		scanf("%d",&t);
		for(i=1;i<=t;i++){
			scanf("%d%d%d%d",&y,&x,&d,&maxv);
			x++,y++;
			scanf("%s",str+1);
			Work((Data){x,y,d,0});
		}
		puts("");
	}
}
