struct BIT{
    long long c[N];
    int n;
    BIT()
    {
        memset(c,0,sizeof(c));
        n=0;
    }

    inline int lowbit(int x)
    {
        return x&(-x);
    }
    inline void modify(int x,long long y)
    {
        for(;x<=n;x+=lowbit(x))
            c[x]+=y;
    }
    inline long long query(int x)
    {
        long long ret=0;
        for(;x;x-=lowbit(x))
            ret+=c[x];
        return ret;
    }
    inline long long query(int l,int r)
    {
        return query(r)-query(l-1);
    }
};
