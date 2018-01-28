#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N=200005;

struct Query{
	int dx,l,r,id;
	friend bool operator < (const Query& lhs,const Query& rhs){
		return lhs.dx<rhs.dx||(lhs.dx==rhs.dx&&lhs.r<rhs.r);
	}
}Q[N];
int n,m,tot,Len,a[N];
ll Now,cnt1[N],cnt2[N],Ans[N];
int main(){
	int i,j,k,x1,x2,y1,y2,l,r;
	scanf("%d",&n);
	Len=sqrt(n);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	scanf("%d",&m);
	for(i=1;i<=m;i++){
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		Q[++tot].l=y1,Q[tot].r=y2,Q[tot].id=i;
		if(x2>1)Q[++tot].l=y1,Q[tot].r=x2-1,Q[tot].id=-i;
		if(x1>1)Q[++tot].l=x1-1,Q[tot].r=y2,Q[tot].id=-i;
		if(x1>1&&x2>1)Q[++tot].l=x1-1,Q[tot].r=x2-1,Q[tot].id=i;
	}
	for(i=1;i<=tot;i++){
		if(Q[i].l>Q[i].r)swap(Q[i].l,Q[i].r);
		Q[i].dx=(Q[i].l-1)/Len+1;
	}
	sort(Q+1,Q+1+tot);
	for(i=1,l=r=1,cnt1[a[1]]=1,cnt2[a[1]]=1,Now=1;i<=tot;i++){
		while(r<Q[i].r)Now+=cnt1[a[++r]],cnt2[a[r]]++;
		while(r>Q[i].r)Now-=cnt1[a[r]],cnt2[a[r--]]--;
		while(l>Q[i].l)Now-=cnt2[a[l]],cnt1[a[l--]]--;
		while(l<Q[i].l)Now+=cnt2[a[++l]],cnt1[a[l]]++;
		if(Q[i].id<0)Ans[-Q[i].id]-=Now;
		else Ans[Q[i].id]+=Now;
	}
	for(i=1;i<=m;i++)printf("%lld\n",Ans[i]);
}
