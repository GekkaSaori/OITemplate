#define maxn 10005
struct UnionFindSet
{
	int x,y,v;
	int fat[maxn];
	UnionFindSet()
	{
		for(int i=0; i<maxn; i++)
			fat[i]=i;
	}
	inline int father(int x)
	{
		if(fat[x]!=x)
			fat[x]=father(fat[x]);
		return fat[x];
	}
	inline void unionn(int x,int y)
	{
		int fa=father(x);
		int fb=father(y);
		if(fa!=fb)
			fat[fa]=fb;
	}
};
struct Edge
{
	int pre,to,w;
	bool operator < (const Edge &b) const
	{
		return this->w < b.w;
	}
};
struct Graph
{
	Edge edge[maxn];
	int cnt=0;
	inline void AddEdge(int u,int v,int w)
	{
		edge[++cnt].pre=u;
		edge[cnt].to=v;
		edge[cnt].w=w;
	}
};
Graph g;
UnionFindSet s;
int Kruskal(int EdgeNumber)
{
	sort(g.edge+1,g.edge+1+EdgeNumber);
	int n=1,ans=0;
	while(n<EdgeNumber-1)
	{
		if(s.father(g.edge[n].pre)!=s.father(g.edge[n].to))
		{
			s.unionn(g.edge[n].pre,g.edge[n].to);
			ans+=g.edge[n].w;
		}
		n++;
	}
	return ans;
}