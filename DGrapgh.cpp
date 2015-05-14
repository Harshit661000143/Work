#include <iostream>
#include <map>
#include <set>
#include <vector>
using namespace std;

class Graph{
 vector<char> *adj;
 set<char> vertices;
 public:
 Graph(){
  adj= new vector<char>;
}
 void addEdge(char v, char e){
  adj[v].push_back(e);
  adj[e].push_back(v);
  vertices.insert(e);
  vertices.insert(v);
}
 
bool isCycleTest(char s, map<char,bool> &visited, char parent){
  if(visited[s]==true)
  return true;
  cout<<s<<"parent"<<parent<<endl;
  visited[s]=true;
  for(vector<char>:: iterator l=adj[s].begin();l!=adj[s].end();l++){
     cout<<"I am "<<s<<" my parent is "<<parent<<"and neighbour is "<<*l<<endl;
     if(parent==*l){
  cout<<s<<" same parent"<<parent<<endl;
      continue;}
     else {
     cout<<s<<" not same parent"<<parent<<"neigh "<<*l<<endl;
    }
    if(isCycleTest(*l,visited,s))
      return true;
  }
     cout<<"After loop I am "<<s<<" my parent is "<<parent<<endl;
  return false;
 }

bool isCycle(){
 int vertex=vertices.size();
 map<char,bool> visited;
 for(set<char>:: iterator start=vertices.begin(); start!=vertices.end();start++)
   visited[*start]=false;
 set<char>:: iterator s=vertices.begin();
 cout<<*s<<endl;
 if(isCycleTest(*s,visited,'\0')){
 cout<<"cycle"<<endl;
   return true;
}
 cout<<"NO cycle"<<endl;
 for(set<char>:: iterator start=vertices.begin(); start!=vertices.end();start++)
   if(!visited[*start])
    return true;
 return false;
}
};

int main(int argc, char* argv[]){
 string input;
 char a,b;
 int count=1;
 int target=atoi(argv[1]);
 Graph g;
 while(getline(cin,input)){
  a=input[0];
  b=input[2];
  g.addEdge(a,b);
 if(count==target)
  break;
 else
  count++;
 }
 if(g.isCycle())
   cout<<"false"<<endl;
 else
   cout<<"true"<<endl;
 return 0;
}
