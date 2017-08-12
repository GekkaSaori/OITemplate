inline int FastPower(int Tp,int Up,int mod)
{
    int r=1,base=Tp;
    while(b)
    {
        if(b&1)
            r*=base;
        base*=base;
        b>>1;
    }
    return r;
}