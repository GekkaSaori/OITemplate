#include<cstdio>
#define N 100010
using namespace std;
int root,nn,n,tot;
class SPLAY
{
	private:
		int fa[N],ch[N][2],siz[N],cnt[N];
		
		int son(int x)
		{
			return x==ch[fa[x]][1];
		}

		void pushup(int rt)
		{
			int l=ch[rt][0],r=ch[rt][1];
			siz[rt]=siz[l]+siz[r]+cnt[rt];
		}

		void rotate(int x)
		{
			int y=fa[x],z=fa[y],b=son(x),c=son(y),a=ch[x][!b];
			if(z) ch[z][c]=x;
			else root=x;
			fa[x]=z;
			if(a) fa[a]=y;
			ch[y][b]=a;
			ch[x][!b]=y;
			fa[y]=x;
			pushup(y);
			pushup(x);
		}

		void splay(int x,int i)
		{
			while(fa[x]!=i)
			{
				int y=fa[x],z=fa[y];
				if(z==i)
				{
					rotate(x);
				}
				else
				{
					if(son(x)==son(y))
					{
						rotate(y);
						rotate(x);
					}
					else
					{
						rotate(x);
						rotate(x);
					}
				}
			}
		}
	public:
		int data[N];
		void ins(int &rt,int x)
		{
			if(rt==0)
			{
				rt=++nn;
				data[nn]=x;
				siz[nn]=cnt[nn]=1;
				return;
			}
			if(x==data[rt])
			{
				cnt[rt]++;
				siz[rt]++;
				return;
			}
			if(x<data[rt])
			{
				ins(ch[rt][0],x);
				fa[ch[rt][0]]=rt;
				pushup(rt);
			}
			else
			{
				ins(ch[rt][1],x);
				fa[ch[rt][1]]=rt;
				pushup(rt);
			}
		}

		int getpre(int rt,int x)
		{
			int p=rt,ans;
			while(p)
			{
				if(x<=data[p])
				{
					p=ch[p][0];
				}
				else
				{
					ans=p;
					p=ch[p][1];
				}
			}
			return ans;
		}

		int getsuc(int rt,int x)
		{
			int p=rt,ans;
			while(p)
			{
				if(x>=data[p])
				{
					p=ch[p][1];
				}
				else
				{
					ans=p;
					p=ch[p][0];
				}
			}
			return ans;
		}

		int getmn(int rt)
		{
			int p=rt,ans=-1;
			while(p)
			{
				ans=p;
				p=ch[p][0];
			}
			return ans;
		}

		void del(int rt,int x)
		{
			if(data[rt]==x)
			{
				if(cnt[rt]>1)
				{
					cnt[rt]--;
					siz[rt]--;
				}
				else
				{
					splay(rt,0);
					int p=getmn(ch[rt][1]);
					if(p!=-1)
					{
						splay(p,rt);
						root=p;
						fa[p]=0;
						ch[p][0]=ch[rt][0];
						fa[ch[rt][0]]=p;
						pushup(p);
					}
					else
					{
						root=ch[rt][0];
						fa[ch[rt][0]]=0;
					}
				}
				return;
			}
			if(x<data[rt])
			{
				del(ch[rt][0],x);
				pushup(rt);
			}
			else
			{
				del(ch[rt][1],x);
				pushup(rt);
			}
		}

		int getk(int rt,int k)
		{
			if(data[rt]==k)
			{
				splay(rt,0);
				if(ch[rt][0]==0)
				{
					return 1;
				}
				else
				{
					return siz[ch[rt][0]]+1;
				}
			}
			if(k<data[rt]) return getk(ch[rt][0],k);
			else return getk(ch[rt][1],k);
		}

		int getkth(int rt,int k)
		{
			int l=ch[rt][0];
			if(siz[l]+1<=k&&k<=siz[l]+cnt[rt]) return data[rt];
			if(k<siz[l]+1) return getkth(ch[rt][0],k);
			if(siz[l]+cnt[rt]<k) return getkth(ch[rt][1],k-(siz[l]+cnt[rt]));
		}
};

SPLAY s;
int main()
{
	scanf("%d",&n);
	while(n--)
	{
		int opt,x;
		scanf("%d%d",&opt,&x);
		if(opt==1)
		{
			tot++;
			s.ins(root,x);
		}
		if(opt==2)
		{
			tot--;
			s.del(root,x);
		}
		if(opt==3)
		{
			printf("%d\n",s.getk(root,x));
		}
		if(opt==4)
		{
			printf("%d\n",s.getkth(root,x));
		}
		if(opt==5)
		{
			printf("%d\n",s.data[s.getpre(root,x)]);
		}
		if(opt==6)
		{
			printf("%d\n",s.data[s.getsuc(root,x)]);
		}
	}
	return 0;
}
