#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
const int N=105;
const ll Mod=1e9+7;

int n,m,L,Len[N];
char str[55][N],ban[55][N];
ll f[N][N];
int Root=1,Totn=1,Son[N][30],Fail[N];
bool Flag[N];
void Insert(char *c){
	int len=strlen(c),i,p=Root,t;
	for(i=0;i<len;i++){
		t=c[i]-'a';
		if(!Son[p][t])Son[p][t]=++Totn;
		p=Son[p][t];
	}
	Flag[p]=1;
}
void BuildAC(){
	int i,x;
	queue<int>q;
	for(i=0;i<26;i++)
		if(Son[Root][i])Fail[Son[Root][i]]=Root,q.push(Son[Root][i]);
		else Son[Root][i]=Root;
	while(!q.empty()){
		x=q.front(),q.pop();
		for(i=0;i<26;i++)
			if(Son[x][i]){
				Fail[Son[x][i]]=Son[Fail[x]][i];
				q.push(Son[x][i]);
			}
			else Son[x][i]=Son[Fail[x]][i];
	}
}
int Run(int id,int st){
	int p=st,i,t;
	for(i=0;i<Len[id];i++){
		t=str[id][i]-'a';
		while(p&&!Son[p][t])p=Fail[p];
		p=Son[p][t];
		if(!p)p=Root;
		if(Flag[p])return 0;
	}
	return p;
}
void Solve_60(){
	int i,j,k,u;
	f[0][1]=1;
	for(i=0;i<L;i++)
		for(j=1;j<=n;j++)if(i+Len[j]<=L)
			for(k=1;k<=Totn;k++){
				u=Run(j,k);
				if(u)f[i+Len[j]][u]=(f[i+Len[j]][u]+f[i][k])%Mod;
			}
	ll ans=0;
	for(i=1;i<=Totn;i++)ans=(ans+f[L][i])%Mod;
	printf("%lld",ans);
}
typedef long long Matrix[N][N];
Matrix st,tmp,ans,src;
void MMul(Matrix A,Matrix B){
	memset(src,0,sizeof(src));
	for(int i=1;i<=Totn;i++)
		for(int j=1;j<=Totn;j++)
			for(int k=1;k<=Totn;k++)
				src[i][j]=(src[i][j]+A[i][k]*B[k][j]%Mod)%Mod;
	memcpy(A,src,sizeof(src));
}
void Mksm(Matrix a,ll b){
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=Totn;i++)ans[i][i]=1;
	for(;b;b>>=1,MMul(a,a))
		if(b&1)MMul(ans,a);
}
void Solve_20(){
	int i,j,k;
	for(i=1;i<=Totn;i++)
		for(j=1;j<=n;j++){
			k=Run(j,i);
			if(k)tmp[i][k]=1;
		}
	st[1][1]=1;
	Mksm(tmp,L);
	MMul(st,ans);
	ll sum=0;
	for(i=1;i<=Totn;i++)
		sum=(sum+ans[1][i])%Mod;
	printf("%lld",sum);
}
int main(){
	int i,j,k;
	scanf("%d%d%d",&n,&m,&L);
	for(i=1;i<=n;i++)scanf("%s",str[i]);
	for(i=1;i<=n;i++)Len[i]=strlen(str[i]);
	for(i=1;i<=m;i++)scanf("%s",ban[i]),Insert(ban[i]);
	BuildAC();
	if(L<=100)Solve_60();
	else Solve_20();
}
