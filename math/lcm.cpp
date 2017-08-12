inline int GCD(int a,int b)
{
    return !b?a:GCD(b,a%b);
}
inline int lcm(int a,int b)
{
    return a*b/GCD(a,b);
}