#include <string.h>
#include <iostream>                 
using namespace::std;
#include <list>
list<int> *adj; 

/*

void findCommonFriends(string P){

for(list<string>::iterator fr=adj[p].begin();fr!=adj[p].end();fr++){
 for(list<string>::iterator fr_2=adj[fr].begin();fr_2!=adj[fr].end();fr_2++){
       if(*fr_2!=*fr)
          cout<<*fr_2;
  }
}
*/

void addFriends(int p, string* listofFriends,int count){
  for(int i=0;i<count;i++){
    adj[p].push_back(listofFriends[i]);
  }
}


int main(){

 string* listF= new string[10];
for(int i=0;i<10;i++){
  listF[i]='A';
} 

for(int i=0;i<10;i++){
  cout<<listF[i];
}
addFriends(1,listF,10);
//list<char> fri;
//fri.push_back('A');
}


