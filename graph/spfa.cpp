#define N 1000000
struct SPFA
{
	queue<int> q;
	bool vis[N];
	int dis[N];
	SPFA()
	{
		memset(vis,0,sizeof(vis));
		memset(dis,0,sizeof(dis));
	}
	void spfa(int p)
	{
		q.push(p);
		vis[p]=true;
		while(!q.empty())
		{
			int t=q.front();
			q.pop();
			vis[t]=false;
			for(int i=1; i<=n; i++)
			{
				if(dis[i]>dis[t]+map[t][i])
				{
					dis[i]=dis[t]+map[t][i];
					if(!vis[i])
						q.push(i);
				}
			}
		}
		printf("%d",dis[ep]);
	}
};