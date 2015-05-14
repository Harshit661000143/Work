#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <list>
using namespace std;
//template <class T>
class Graph{
 public:
	set<char> vertex;
	vector<char> *adj;
	list<char> queue;
	Graph(){
		adj= new vector<char>;
	}
	void addEdge(char v, char e);
	void bfs(char v, map<char, bool> &visited);
        

};
//template <class T>
	void Graph:: addEdge( char v, char e){
		adj[v].push_back(e);
		adj[e].push_back(v);
		vertex.insert(v);
		vertex.insert(e);
	}
//template <class T>
	void Graph:: bfs(char v, map<char, bool> &visited){
		if(vertex.find(v)!=vertex.end()){

			visited[v]=true;
			cout<<v<<"\n";
			for(std::vector<char>::iterator ver=adj[v].begin();ver!=adj[v].end();ver++){
				if(!visited[*ver])
					queue.push_back(*ver);
			}
			while(!queue.empty()){
				char next=queue.front();
				queue.pop_front();
				bfs(next,visited);
			}

		}
        }

//template <class T>
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
map<char, bool> visited;
for(std::set<char>::iterator s=g.vertex.begin();s!=g.vertex.end();s++)
  visited[*s]=false;
 g.bfs(a, visited);
 //  cout<<"false"<<endl;
// else
 //  cout<<"true"<<endl;
 return 0;
}

                

