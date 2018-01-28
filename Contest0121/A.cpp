#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=1005;

int T,n,f[N];
char str[N];
bool check(int l,int r){
	for(;l<r;l++,r--)
		if(str[l]!=str[r])return 0;
	return 1;
}
int main(){
	int i,j,k;
	scanf("%d",&T);
	while(T--){
		scanf("%s",str+1);
		n=strlen(str+1);
		memset(f,0x3f,sizeof(f));
		f[0]=0;
		for(i=1;i<=n;i++){
			if(check(1,i)){
				f[i]=0;
				continue;
			}
			for(j=1;j<i;j++)
				if(check(j+1,i))f[i]=min(f[i],f[j]+1);
		}
		printf("%d\n",f[n]);
	}
}
