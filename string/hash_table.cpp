#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<vector>
#include<ctime>
#define tab 31
#define Mod 1000003
#define mod 8446744073709550603ll
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

vector<ull>Bit;
int bit=30;

void init(){
	ull ans=1;
	Bit.push_back(1);
	for(int i=1;i<=30;++i){
		ans*=tab;
		Bit.push_back(ans);
	}
}

void Exended(int l,int r){
	ull ans=Bit[Bit.size()-1];
	for(int i=l;i<=r;++i){
		ans*=tab;
		Bit.push_back(ans);
	}
	bit=r;
}

struct hash_list{
	private:
	int sz;
	vector<ll>List;
	vector<int>LIST[Mod+5];
	ull Hash(string str){
		ull hash=0;
		int len=str.size();
		if(len>bit)Exended(bit+1,len+3);
		for(int i=len-1;i>-1;--i){
			hash+=(str[i]-'0'+1)*Bit[len-i];
		}
		return hash%mod;
	}
	public:
	hash_list(){
		sz=-1;
		List.clear();
		for(int i=0;i<=Mod;++i)
			LIST[i].clear();
	}
	int add_list(string str){
		if(Query(str))return -1;
		ull hash=Hash(str);
		int Summary=hash%Mod;
		List.push_back(hash);sz++;
		LIST[Summary].push_back(sz);
		return 1;
	}
	bool Query(string str){
		ll hash=Hash(str);
		int Sum=hash%Mod;
		for(int i=0;i<LIST[Sum].size();++i)
			if(List[LIST[Sum][i]]==hash)
				return true;
		return false;
	}
	int SIZE(){
		return sz+1;
	}
}hash_table;

int main(){
	int T;
	cin>>T;
	init();
	for(int i=1;i<=T;++i){
		int j;string str;
		cin>>j>>str;
		if(j==1)cout<<hash_table.add_list(str)<<endl;
		else cout<<hash_table.Query(str)<<endl;
	}
	cout<<hash_table.SIZE();
	return 0;
}
