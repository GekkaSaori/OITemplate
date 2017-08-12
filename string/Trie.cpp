#include<algorithm>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
using namespace std;

struct Node{
	Node* Alphabet[26];
	int count;bool isword;
}root;

struct Trie{
	Node* Create_node(){
		Node* node=(Node*)malloc(sizeof(root));
		node->count=false;
		node->isword=false;
		memset(node->Alphabet,NULL,sizeof(node->Alphabet));
		return node;
	}
	void Insert_word(char* str){
		Node* node=&root;
		char* word=str;
		int id;
		while(*word){
			id=*word-'a';
			if(node->Alphabet[id]==NULL)
				node->Alphabet[id]=Create_node();
			node=node->Alphabet[id];
			++word;
			node->count+=1;
		}
		node->isword=true;
	}
	int Query_word(char* str){
		Node* node=&root;
		char* word=str;
		int id;
		while(*word){
			id=*word-'a';
			if(node->Alphabet[id]==NULL)
				return false;
			node=node->Alphabet[id];
			++word;
		}
		return node->isword;
	}
}trie;

int main(){
	char* str="iloveyouforever";
	char* s="iloveyou";
	trie.Insert_word(str);
	cout<<trie.Query_word(s);
	return 0;
}
