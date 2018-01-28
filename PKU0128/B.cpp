#include<stdio.h>
#include<algorithm>
using namespace std;
const int Inf=1e9+7;
int main(){
	int T,n,x,L,R;
	char argv[12];
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		L=-Inf,R=Inf;
		while(n--){
			scanf("%s%d",argv,&x);
			if(argv[0]=='=')L=R=x;
			else if(argv[0]=='<'&&argv[1]=='=')R=min(R,x);
			else if(argv[0]=='<')R=min(R,x-1);
			else if(argv[0]=='>'&&argv[1]=='=')L=max(L,x);
			else if(argv[0]=='>')L=max(L,x+1);
		}
		if(R==Inf||L==-Inf)puts("-1");
		else printf("%d\n",R-L+1);
	}
}
