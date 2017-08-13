
#include<algorithm>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#define N 50005
using namespace std;

struct Point{
    double x,y;
};  

Point result[N];
Point tree[N];
int n,top;

double Dis(Point p1,Point p2){
	double x=p1.x-p2.x;
	double y=p1.y-p2.y;
    return sqrt(x*x+y*y);
}

double Multiply(Point p1,Point p2,Point p3){
	double x1=p2.x-p1.x;
	double y1=p3.y-p1.y;
	double y2=p2.y-p1.y;
	double x2=p3.x-p1.x;
    return (x1*y1-y2*x2);
}

int cmp(const void *p1,const void *p2){
    Point *p3,*p4;
    double m;
    p3=(Point*)p1; 
    p4=(Point*)p2; 
    m=Multiply(tree[0],*p3,*p4) ;
    return m<0;
    return m==0&&(Dis(tree[0],*p3)<Dis(tree[0],*p4));
    return 0;
}

void Convex_hull(){
     result[0]=tree[0];
     result[1]=tree[1];
     result[2]=tree[2];
     top=2;
     for(int i=3;i<=n;++i){
         while(Multiply(result[top-1],result[top],tree[i])<=0)top--;
          result[top+1]=tree[i];
          top++;
     }

}

void Special_judgment(){
	scanf("%d",&n);
    for(int i=0;i<n;++i)
        scanf("%lf%lf",&tree[i].x,&tree[i].y);
	if(n>2)return;
	exit(0);
}

void Find_The_start_point(){
	double px,py=-1;
	int pos;
    for(int i=0;i<n;++i){
        if(py==-1||tree[i].y<py){
            px=tree[i].x;
            py=tree[i].y;
            pos=i;
        }
    	else if(tree[i].y==py&&tree[i].x<px){
            px=tree[i].x;
            py=tree[i].y;
            pos=i;
        }
    }
    swap(tree[0],tree[pos]);
	qsort(&tree[1],n-1,sizeof(double)<<1,cmp);
	tree[n]=tree[0];
}

int rotating_calipers(Point *ch,int n)  
{  
    int q=1;
	double ans=0;  
    ch[n]=ch[0];  
    for(int p=0;p<n;p++)  
    {  
        while(Multiply(ch[p+1],ch[q+1],ch[p])>Multiply(ch[p+1],ch[q],ch[p]))  
            q=(q+1)%n;  
        ans=max(ans,max(Dis(ch[p],ch[q]),Dis(ch[p+1],ch[q+1])));              
    }  
    return ans;   
}

double Answer(){
	Special_judgment();
    Find_The_start_point();
	Convex_hull();
	return  rotating_calipers(result,top);
}

int main(){
	return 0;
}