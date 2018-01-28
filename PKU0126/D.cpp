#include<stdio.h>
#include<algorithm>
using namespace std;

int n,m,A[105][10005];
bool Vis[105][10005],Mark[105][10005];
bool Check(int x){
	int i,j,k,Maxx;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			Vis[i][j]=Mark[i][j]=0;
	for(i=1;i<=n;i++){
		Maxx=0;
		for(j=1;j<=m;j++){
			if(A[i][j]>=x)Maxx=j+x-1;
			if(Maxx>=j)Vis[i][j]=1;
		}
	}
	for(i=1;i<=n;i++){
		Maxx=m+1;
		for(j=m;j>=1;j--){
			if(A[i][j]>=x)Maxx=j-x+1;
			if(Maxx<=j)Vis[i][j]=1;
		}
	}
	for(j=1;j<=m;j++){
		Maxx=0;
		for(i=1;i<=n;i++){
			if(A[i][j]>=x)Maxx=i+x-1;
			if(Maxx>=i)Mark[i][j]=1;
		}
	}
	for(j=1;j<=n;j++){
		Maxx=n+1;
		for(i=n;i>=1;i--){
			if(A[i][j]>=x)Maxx=i-x+1;
			if(Maxx<=i)Mark[i][j]=1;
		}
	}
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			if(!Vis[i][j]||!Mark[i][j])
				return 0;
	return 1;
}
int main(){
	int i,j,k,L,R,Mid,Ans;
	while(scanf("%d%d",&n,&m)!=EOF&&n&&m){
		L=1,R=0,Ans=0;
		for(i=1;i<=n;i++)
			for(j=1;j<=m;j++){
				scanf("%d",&A[i][j]);
				R=max(R,A[i][j]);
			}
		while(L<=R){
			Mid=L+R>>1;
			if(Check(Mid))R=Mid-1,Ans=Mid;
			else L=Mid+1;
		}
		if(Ans)printf("%d\n",Ans);
		else puts("NO ANSWER!");
	}
}

