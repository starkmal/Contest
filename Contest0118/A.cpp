#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=70005;

bool vis[N];
int st,ed;
int main(){
	char t;
	int i,j,k,x,y;
	st=-32768,ed=32767;
	while(1){
		t=getchar();
		while(t!='>'&&t!='<')t=getchar();
		if(t=='<'){
			getchar(),getchar();
			scanf("%d",&y);
			if(y<st){puts("false");return 0;}
			if(y>ed)y=ed;
			fill(vis,vis+y-st+1,1);
			while(t!='\n'&&t!='|')t=getchar();
			if(t=='\n')break;
		}
		else{
			getchar(),getchar();
			scanf("%d",&x);
			if(x<st)x=st;
			if(x>ed){puts("false");return 0;}
			while(t!='\n'&&t!='&'&&t!='|')t=getchar();
			if(t=='&'){
				while(t!='=')t=getchar();
				scanf("%d",&y);
				if(x<=y){
					if(y>ed)y=ed;
					fill(vis+x-st,vis+y-st+1,1);
				}
				while(t!='\n'&&t!='|')t=getchar();
				if(t=='\n')break;
			}
			else {
				fill(vis+x-st,vis+ed-st+1,1);
				if(t=='\n')break;
			}
		}

	}
	x=0,k=0,y=0;
	for(i=0;i<=ed-st;i++){
		if(!k&&vis[i])x=i,k=1;
		else if(k&&!vis[i]){
			if(!y)y=1;
			else puts(" ||");
			if(x!=0)printf("x >= %d && ",x+st);
			printf("x <= %d",i-1+st);
			k=0;
		}
	}
	if(k&&x==0)puts("true");
	else if(k&&x){
		if(y)puts(" ||");
		printf("x >= %d",x+st);
	}
	if(!k&&!y)puts("false");
}
