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
