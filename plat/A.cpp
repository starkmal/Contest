#include<stdio.h>
#include<ctype.h>
#include<algorithm>
using namespace std;
typedef double db;
typedef long long ll;
const int N=400005;

int n;
ll Sum,tot=1;
struct Node{
	Node *Son[2];
	ll val,lazy,tot;
}*Root,*tl,*null,pool[N];
void Init(){
	Root=tl=null=pool;
	null->Son[0]=null->Son[1]=null;
	null->val=null->lazy=0;
}
void Build(Node* &p,int l,int r){
	p=++tl;
	p->tot=r-l+1;
	p->Son[0]=p->Son[1]=null;
	if(l<r){
		int mid=l+r>>1;
		Build(p->Son[0],l,mid);
		Build(p->Son[1],mid+1,r);
	}
}
void Setv(Node* p,ll d){
	p->val+=d*p->tot;
	p->lazy+=d;
}
void Putdown(Node* p){
	if(p->Son[0]!=null)Setv(p->Son[0],p->lazy);
	if(p->Son[1]!=null)Setv(p->Son[1],p->lazy);
	p->lazy=0;
}
void Modify(Node* p,int l,int r,int x,int y,ll d){
	if(p->lazy)Putdown(p);
	if(x<=l&&r<=y){
		Setv(p,d);
		return;
	}
	int mid=l+r>>1;
	if(l<=y&&mid>=x)Modify(p->Son[0],l,mid,x,y,d);
	if(mid<y&&r>=x)Modify(p->Son[1],mid+1,r,x,y,d);
}
ll GetVal(Node* p,int l,int r,int k){
	if(p->lazy)Putdown(p);
	if(l==r)return p->val;
	int mid=l+r>>1;
	if(k<=mid)return GetVal(p->Son[0],l,mid,k);
	else return GetVal(p->Son[1],mid+1,r,k);
}
int main(){
	int i,j,k,opt,x,y;
	scanf("%d",&n);
	Init();
	n++;
	Build(Root,1,n);
	for(i=1;i<n;i++){
		scanf("%d",&opt);
		if(opt==1){
			scanf("%d%d",&x,&y);
			Modify(Root,1,n,1,x,y);
			Sum+=x*y;
		}
		else if(opt==2){
			scanf("%d",&x);
			tot++;
			Modify(Root,1,n,tot,tot,x);
			Sum+=x;
		}
		else {
			k=GetVal(Root,1,n,tot);
			Modify(Root,1,n,tot,tot,-k);
			Sum-=k,tot--;
		}
		printf("%.6lf\n",(db)Sum/tot);
	}
}
