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
