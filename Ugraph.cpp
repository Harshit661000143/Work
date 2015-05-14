#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;
class Graph{
  set<char> vertices;
  vector<char> *adj;
  public:
  Graph(){
adj = new vector<char>;
 }
 void addEdge(char v, char e){
 adj[v].push_back(e);
 adj[e].push_back(v);
 incoming.insert(e);
 if(incoming.find(v)==incoming.end())
   outgoing.insert(v);
 if(outgoing.find(e)!=outgoing.end())
   outgoing.erase(e);
}
 int outgoingedges(){
  return outgoing.size();
 }
 int incomingedges(){
  return incoming.size();
 }
 bool isCyclicUtil(char root,map<char,bool> &visited){
   if(visited[root])
  return true;
  visited[root]=true;
   vector<char>::iterator vert;
   for(vert = adj[root].begin(); vert != adj[root].end(); ++vert)
       if (isCyclicUtil(*vert, visited))
          return true;
       
   return false;
 }
 
 bool isCyclic(){
  map<char,bool> visited;
  int vertex= incomingedges()+ outgoingedges();
 for(std::set<char>::iterator it=outgoing.begin(); it!=outgoing.end(); ++it)
   visited[*it]=false;
 for(std::set<char>::iterator it=incoming.begin(); it!=incoming.end(); ++it)
   visited[*it]=false;
 set<char>::iterator root=outgoing.begin();
 if(outgoing.empty())
  return true;
 cout<<"ROOT=:"<<*root<<endl;
 if(isCyclicUtil(*root,visited))
   return true;
 else
   return false;

}


 
void printData(){
  int i=0;
 for(std::set<char>::iterator it=outgoing.begin(); it!=outgoing.end(); ++it){
    std::cout << *it << std::endl;
    cout<<"OUT"<<"\n";
}
cout<<"Completed out\n";
 for(std::set<char>::iterator it=incoming.begin(); it!=incoming.end(); ++it){
    std::cout << *it << std::endl;
    cout<<"IN"<<"\n";
}
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
 if(g.outgoingedges()>1){
  cout<<"false"<<"\n";
 return 0;
}
 if(g.isCyclic())
   cout<<"false"<<endl;
 else
   cout<<"true"<<endl;
 return 0;
}
     


