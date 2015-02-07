#define DEBUG 0

#define MATRIX 2
#define MATRIXROW 3
#define MATRIXCOLUMN 3

#include "global.h"

struct node{
  node *right;
  node *left;
  node *up;
  node *down;
  int x;
  int y;
 };
struct coodinates{
int x;
int y;
coodinates(int a, int b)
 {
   x=a;
   y=b;
 }
};

struct cost{
int g;
int h;
};




int createIndex(int x,int y)
{
  return x*(MATRIX+1)+y;
}
void createTree(node *root);
void bfs(int index);
void createChild(int x, int y, node **root, int index);
int mat [MATRIX + 1][MATRIX + 1]= {
{ 1,0,0 },
{ 1,1,1 },
{ 0,1,1 }
};
struct comparefn{
  bool operator()( const coodinates& lhs, const coodinates& rhs) const
  {
    if((lhs.x<rhs.x) && (lhs.y<rhs.y))
     return true;
    else
     return false;
  }
};
map<int,bool> traversed;
list<int> *adj;
//cost *fcost;
int main()
{
 node *root= new node;
 int x=2,y=2;
 root->x=x;
 root->y=y;
 adj= new list<int>[(x+1)*(y+1)];
 createTree(root);
// cout <<"DATA"<<root->left->y<<"\n";
 int index=createIndex(x,y);
 bfs(index);
 
}
void bfs(int index)
{
 bool *visited= new bool[(MATRIXROW)*(MATRIXCOLUMN)];
 loop(x,MATRIXROW*MATRIXCOLUMN,1)
  visited[x]=false;
 list<int> queue;
  queue.push_back(index);
  list<int>:: iterator i;
  while(!queue.empty())
   {
     index=queue.front();
     visited[index]=true;
     cout<<index<<"\t";
     queue.pop_front();
     for(i=adj[index].begin();i!=adj[index].end();++i)
       {
         if(!visited[*i])
          {
            queue.push_back(*i);
            visited[*i]=true;
          }
       }
   }
}
 
  



void createTree(node *root)
{
 
 if(root==NULL)
  return;
  int x= root->x;
  int y= root->y;
  int index= createIndex(x,y);
  cout<<"checking map for x=" <<x<<"\t and y="<<y<<"\n";
  if(traversed[index]){
   return;}
   traversed[index]=true;
  
 cout <<"Creating child for x\t"<<root->x<<"\t"<<root->y<<"\n";
#if 1
 createChild(x,y-1,&root->left,index);
 createChild(x,y+1,&root->right,index);
 createChild(x+1,y,&root->down, index);
 createChild(x-1,y,&root->up, index);
#endif
// cout <<"DATA"<<root->left->y<<"\n";
// cout <<"DATA"<<root->left->x<<"\n";
// cout<<"BEGIN MAKING TREE\n"; 
 createTree(root->left);
 createTree(root->right);
 createTree(root->up);
 createTree(root->down);
#if 0
 createTree(root->right,root->right->x,root->right->y);
 createTree(root->up,root->up->x,root->up->y);
 createTree(root->down,root->down->x,root->down->y);
#endif 
// cout<<"END MAKING TREE\n"; 
}
#if 0
 cout <<"DATA"<<root->left->y<<"\n";
 cout <<"DATA"<<root->left->x<<"\n";
 cout <<"DATA"<<root->up->y<<"\n";
 cout <<"DATA"<<root->up->x<<"\n";
#endif
void createChild(int x, int y, node **child, int index)
{ 
// cout<<"INSIDE\n";
 if(x<=MATRIX && y<=MATRIX && x>=0 && y>=0 && mat[x][y])
  {
    node *newNode= new node;
    newNode->x=x;
    newNode->y=y;
    *child=newNode;
    adj[index].push_back(createIndex(x,y));
  
     
#if DEBUG
 if(*child!=NULL)
 cout <<"DATA fun"<<(*child)->x<<"\n";
#endif

  }
  else
  {
   *child=NULL;
  }
// cout<<"END\n";
}

  
  
 

  
