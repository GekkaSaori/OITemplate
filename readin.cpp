inline int readin()
{
    int ret=0;char ch=getchar();
    while(ch<'0'||ch>'9')getchar();
    while(ch>='0'&&ch<='9'){ret=ret*10+ch-'0';ch=getchar();}
    return ret;
}