#define N 1000000
struct Graph
{
	struct node
	{
		int next,to,dis;
	} edge[N<<1];
	int head[N/2];
	inline void add(int u,int v,int w)
	{
		edge[++cnt].next=head[u];
		edge[cnt].to=v;
		edge[cnt].dis=w;
		head[u]=cnt;
	}
};