#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=2500;

char Map[ N ][ N ];
int n;
void Draw( int l,int r,int u,int d ){
	if(d-u<1)return;
	int i,j,k,len=r-l+1,mid=l+r>>1;
	for(i=l,j=d;i<=mid;i++,j--)Map[j][i]='/';
	for(i=mid+1,j=u;i<=r;i++,j++)Map[j][i]='\\';
	for(i=l;i<=r;i++)if(Map[d][i]==' ')Map[d][i]='_';
	Draw(l,mid,(u+d>>1)+1,d);
	Draw(mid+1,r,(u+d>>1)+1,d);
	Draw((l+mid>>1)+1,(mid+1+r>>1),u,u+d>>1);
}
int main(  ){
	int i,j,k;
	while(scanf("%d",&n)!=EOF&&n!=0){
		for(i=1;i<=(1<<n);i++)
			for(j=1;j<=(1<<n+1);j++)
				Map[i][j]=' ';
		Draw(1,1<<n+1,1,1<<n);
		for(i=1;i<=(1<<n);i++,puts("")){
			j=1<<n+1;
			while(Map[i][j]==' ')j--;
			for(k=1;k<=j;k++)putchar(Map[i][k]);
		}
		puts("");
	}
}
