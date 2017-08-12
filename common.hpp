#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<queue>
#define inf 0x3f3f3f3f
using namespace std;

typedef long long ll;

//读入优化，支持整数
template<typename T>  
inline void read(T& s) {  
    s=0;T f=1;char ch=getchar();  
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}  
    while(ch>='0'&&ch<='9'){s=s*10+(T)ch-'0';ch=getchar();}
	s*=f;  
    return;  
}

//最大公约数，支持整数
template<typename T> 
T Gcd(T a,T b){
    if(!b)return a;
    else return Gcd(b,a%b);
}

//快速幂，支持整数
template<typename T> 
T Pow(T a,T b,T c){
    int ans=1,base=a;
    while(b){
    	if(b&1)
			ans=(ans%c*base%c)%c;
		base=(base%c*base%c)%c;
		b>>=1;
	}
	return ans%c;
}


#define MAX_N_FOR_UFS 1000005
struct UFS{
	private:
	int fat[MAX_N_FOR_UFS];
	inline int father(int x){
		if(fat[x]!=x)
			fat[x]=father(fat[x]);
		return fat[x];
	}
	public:
	UFS(){
		for(int i=0; i<MAX_N_FOR_UFS; i++)
			fat[i]=i;
	}
	inline void unionn(int x,int y){
		int fa=father(x);
		int fb=father(y);
		if(fa!=fb)
			fat[fa]=fb;
	}
};

//fhq Treap,int 
#define N_T 500005
struct Treap{ 
	private:
	int ch[N_T][2],val[N_T];  
	int pri[N_T],siz[N_T];
	int mark[N_T];  
	int sz,root;
	int x,y,z;
	void update(int x) {  
    	siz[x]=1+siz[ch[x][0]]+siz[ch[x][1]];  
	}  
	int new_node(int v) {  
	    siz[++sz]=1; val[sz]=v;  
	    pri[sz]=rand(); return sz;  
	}  
	int merge(int x,int y) {  
	    if (!x || !y) return x+y;  
	    if (pri[x]<pri[y]) {  
	        ch[x][1]=merge(ch[x][1],y);  
	        update(x); return x;  
	    }  
	    else {  
	        ch[y][0]=merge(x,ch[y][0]);  
	        update(y); return y;  
	    }  
	}  
	void split(int now,int k,int &x,int &y) {  
	    if (!now)x=y=0;  
	    else {  
	        if(val[now]<=k) x=now,split(ch[now][1],k,ch[now][1],y);  
	        else y=now,split(ch[now][0],k,x,ch[now][0]);  
	        update(now);  
	    }  
	}  
	int kth(int now,int k) {  
	    while(true)  
	    {  
	        if(k<=siz[ch[now][0]])  
	            now=ch[now][0];  
	        else  
	            if(k==siz[ch[now][0]]+1) return now;  
	            else k-=siz[ch[now][0]]+1,now=ch[now][1];  
	    }  
	}
	public: 
	void Insert(int node){//插入 
		split(root,node,x,y);  
        root=merge(merge(x,new_node(node)),y);
        return;
    }
    void Delete(int node){//删除 
		split(root,node,x,z); split(x,node-1,x,y);  
        y=merge(ch[y][0],ch[y][1]);  
        root=merge(merge(x,y),z);return;
    }
    int Rank(int node){//查找数的排名 
    	split(root,node-1,x,y);  
        int ans=siz[x]+1;root=merge(x,y);
		return ans;
    }
    int RankX(int x){//查找排名为x的数 
    	return val[kth(root,x)];
	}
    int Front(int node){//前驱 
		split(root,node-1,x,y);  
        int ans=val[kth(x,siz[x])];  
        root=merge(x,y);
		return ans;
    }
    int behind(int node){//后驱 
    	split(root,node,x,y);  
        int ans=val[kth(y,1)];  
        root=merge(x,y); return ans;
	}
	void Res(int l,int r){//区间翻转 
	    int a,b,c,d;
	    split(root,r+1,a,b);
	    split(a,l,c,d);
	    mark[d]^=1;
	    root=merge(merge(c,d),b);
	}
};

//树状数组，long long 
#define N_BIT 
struct BIT{
	ll c[N_BIT];
    int n;
    BIT(int n){        
		memset(c,0,sizeof(c));n=n;
    }
    inline int lowbit(int x){
        return x&(-x);
    }
    inline void modify(int x,ll y){
        for(;x<=n;x+=lowbit(x))
            c[x]+=y;
    }
    inline ll query(int x){
        ll ret=0;
        for(;x;x-=lowbit(x))
            ret+=c[x];
        return ret;
    }
    inline ll query(int l,int r){
        return query(r)-query(l-1);
    }
};

//求同余方程 
template<typename T>
inline void Exgcd(T a,T b,T &x,T &y){
	if(b==0){
		x=1,y=0;return;
	}
	Exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;
}
template<typename T>
T exgcd(T x,T z,T p){
    T t=Gcd(x,p);
    p=-p;
    if(z%t)
        return -1;
    x/=t;z/=t;p/=t;
    T a,b;
    Exgcd(x,p,a,b);
    a=(ll)a*z%p;
    while(a<0)a+=p;
    return a;
}

//最大流Dinic
#define N_Dinic 1000005
struct Dinic{
	private:
	struct edge{
		int to,next,v;
	};
	edge e[N_Dinic<<2];
	int head[N_Dinic<<1];
	int ne,q[N_Dinic<<1];
	int h[N_Dinic<<1],ans,n,S,T;

	inline void ins(int u,int v,int f){
		ne++;e[ne].to=v;
		e[ne].next=head[u];
		e[ne].v=f;head[u]=ne;
	}
	bool bfs(){
		int t=0,w=1;
		memset(h,-1,sizeof(h));
		q[t]=S;h[S]=0;
		while(t<w){
			int now=q[t++];
			for(int i=head[now];i;i=e[i].next){
				int v=e[i].to;
				if(h[v]==-1&&e[i].v){
					h[v]=h[now]+1;
					q[w++]=v;
				}
			}
		}
		if(h[T]!=-1) return 1;
		return 0;
	}
	int dfs(int x,int f){
		if(x==T) return f;
		int w,used=0;
		for(int i=head[x];i;i=e[i].next){
			int v=e[i].to;
			if(h[v]==h[x]+1){
				w=dfs(v,min(f-used,e[i].v));
				e[i].v-=w;e[i^1].v+=w;used+=w;
				if(used==f) return f;
			}
		}
		if(!used) h[x]=-1;
		return used;
	}
	public:
	Dinic(int s,int t){
		ne=1,ans=0;
		S=s;T=t;
	};
	inline void insert(int u,int v,int f){
		ins(u,v,f);ins(v,u,0);
	}
	int dinic(){
		ans=0;
		while(bfs())
			ans+=dfs(S,inf);
		return ans;
	}
};

//最小费用最大流 
#define MCMF 100005
#define MCMF_N 1000005
struct Mcmf{
	struct Edge{
		int to,next,from;
		ll v,c;
	}e[MCMF<<1];
	int ne,head[MCMF_N],from[MCMF_N];
	bool inq[MCMF_N];
	int S,T;
	ll dis[MCMF_N],ans;
	queue<int> q;
	Mcmf(){
		ans=0;ne=1;
	}
	void ins(int u,int v,ll f,int c){
		ne++;e[ne].to=v;e[ne].from=u;
		e[ne].v=f;e[ne].c=c;
		e[ne].next=head[u];head[u]=ne;
	}
	void insert(int u,int v,ll f,int c){
		ins(u,v,f,c);ins(v,u,0,-c);
	}
	bool spfa(){
		memset(dis,0x3f,sizeof(dis));
		dis[S]=0;
		q.push(S);
		while(!q.empty()){
			int now=q.front();q.pop();
			inq[now]=0;
			for(int i=head[now];i;i=e[i].next){
				int v=e[i].to;
				if(e[i].v==0) continue;
				if(dis[v]>dis[now]+e[i].c){
					dis[v]=dis[now]+e[i].c;
					from[v]=i;
					if(!inq[v]){
						q.push(v);
						inq[v]=1;
					}
				}
			}
		}
		if(dis[T]!=inf) return 1;
		return 0;
	}
	void flow(){
		ll mn=inf;
		for(int i=T;i;i=e[from[i]].from){
			mn=min(e[from[i]].v,mn);
		}
		for(int i=T;i;i=e[from[i]].from){
			e[from[i]].v-=mn;
			e[from[i]^1].v+=mn;
			ans+=e[from[i]].c*mn;
		}
	}
	void mcmf(){
		while(spfa())
			flow();
	}
};

//线段树 
#define LIFT ret<<1
#define RIGHT ret<<1|1
#define lson l,mid,ret<<1
#define rson mid+1,r,ret<<1|1
#define SBT_Node_sum 1000005
struct SegmentTree
{
    private:
    int n;
    int sum[SBT_Node_sum];
	int tree[SBT_Node_sum<<2];
    int mark[SBT_Node_sum<<2];
    inline void pushup(int ret){
        tree[ret]=tree[LIFT]+tree[RIGHT];
    }
	inline void build(int ret,int l,int r){
        if(l==r){
            tree[ret]=sum[l];return;
        }
        int mid=(l+r)>>1;
        build(lson);
        build(rson);
        pushup(ret);
	}
	inline void down(int ret,int l,int r){
        int m=(l+r)>>1;
		mark[LIFT]+=mark[ret];
		mark[RIGHT]+=mark[ret];
		tree[LIFT]+=mark[ret]*(m-l+1);
		tree[RIGHT]+=mark[ret]*(r-m);
		mark[ret]=0;
	}
	inline int ask_point(int ret,int l,int r,int sum){
		if(l==r)
			return tree[ret];
		if(mark[ret]) down(ret,l,r);
		int mid=(l+r)>>1;
		if(sum<=mid) return ask_point(lson,sum);
		else return ask_point(rson,sum);
	}
	inline void change_point(int ret,int l,int r,int sum){
		if(l==r){
			tree[ret]+=sum;return;
        }
		int mid=(l+r)>>1;
		if(sum<=mid)change_point(lson,sum);
		else change_point(rson,sum);
		pushup(ret);
	}
	inline int ask_interval(int ret,int l,int r,int L,int R){
		int ans=0;
        if(l>=L&&r<=R)
			return tree[ret];
		if(mark[ret]) down(ret,l,r);
		int mid=(l+r)>>1;
		if(L<=mid)ans+=ask_interval(lson,L,R);
		if(R>mid)ans+=ask_interval(rson,L,R);
        return ans;
	}
	inline void change_interval(int ret,int l,int r,int L,int R,int sum){
		if(l>=L&&r<=R){
			tree[ret]+=(r-l+1)*sum;
			mark[ret]+=sum;return;
		}
		if(mark[ret]) down(ret,l,r);
		int mid=(l+r)>>1;
		if(L<=mid)change_interval(lson,L,R,sum);
		if(R>mid)change_interval(rson,L,R,sum);
		pushup(ret);
	}
    public:
    SegmentTree(int n,int Array[]){
        n=n;
        for(int i=1;i<=n;++i)
            sum[i]=Array[i];
        build(1,1,n);
    }
    void Change_ONE(int pos){
        change_point(1,1,n,pos);
    }
    int Ask_ONE(int pos){
         return ask_point(1,1,n,pos);
    }
    void Change_SB(int L,int R,int sum){
        change_interval(1,1,n,L,R,sum);
    }
    int Ask_SB(int L,int R){
        return ask_interval(1,1,n,L,R);
    }
};


