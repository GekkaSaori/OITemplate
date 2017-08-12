#define N 1000000
struct Graph
{
	struct node
	{
		int next,to,dis;
	} edge[N];
	int head[N];
	inline void add(int u,int v,int w)
	{
		edge[++cnt].next=head[u];
		edge[cnt].to=v;
		edge[cnt].dis=w;
		head[u]=cnt;
	}
};
Graph g;
struct Dijkstra
{
	struct NODE
	{
		int x,y;
		bool operator < (NODE a)const
		{
			return x>a.x;
		}
	};
	priority_queue<NODE>q;
	int cnt,n,m,s,t,dis[N/2];
	bool visit[N/2];
	inline void dijkstra()
	{
		memset(dis,1,sizeof(dis));
		dis[s]=0;
		NODE a;
		a.x=dis[s];
		a.y=s;
		q.push(a);
		while(!q.empty())
		{
			NODE a=q.top();
			q.pop();
			if(visit[a.x]) continue;
			int v=a.y;
			visit[v]=1;
			for(int i=g.head[v]; i; i=g.edge[i].next)
			{
				if(dis[g.edge[i].to]>g.edge[i].dis+dis[v])
				{
					dis[g.edge[i].to]=g.edge[i].dis+dis[v];
					NODE a;
					a.x=dis[g.edge[i].to];
					a.y=g.edge[i].to;
					q.push(a);
				}
			}
		}
		printf("%d",dis[t]);
	}
};
