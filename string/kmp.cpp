#define Maxn 1000000
#define Maxm 1000
struct KMP{
    int pre[Maxn];
    int len1,len2;
    int p;

    KMP()
    {
        for(int i=0;i<Maxn;i++)
            pre[i]=0;
    }

    inline void preprocess(char*pattern)
    {
        len2=strlen(pattern),p=-1;
        pre[0]=-1;
        for(int i=1;i<len2;i++)
        {
            while(p!=-1&&pattern[p+1]!=pattern[i])
                p=pre[p];
            p+=(pattern[p+1]==pattern[i]);
            pre[i]=p;
        }
    }

    inline void kmp(char*original,char*pattern)
    {
        len1=strlen(original);
        p=-1;
        for(int i=0;i<len1;i++)
        {
            while(p!=-1&&original[i]!=pattern[p+1])
                p=pre[p];
            p+=(pattern[p+1]==original[i]);
            if(p+1==len2)
                printf("%d\n",i-len2+2),p=pre[p];
        }
        for(int i=0;i<len2;i++)
            printf("%d ",pre[i]+1);
    }
};