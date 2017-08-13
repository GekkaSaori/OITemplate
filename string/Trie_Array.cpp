struct Trie{
	int ch[maxnode][Alphabet];
	int sz;
	inline void Insert(char* str){
		int u=0;
		int len=strlen(str);
		for(int i=0;i<len;++i){
			if(str[i]=='\0')break;
			int c=str[i]-'a';
			if(!ch[u][c])ch[u][c]=++sz;
			u=ch[u][c];
		}
		return ;
	}
	inline bool query(char* str){
		int u=0;
		int len=strlen(str);
		for(int i=0;i<len;++i){
			int c=str[i]-'a';
			if(!ch[u][c])return 0;
			u=ch[u][c];
		}
		return true;
	}
};
