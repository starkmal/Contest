#include<stido.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=105;

int T,n,m;
int vis[N],a[N][N],b[N][N],tot;
bool Check(){
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(vis[j]!=a[i][j])return 0;
	return 1;
}
bool Dfs(int d){
	if(d>n)return Check();
	vis[d]=1;
	if(Dfs(d+1))return 1;
	vis[d]=0;
	if(Dfs(d+1))return 1;
}
char str[N<<5],buf[N];
void Work(){
	
}
int main(){
	int i,j,k,x;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(i=1;i<=m;i++){
			scanf("%[^n]",str);
			tot=j=0,k=strlen(str);
			while(j<k){
				sscanf(str+j,"%d",x);
				b[i][++tot]=x;
				j+=strlen(buf);
			}
		}
		Work();
	}
}
