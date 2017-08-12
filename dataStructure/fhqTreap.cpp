#include<cstdio>
#include<algorithm>
#define N 100010
using namespace std;

struct TreapType
{
	TreapType *l,*r;
	int key,fix,size;
	TreapType(int _key):fix(rand()),key(_key),l(NULL),r(NULL),size(1) {}
	inline void update()
	{
		size=1+(l?l->size:0)+(r?r->size:0);
	}
}*root;

int T;

typedef pair<TreapType*,TreapType*> Droot;

inline int Size(TreapType *x)
{
	return x?x->size:0;
}

Droot Split(TreapType *x,int k)
{
	if(!x) return Droot(NULL,NULL);
	Droot y;
	if(Size(x->l)>=k)
	{
		y=Split(x->l,k);
		x->l=y.second;
		x->update();
		y.second=x;
	}
	else
	{
		y=Split(x->r,k-Size(x->l)-1);
		x->r=y.first;
		x->update();
		y.first=x;
	}
	return y;
}

TreapType* Merge(TreapType *A,TreapType *B)
{
	if(!A) return B;
	if(!B) return A;
	if(A->fix<B->fix)
	{
		A->r=Merge(A->r,B);
		A->update();
		return A;
	}
	else
	{
		B->l=Merge(A,B->l);
		B->update();
		return B;
	}
}

int Getkth(TreapType *x,int k)
{
	if(!x) return 0;
	return k<=x->key?Getkth(x->l,k):Getkth(x->r,k)+Size(x->l)+1;
}

int Findkth(int k)
{
	Droot x=Split(root,k-1);
	Droot y=Split(x.second,1);
	TreapType *ans=y.first;
	root=Merge(Merge(x.first,ans),y.second);
	return ans->key;
}

void Insert(int v)
{
	int k=Getkth(root,v);
	Droot x=Split(root,k);
	TreapType *now=new TreapType(v);
	root=Merge(Merge(x.first,now),x.second);
}

void Delete(int v)
{
	int k=Getkth(root,v);
	Droot x=Split(root,k);
	Droot y=Split(x.second,1);
	root=Merge(x.first,y.second);
}

int Pre(int v)
{
	int k=Getkth(root,v);
	Droot x=Split(root,k-1);
	Droot y=Split(x.second,1);
	TreapType *ans=y.first;
	root=Merge(Merge(x.first,ans),y.second);
	return ans->key;
}

int Suc(int v)
{
	int k=Getkth(root,v+1);
	Droot x=Split(root,k);
	Droot y=Split(x.second,1);
	TreapType *ans=y.first;
	root=Merge(Merge(x.first,ans),y.second);
	return ans->key;
}

int main()
{
	scanf("%d",&T);
	while(T--)
	{
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			Insert(x);
		}
		if(opt==2)
		{
			Delete(x);
		}
		if(opt==3)
		{
			printf("%d\n",Getkth(root,x)+1);
		}
		if(opt==4)
		{
			printf("%d\n",Findkth(x));
		}
		if(opt==5)
		{
			printf("%d\n",Pre(x));
		}
		if(opt==6)
		{
			printf("%d\n",Suc(x));
		}
	}
	return 0;
}