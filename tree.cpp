#include <iostream>
using namespace std;

template <class T>
class Node{
 
  T data;
  Node* left;
  Node* right;

  public:
   Node(T newData){
     data = newData;
     left = NULL;
     right = NULL;
   }
   ~Node(){
     cout<<"Exiting\n";
   }
   void print();
   Node* addNode(T newdata, Node<T> *root);
};
template <class T>
void Node<T>:: print(){
  cout<<"Data\n";
  cout<<data;
  if(left!=NULL)
    cout<<left->data;
  if(right!=NULL)
    cout<<right->data;
  if(left!=NULL&& right!=NULL){
  left->print();
  right->print();
}
} 
template <class T>
Node<T>* Node<T>:: addNode(T newdata, Node<T> *root){
  if(root==NULL){
    Node<T> *temp=new Node<T>(newdata);
    return temp;
  }
  if( root->data < newdata)
    root->right= addNode(newdata, root->right);
  else  
    root->left= addNode(newdata, root->left);
  return root;
}
int main(){
  Node<int> *root=new Node<int>(10);
  root= root->addNode(20,root);
  root= root->addNode(15,root);
  root= root->addNode(11,root);
  root= root->addNode(12,root);
  root->print();
} 
