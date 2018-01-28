#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef double db;
const int N=1005;

int n,m,len,fail[N];
char c[30],b[N];
db f[N][N],g[30];
int main(){
	int i,j,k,t;
	while(scanf("%d%d",&n,&m)!=EOF&&n&&m){
		for(i=1;i<=n;i++){
			scanf("%s%lf",b,&g[i]);
			c[i]=b[0];
		}
		scanf("%s",b+1);
		len=strlen(b+1);
		for(i=2,j=0;i<=len;i++){
			while(j&&b[j+1]!=b[i])j=fail[j];
			if(b[j+1]==b[i])j++;
			fail[i]=j;
		}
		memset(f,0,sizeof(f));
		f[0][0]=1;
		for(i=0;i<m;i++)
			for(j=0;j<len;j++)
				for(k=1;k<=n;k++){
					t=j;
					while(t&&b[t+1]!=c[k])t=fail[t];
					if(b[t+1]==c[k])t++;
					f[i+1][t]+=f[i][j]*g[k];
				}
		db ans=0;
		for(i=1;i<=m;i++)ans+=f[i][len];
		printf("%.2lf%%\n",ans*100);
	}
}
