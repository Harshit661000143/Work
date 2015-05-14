// trie implemention  in c
//#include<stdio.h>
//#include<stdlib.h>
#include<iostream>

#include<string.h>
using namespace std;
struct node {
	int data;
	struct node *Children[26];
};
struct node *getNode()
{
	int i;
	struct node *Node=(struct node*)malloc(sizeof(struct node));
	Node->data=(-1);
	for(i=0;i<26;i++)
	{
		Node->Children[i]=NULL;
	}
	return Node;
}
void add_Word(char keys[],struct node **Root)
{
	struct node *Trie=(*Root);
	int length=strlen(keys);
	int level=0;
	for(level=0;level<length;level++)
	{         
		int Index=(int)keys[level]-(int)'a';
//                cout<<"Index = "<<Index<<"keys[level] = "<<keys[level]<<endl;
		if((Trie->Children[Index])==NULL)
		{
			Trie->Children[Index]=getNode();
		}
		Trie=Trie->Children[Index];
	}
        cout<<"level = "<<level<<endl;   
	Trie->data=level;
}
void Search_Word(char *keys,struct node *Root)
{
	int flag=1,i;
	struct node* current=Root;
	for(i=0;i<strlen(keys);i++)
	{
		int Index=(int)keys[i]-(int)'a';
		if(current->Children[Index]!=NULL)
		{
			current=current->Children[Index];
                cout<<" Search Index = "<<Index<<" keys[i] = "<<keys[i]<<endl;
		}
		else
		{
			break;
		}
	}
        cout<<"current->data = "<<current->data<<endl;
	if(keys[i]=='\0' && current->data!=-1)
	{
	printf("%s is PRESENT \n",keys);
	}
	else
	{
		printf("%s is NOT PRESENT  \n",keys);
	}
}

int main()
{
	struct node *Root=getNode();
	int i;
	char keys[100][8] = {"the", "a", "there", "answera", "any", "by", "bye", "their"};
	for(i=0;i<8;i++)
	{
        printf("%s is key  \n",keys[i]);
		add_Word(keys[i],&Root);
	}
	
	Search_Word("th",Root);
	Search_Word("the",Root);
}








