struct SegmentTreeTypeAdd
{
	struct node
	{
		int l,r,w,f;//left,right,weight,flag;
		node()
		{
			l=r=w=f=0;
		}
	} tree[400001];
	inline void build(int k,int ll,int rr)//建树
	{
		//用法：build(节点编号,左孩子,右孩子);
		//初始化：build(1,1,节点个数);
		tree[k].l=ll,tree[k].r=rr;
		if(tree[k].l==tree[k].r)
		{
			scanf("%d",&tree[k].w);
			return;
		}
		int m=(ll+rr)/2;
		build(k*2,ll,m);
		build(k*2+1,m+1,rr);
		tree[k].w=tree[k*2].w+tree[k*2+1].w;
	}
	inline void down(int k)//标记下传
	{
		//用法：down(需要下传标记的根节点);
		tree[k*2].f+=tree[k].f;
		tree[k*2+1].f+=tree[k].f;
		tree[k*2].w+=tree[k].f*(tree[k*2].r-tree[k*2].l+1);
		tree[k*2+1].w+=tree[k].f*(tree[k*2+1].r-tree[k*2+1].l+1);
		tree[k].f=0;
	}
	inline void ask_point(int k)//单点查询
	{
		//用法：ask_point(需要查询的点的编号);
		if(tree[k].l==tree[k].r)
		{
			ans=tree[k].w;
			return ;
		}
		if(tree[k].f) down(k);
		int m=(tree[k].l+tree[k].r)/2;
		if(x<=m) ask_point(k*2);
		else ask_point(k*2+1);
	}
	inline void change_point(int k)//单点修改
	{
		//用法：change_point(需要修改的点的编号);
		if(tree[k].l==tree[k].r)
		{
			tree[k].w+=y;
			return;
		}
		int m=(tree[k].l+tree[k].r)/2;
		if(x<=m) change_point(k*2);
		else change_point(k*2+1);
		tree[k].w=tree[k*2].w+tree[k*2+1].w;
	}
	inline void ask_interval(int k)//区间查询
	{
		//用法：ask_iterval(查询起点);
		if(tree[k].l>=a&&tree[k].r<=b)//a与b为需要查询的区间
		{
			ans+=tree[k].w;
			return;
		}
		if(tree[k].f) down(k);
		int m=(tree[k].l+tree[k].r)/2;
		if(a<=m) ask_interval(k*2);
		if(b>m) ask_interval(k*2+1);
	}
	inline void change_interval(int k)//区间修改
	{
		//用法：change_interval(修改起点);
		if(tree[k].l>=a&&tree[k].r<=b)//a与b为需要修改的区间
		{
			tree[k].w+=(tree[k].r-tree[k].l+1)*y;
			tree[k].f+=y;
			return;
		}
		if(tree[k].f) down(k);//若有孩子节点，下传标记
		int m=(tree[k].l+tree[k].r)/2;//二分处理
		if(a<=m) change_interval(k*2);
		if(b>m) change_interval(k*2+1);
		tree[k].w=tree[k*2].w+tree[k*2+1].w;
	}
};