#include<stdio.h>
#include<algorithm>
#include<vector>
#include<set>
#include<ctype.h>
#include<stack>
using namespace std;
typedef long long ll;
const int N=50005;
inline ll _R(){
	ll d=0;char t=getchar();
	while(!isdigit(t))t=getchar();
	for(;isdigit(t);t=getchar())d=(d<<1)+(d<<3)+t-'0';
	return d;
}
ll ksm(ll a,ll b,ll c){
	ll ans=1;
	for(;b;b>>=1,a=a*a%c)
		if(b&1)ans=ans*a%c;
	return ans;
}
ll getphi(ll x){
	ll ans=x;
	for(ll i=2;i*i<=x;i++)
		if(x%i==0){
			ans-=ans/i;
			while(x%i==0)x/=i;
		}
	if(x>1)ans-=ans/x;
	return ans;
}
int n,m;
ll P,mod,c,a[N];

ll tot,S[N];
vector<ll>V[N];
vector<ll>::iterator it[N];
set<int>T;
stack<set<int>::iterator>s;

struct Node{
	Node* Son[2];
	ll Sum;
}*Root,*null,*tl,pool[N<<2];
void Init(){
	Root=null=tl=pool;
	null->Sum=0;
	null->Son[0]=null->Son[1]=null;
}
void Build(Node* &p,int l,int r){
	p=++tl;
	if(l<r){
		int mid=l+r>>1;
		Build(p->Son[0],l,mid);
		Build(p->Son[1],mid+1,r);
		p->Sum=(p->Son[0]->Sum+p->Son[1]->Sum)%P;
	}else p->Sum=a[l];
}
void Modify(Node* &p,int l,int r,int k,ll d){
	if(l==r){
		p->Sum=d%P;
		return;
	}
	int mid=l+r>>1;
	if(k<=mid)Modify(p->Son[0],l,mid,k,d);
	else Modify(p->Son[1],mid+1,r,k,d);
	p->Sum=(p->Son[0]->Sum+p->Son[1]->Sum)%P;
}
ll GetSum(Node* p,int l,int r,int x,int y){
	if(x<=l&&r<=y)return p->Sum;
	int mid=l+r>>1;
	ll sum=0;
	if(l<=y&&mid>=x)sum+=GetSum(p->Son[0],l,mid,x,y);
	if(mid<y&&r>=x)sum=(sum+GetSum(p->Son[1],mid+1,r,x,y))%P;
	return sum;
}

int main(){
	freopen("verbinden.in","r",stdin);
	freopen("verbinden.out","w",stdout);
	int i,j,k,opt,x,y;
	ll t,r,ans;
	n=_R(),m=_R(),P=_R(),c=_R();
	S[0]=P;
	while(S[tot]!=1)S[tot+1]=getphi(S[tot]),tot++;
	for(i=1;i<=n;i++){
		a[i]=_R(),r=-1;
		for(j=1;j<=tot;j++){
			t=a[i]%S[j];
			for(k=j-1;k>=1;k--)t=ksm(c,t,S[k]);
			if(t==r)break;
			V[i].push_back(t);r=t;
		}
		it[i]=V[i].begin();
	}

	for(i=1;i<=n;i++)T.insert(i);
	Init();
	Build(Root,1,n);
	for(i=1;i<=m;i++){
		opt=_R(),x=_R(),y=_R();
		if(opt==0){
			for(set<int>::iterator tt=T.lower_bound(x);tt!=T.end()&&*tt<=y;tt++){
				Modify(Root,1,n,*tt,ksm(c,*it[*tt],P));
				it[*tt]++;
				if(it[*tt]==V[*tt].end())s.push(tt);
			}
			while(!s.empty())T.erase(s.top()),s.pop();
		}
		else printf("%lld\n",GetSum(Root,1,n,x,y));
	}
}
