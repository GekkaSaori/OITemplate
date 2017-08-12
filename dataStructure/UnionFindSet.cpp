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