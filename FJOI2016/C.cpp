#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=100005,M=N<<4;

int n,m,a[N];
int tot,Hash[N];
int Totn,Root[N],Son[M][2],Sum[M];
void Build(int &p,int l,int r){
    p=++Totn;
    if(l<r){
         int mid=l+r>>1;
         Build(Son[p][0],l,mid);
         Build(Son[p][1],mid+1,r);
    }
}
int Copy(int p){
    int x=++Totn;
    Son[x][1]=Son[p][1];
    Son[x][0]=Son[p][0];
    Sum[x]=Sum[p];
    return x;
}
int Insert(int p,int l,int r,int k,int d){
    int rt=Copy(p);
	Sum[rt]+=d;
    if(l==r)return rt;
    int mid=l+r>>1;
    if(k<=mid)Son[rt][0]=Insert(Son[rt][0],l,mid,k,d);
    else Son[rt][1]=Insert(Son[rt][1],mid+1,r,k,d);
    return rt;
}
int Query(int p1,int p2,int l,int r,int k){
	if(l==r)return Sum[p2]-Sum[p1];
	int mid=l+r>>1,rt=0;
	if(k>mid)rt=Sum[Son[p2][0]]-Sum[Son[p1][0]]+Query(Son[p1][1],Son[p2][1],mid+1,r,k);
	else rt=Query(Son[p1][0],Son[p2][0],l,mid,k);
	return rt;
}
int main(){
    int i,j,k,t;
    int x,y,ans;
    scanf("%d",&n);
    for(i=1;i<=n;i++)scanf("%d",&a[i]),Hash[i]=a[i];
    sort(Hash+1,Hash+1+n);
    tot=unique(Hash+1,Hash+1+n)-Hash-1;
    Build(Root[0],1,tot);
    for(i=1;i<=n;i++)
      Root[i]=Insert(Root[i-1],1,tot,lower_bound(Hash+1,Hash+1+tot,a[i])-Hash,a[i]);
    scanf("%d",&m);
    while(m--){
        scanf("%d%d",&x,&y);
        ans=1;
        while(1){
			t=Query(Root[x-1],Root[y],1,tot,upper_bound(Hash+1,Hash+1+tot,ans)-Hash-1);
			if(t<ans)break;
			ans=t+1;
		}
        printf("%d\n",ans);
    }
}
