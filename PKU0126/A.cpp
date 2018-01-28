#include<stdio.h>
#include<iostream>
#include<algorithm>
using namespace std;
typedef long long ll;

ll p,q,m,r,a[60],b[60],c[60];
ll A,B,C;
ll i,j,k,t,f;
bool check(ll x){
	for(j=1,t=0,k=1;j<A;j++,k*=x){
		if(a[j]>=x)return 0;
		t+=a[j]*k;
	}
	for(j=1,m=0,k=1;j<B;j++,k*=x){
		if(b[j]>=x)return 0;
		m+=b[j]*k;
	}
	for(j=1,f=0,k=1;j<C;j++,k*=x){
		if(c[j]>=x)return 0;
		f+=c[j]*k;
	}
	if(t*m==f)return 1;
	return 0;
}
int main(){
	cin>>p>>q>>r;
	for(j=p,A=1;j;j/=10,A++)a[A]=j%10;
	for(j=q,B=1;j;j/=10,B++)b[B]=j%10;
	for(j=r,C=1;j;j/=10,C++)c[C]=j%10;
	for(i=2;i<=16;i++){
		if(check(i)){
			cout<<i;
			return 0;
		}
	}
	puts("0");
}
