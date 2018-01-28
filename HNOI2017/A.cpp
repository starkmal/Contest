#include<stdio.h>
#include<algorithm>
#include<map>
using namespace std;
const int N=100005;

int m;

int Totn;
struct Node{
	Node *Fa,*Son[2],*_real_fa,*_real_Son[2];
	int Size;
	bool rev;
}pool[N],*root,*null;
inline void PushUp(Node* x){
	x->Size=x->Son[0]->Size+x->Son[1]->Size+1;
}
inline bool isRoot(Node* x){
	return x->Fa==null||(x->Fa->Son[0]!=x&&x->Fa->Son[1]!=x);
}
inline void Rotate(Node* x){
	Node *y=x->Fa,*z=y->Fa;
	int l=y->Son[0]==x,r=l^1;
	if(!isRoot(y))z->Son[z->Son[1]==y]=x;x->Fa=z;
	y->Son[r]=x->Son[l];
	x->Son[l]->Fa=y;
	x->Son[l]=y,y->Fa=x;
	PushUp(y),PushUp(x);
}
inline void Setr(Node* x){
	x->rev^=1;
	swap(x->Son[0],x->Son[1]);
}
inline void PushDown(Node* x){
	if(x->rev){
		x->rev=0;
		if(x->Son[0]!=null)Setr(x->Son[0]);
		if(x->Son[1]!=null)Setr(x->Son[1]);
	}
}
Node* s[N];
int top;
void Splay(Node* x){
	s[top=1]=x;
	for(Node* i=x;!isRoot(i);i=i->Fa)s[++top]=i->Fa;
	while(top)PushDown(s[top--]);
	while(!isRoot(x)){
		Node *y=x->Fa,*z=y->Fa;
		if(!isRoot(y)){
			if(z->Son[0]==y^y->Son[0]==x)Rotate(x);
			else Rotate(y);
		}
		else Rotate(x);
	}
}
void Access(Node* x){
	for(Node *t=null;x!=null;t=x,x=x->Fa){
		Splay(x);
		x->Son[1]=t;
		PushUp(x);
	}
}
void MakeToRoot(Node* x){
	Access(x),Splay(x),Setr(x);
}
void Link(Node* x,Node* y){
	MakeToRoot(x);
	x->Fa=y;
}
void Cut(Node* x,Node* y){
	MakeToRoot(x);
	Access(y),Splay(y);
	x->Fa=y->Son[0]=null;
	PushUp(y);
}

map<int,Node*>M;
typedef map<int,Node*>::iterator mit;
int getDep(Node* x){
	MakeToRoot(root);
	Access(x);
	Splay(x);
	return x->Size;
}

Node* NewNode(){
	Node* x=&pool[++Totn];
	x->_real_fa=x->_real_Son[0]=x->_real_Son[1]=null;
	x->Fa=x->Son[0]=x->Son[1]=null;
}
mit getNode(int v){
	mit it=M.lower_bound(v);
	if(it==M.end()){it--;return it;}
	if(it==M.begin())return it;
	mit jt=it;jt--;
	if(getDep(jt->second)<getDep(it->second))return it;
	else return jt;
}
void LK(Node* fa,Node* x,int l){
	Link(fa,x);
	x->_real_fa=fa;
	fa->_real_Son[l]=x;
}
void DEL(Node* fa,Node* x,int l){
	Cut(fa,x);
	Node *y=x->_real_Son[l^1];
	x->_real_fa=null;
	fa->_real_Son[l]=null;
	if(y!=null)Cut(x,y),LK(fa,y,l);
}
int main(){
	int i,j,k,y,opt;
	scanf("%d",&m);
	null=pool;
	null->Size=0;
	null->Fa=null->Son[0]=null->Son[1]=null;
	null->_real_fa=null->_real_Son[0]=null->_real_Son[1]=null;
	root=null;
	while(m--){
		scanf("%d",&opt);
		if(opt!=1&&opt!=4)continue;
		if(opt==1){
			scanf("%d",&y);
			Node *p=NewNode();
			p->Size=1;
			if(root==null){
				puts("1");
				root=p;
			}
			else{
				mit q=getNode(y);
				Access(q->second),Splay(q->second);
				printf("%d\n",getDep(q->second)+1);
				if(q->first<y)LK(q->second,p,1);
				else LK(q->second,p,0);
			}
			Access(p),Splay(p);
			M.insert(make_pair(y,p));
		}
		else if(opt==2){
			Node *x=M.begin()->second;
			printf("%d\n",getDep(x));

			if(x!=root){
				DEL(x->_real_fa,x,0);
				LK(x,root,1);
				root=x;
			}
		}
		else if(opt==4){
			mit it=M.begin();
			Node *x=it->second;
			printf("%d\n",getDep(x));

			if(x!=root)DEL(x->_real_fa,x,0);
			else {
				if(x->_real_Son[1]==null)root=null;
				else{
					Cut(x,x->_real_Son[1]);
					x->_real_Son[1]->_real_fa=null;
					root=x->_real_Son[1];
				}
			}
			M.erase(it);
		}
		else if(opt==3){
			mit it=M.end();
			it--;
			Node *x=it->second;
			printf("%d\n",getDep(x));
			if(x!=root){
				DEL(x->_real_fa,x,1);
				LK(x,root,0);
				root=x;
			}
		}
		else{
			mit it=M.end();
			it--;
			Node *x=it->second;
			printf("%d\n",getDep(x));
			if(x!=root)DEL(x->_real_fa,x,1);
			else {
				if(x->_real_Son[0]==null)root=null;
				else{
					Cut(x,x->_real_Son[0]);
					x->_real_Son[0]->_real_fa=null;
					root=x->_real_Son[0];
				}
			}
			M.erase(it);
		}
	}
}
