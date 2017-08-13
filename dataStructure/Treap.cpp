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
