inline void exgcd(int a,int b,int &x,int &y)
{
	if(b==0)
	{
		x=1,y=0;return;
	}
	exgcd(b,a%b,x,y);
	int t=x;x=y;y=t-a/b*y;
}