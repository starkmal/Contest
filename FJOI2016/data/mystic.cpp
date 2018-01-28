# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <iostream>
# include <algorithm>
# include <cmath>
# include <string>
using namespace std;

const int M=200010,MM=5000010;
int root[MM],ch[MM][2],s[MM],ind=0,m;
int n,a[M],mm=0;

inline void update(int &root,int oldrt,int l,int r,int x) {
	root=++ind;
	if(l==r) {
		s[root]=s[oldrt]+x;
		return;
	}
	int mid=l+r>>1;
	if(x<=mid) ch[root][1]=ch[oldrt][1],update(ch[root][0],ch[oldrt][0],l,mid,x);
	if(x>mid) ch[root][0]=ch[oldrt][0],update(ch[root][1],ch[oldrt][1],mid+1,r,x);	
	s[root]=s[ch[root][0]]+s[ch[root][1]];	
}

inline int query(int rootx,int rooty,int l,int r,int ql,int qr) {
	if(ql<=l && r<=qr) return s[rootx]-s[rooty];
	int mid=l+r>>1;
	if(qr<=mid) {
		return query(ch[rootx][0],ch[rooty][0],l,mid,ql,qr);
	} else if(ql>mid) {
		return query(ch[rootx][1],ch[rooty][1],mid+1,r,ql,qr);
	} else {
		return query(ch[rootx][0],ch[rooty][0],l,mid,ql,qr) + query(ch[rootx][1],ch[rooty][1],mid+1,r,ql,qr);
	}
}

inline int qu(int l,int r) {
	int lasgg=1111111111;
	for (int t=1,gg;;) {
		gg=query(root[r],root[l-1],1,mm,1,t);
		if(gg==lasgg) return t;
		t=gg+1;
		lasgg=gg;
	}
}

int main() {
	freopen("mystic.in","r",stdin);
	freopen("mystic.out","w",stdout);
	
	scanf("%d",&n);
	for (int i=1;i<=n;++i) {
		scanf("%d",&a[i]);
		if(a[i]>mm) mm=a[i];
	}
	
	for (int i=1;i<=n;++i) {
		update(root[i],root[i-1],1,mm,a[i]);
	}
	
	/*
	for (int i=1;i<=n;++i) {
		printf("root[%d]=%d\n",i,root[i]);
	}
	for (int i=1;i<=30;++i) {
		printf("i=%d, lch=%d, rch=%d, l=%d, r=%d, s=%d\n",i,ch[i][0],ch[i][1],L[i],R[i],s[i]);
	}
	*/
	
	scanf("%d",&m);
	for (int i=1,l,r;i<=m;++i) {
		scanf("%d%d",&l,&r);
		printf("%d\n",qu(l,r));
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
