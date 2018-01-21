#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=150;
#define debug 0

char str[N],buf[N][N],now[N],tsh[N];
int tot;
bool isCap(char *c){
	int len=strlen(c),i;
	if(c[0]<'A'||c[0]>'Z')return 0;
	if(len<2)return 0;
	for(i=1;i<len;i++)
		if(c[i]>='A'&&c[i]<='Z')return 0;
	return 1;
}
void clearbuf(){
	if(!tot)return;
	if(tot==1){
		tot=0;
		printf("%s",buf[1]);
		return;
	}
	int i;
	for(i=1;i<=tot;i++)putchar(buf[i][0]);
	putchar(' ');putchar('(');
	for(i=1;i<=tot;i++){
		printf("%s",buf[i]);
		if(i<tot)putchar(' ');
	}
	putchar(')');
	tot=0;
}
int main(){
	int n,m,i,j,k,flag;
	while(scanf("%[^\n]",str)!=EOF){
		getchar();
#if debug
		puts(str);
#endif
		n=strlen(str);
		k=0;
		while(k<n){
			j=0,flag=0;
			for(;k<n&&!(str[k]>='A'&&str[k]<='Z')&&!(str[k]>='a'&&str[k]<='z');k++){
				tsh[j++]=str[k];
				if(j>1||tsh[j-1]!=' ')flag=1;
			}
			tsh[j]='\0';
			if(k>=n){
				clearbuf();
				printf("%s",tsh);
				break;
			}
			if(flag){
				clearbuf();
				printf("%s",tsh);
			}
			sscanf(str+k,"%[A-Za-z]",now);
//			puts(now);
			m=strlen(now),k+=m;
			if(!isCap(now)){
				clearbuf();
				if(!flag)printf("%s",tsh);
				printf("%s",now);
			}
			else {
				if(!flag&&tot==0)printf("%s",tsh);
				sscanf(now,"%s",buf[++tot]);
			}
		}
		memset(str,0,sizeof(str));
		clearbuf();
		putchar('\n');
	}
}
