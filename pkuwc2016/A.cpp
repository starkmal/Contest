#include<stdio.h>
#include<algorithm>
using namespace std;
typedef double db;
db Maxx;
int T,n,m,id;
int main(){
	int i,j,k;
	int x;db y;
	scanf("%d",&T);
	while(T--){
		Maxx=0;
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++){
			scanf("%d%lf",&x,&y);
			if(x<=m&&y>Maxx)Maxx=y,id=i;
		}
		printf("%d\n",id);
	}
}
