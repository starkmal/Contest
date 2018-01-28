#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=200005;

int n,m;
int Tote,Last[N],Next[N],End[N];
void Ins(int x,int y){
	End[++Tote]=y;
	Next[Tote]=Last[x];
	Last[x]=Tote;
}

namespace Pri_Tree{
	struct Node{
		Node* Son[2];
		int Sum;
	}pool[N*100],*Root[N],*null,*tl;
	void Build(Node* &p,int l,int r){
		p=++tl;
		if(l<r){
			register int mid=l+r>>1;
			Build(p->Son[0],l,mid);
			Build(p->Son[1],mid+1,r);
		}else p->Son[0]=p->Son[1]=null;
	}
	void Init(){
		null=tl=pool;
		null->Sum=0;
		null->Son[0]=null->Son[1]=null;
		Build(Root[0],1,n);
	}
	Node* Copy(Node* p){
		Node* x=++tl;
		x->Sum=p->Sum;
		x->Son[0]=p->Son[0];
		x->Son[1]=p->Son[1];
		return x;
	}
	Node* Insert(Node* p,int l,int r,int k){
		Node* rt=Copy(p);
		rt->Sum++;
		if(l==r)return rt;
		register int mid=l+r>>1;
		if(k<=mid)rt->Son[0]=Insert(rt->Son[0],l,mid,k);
		else rt->Son[1]=Insert(rt->Son[1],mid+1,r,k);
		return rt;
	}
	int GetSum(Node* p,int l,int r,int x,int y){
		if(x<=l&&r<=y)return p->Sum;
		register int mid=l+r>>1,sum=0;
		if(l<=y&&mid>=x)sum+=GetSum(p->Son[0],l,mid,x,y);
		if(mid<y&&r>=x)sum+=GetSum(p->Son[1],mid+1,r,x,y);
		return sum;
	}

	int GetAns(int z,int x,int y){return GetSum(Root[z],1,n,x,y);}
	void Maintain(int i){Root[i]=Copy(Root[i-1]);}
	void Add(int x,int y){Root[x]=Insert(Root[x-1],1,n,y);}
}
int vtt,Dep[N],Fa[N],Top[N],Id[N],Son[N];
int Dfs1(int x){
	register int i,Size=1,maxx=0,tmp,u;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		tmp=Dfs1(u);
		Size+=tmp;
		if(tmp>maxx)maxx=tmp,Son[x]=u;
	}
	return Size;
}
void Dfs2(int x,int anc){
	Id[x]=++vtt;
	Top[x]=anc;
	Dep[x]=Dep[Fa[x]]+1;
	if(Son[x])Dfs2(Son[x],anc);
	register int i,u;
	for(i=Last[x];i;i=Next[i]){
		u=End[i];
		if(u!=Son[x])Dfs2(u,u);
	}
}
int GetAns(int x,int y,int z){
	register int sum1=0,sum2=0;
	while(Top[x]!=Top[y]){
		if(Dep[Top[x]]<Dep[Top[y]])swap(x,y);
		sum1+=Dep[x]-Dep[Top[x]]+1;
		if(z>0)sum2+=Pri_Tree::GetAns(z,Id[Top[x]],Id[x]);
		x=Fa[Top[x]];
	}
	if(Dep[x]<Dep[y])swap(x,y);
	sum1+=Dep[x]-Dep[y]+1;
	if(z>0)sum2+=Pri_Tree::GetAns(z,Id[y],Id[x]);
	printf("%d %d\n",sum1,sum2);
}
int main(){
	register int i,j,k,x,y,z,opt;
	int root;
	scanf("%d",&n);
	for(i=1;i<=n;i++){
		scanf("%d",&x);
		if(x!=0)Fa[i]=x,Ins(x,i);
		else root=i;
	}
	Pri_Tree::Init();
	Dfs1(root);
	Dfs2(root,root);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d%d",&x,&y,&z);
			GetAns(x,y,i-z-1);
			Pri_Tree::Maintain(i);
		}
		else {
			scanf("%d",&x);
			Pri_Tree::Add(i,Id[x]);
		}
	}
}
