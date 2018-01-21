#include<stdio.h>
#include<ctype.h>
#include<algorithm>
using namespace std;
const int N=1005;
inline int _R(){
	char t=getchar();
	while(!isdigit(t)){
		if(t=='#')return -1;
		t=getchar();
	}
	while(isdigit(t))t=getchar();
	return 1;
}
int T,n;
int s[N];
int main(){
	int i,j,k;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(i=1;i<=n;i++)s[i]=_R();
		if(n%2==0)
			puts("No");
		else{
			bool flag=1;
			for(i=2;i<=n;i++)
				if(s[i]==-1&&s[i-1]==-1){
					puts("No");
					flag=0;
					break;
				}
			if(flag)puts("Yes");
		}
	}
}
