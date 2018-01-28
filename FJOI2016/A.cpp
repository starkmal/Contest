#include<stdio.h>
#include<algorithm>
#include<map>
using namespace std;
const int N=3005;

struct BigInt{
	const static int M=100000000;
	int len,*d;
	void Init(){
		d=new int[20];
		len=1;
		for(int i=0;i<20;i++)d[i]=0;
	}
	void operator += (const BigInt& s){
		len=max(len,s.len);
		for(int i=0;i<len;i++){
			d[i]+=s.d[i];
			d[i+1]+=d[i]/M;
			d[i]%=M;
		}
		if(d[len])len++;
	}
	void Print(){
		printf("%d",d[len-1]);
		for(int i=len-2;i>=0;i--)
			printf("%08d",d[i]);
	}
}f[N][N];
bool vis[N][N];
map<char,int>Last,Pam[N],Pbm[N];
typedef map<char,int>::iterator mc;
void DP(int i,int j){
	if(vis[i][j])return;
	f[i][j].Init();
	f[i][j].d[0]=1,vis[i][j]=1;
	for(mc it=Pam[i].begin();it!=Pam[i].end();it++)
		if(Pbm[j].count(it->first)){
			DP(it->second,Pbm[j][it->first]);
			f[i][j]+=f[it->second][Pbm[j][it->first]];
		}
}
int n,m,opt;
char A[N],B[N],Buf[N];
void Print(int i,int j,int len){
	Buf[len]=0;
	puts(Buf);
	for(mc it=Pam[i].begin();it!=Pam[i].end();it++)
		if(Pbm[j].count(it->first)){
			Buf[len]=it->first;
			Print(it->second,Pbm[j][it->first],len+1);
		}
}
int main(){
	scanf("%d%d%s%s%d",&n,&m,A+1,B+1,&opt);
	Last.clear();
	for(int i=n;i>=0;i--){
		Pam[i]=Last;
		Last[A[i]]=i;
	}
	Last.clear();
	for(int i=m;i>=0;i--){
		Pbm[i]=Last;
		Last[B[i]]=i;
	}
	if(opt)Print(0,0,0);
	DP(0,0);
	f[0][0].Print();
}
