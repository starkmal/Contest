#include<stdio.h>
#include<algorithm>
#include<set>
#include<stack>
using namespace std;
const int N=300005;

int n,m,Ans[N];
set<int>s;
stack<set<int>::iterator>t;
int main(){
	int i,j,k,x,y;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;i++)s.insert(i);
	for(i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&k);
		for(set<int>::iterator it=s.lower_bound(x);it!=s.end()&&*it<=y;it++)
			if(*it!=k)
				Ans[*it]=k,t.push(it);
		while(!t.empty())s.erase(t.top()),t.pop();
	}
	for(i=1;i<=n;i++)printf("%d ",Ans[i]);
}
