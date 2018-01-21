#include<stdio.h>
#include<algorithm>
#include<vector>
using namespace std;
const int N=100005,M=5005;

int n,m,q,a[N],Ans[M];
vector<int>v[5005];
int main(){
	int i,j,k,x,y;
	char opt[20];
	scanf("%d%d%d",&n,&m,&q);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	for(i=1;i<=m;i++){
		scanf("%d",&k);
		for(j=1;j<=k;j++){
			scanf("%d",&x);
			v[i].push_back(x);
			Ans[i]+=a[x];
			
		}
	}
	for(i=1;i<=q;i++){
		scanf("%s",opt);
		if(opt[0]=='?'){
			
		}
		else{
			
		}
	}
}
