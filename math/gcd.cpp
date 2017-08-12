inline int GCD(int a,int b)
{
    return !b?a:GCD(b,a%b);
}