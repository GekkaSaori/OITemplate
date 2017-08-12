#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define N 1000000
#define inf 0x3f3f3f3f
struct Graph
{
	struct node
	{
		int next,to,dis;
	} edge[N<<1];
	int head[N/2],cnt;
	Graph(){cnt=1;}
	void add(int u,int v,int w)
	{
		edge[++cnt].next=head[u];
		edge[cnt].to=v;
		edge[cnt].dis=w;
		head[u]=cnt;
	}
};
Graph g;
class Dinic
{
	private:
		int q[N<<1],h[N<<1],ans,n,S,T;
		inline void insert(int u,int v,int f)
		{
			g.add(u,v,f);
			g.add(v,u,0);
		}

		bool bfs()
		{
			int t=0,w=1;
			memset(h,-1,sizeof(h));
			q[t]=S;
			h[S]=0;
			while(t<w)
			{
				int now=q[t++];
				for(int i=g.head[now]; i; i=g.edge[i].next)
				{
					int v=g.edge[i].to;
					if(h[v]==-1&&g.edge[i].to)
					{
						h[v]=h[now]+1;
						q[w++]=v;
					}
				}
			}
			if(h[T]!=-1) return 1;
			return 0;
		}

		int dfs(int x,int f)
		{
			if(x==T) return f;
			int w,used=0;
			for(int i=g.head[x]; i; i=g.edge[i].next)
			{
				int v=g.edge[i].to;
				if(h[v]==h[x]+1)
				{
					w=dfs(v,min(f-used,g.edge[i].to));
					g.edge[i].to-=w;
					g.edge[i^1].to+=w;
					used+=w;
					if(used==f) return f;
				}

			}
			if(!used) h[x]=-1;
			return used;
		}
	public:
		void dinic()
		{
			while(bfs())
				ans+=dfs(S,inf);
		}
};
