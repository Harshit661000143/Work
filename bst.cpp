#include "global.h"

struct node{
 int data;
 node *left;
 node *right;
 node *parent;
};

node* createNode(int data){
  node *Node= new node;
  Node->data = data;
  Node->left = NULL;
  Node->right = NULL;
  Node->parent = NULL;
  return Node;
}

node* push(int data, node* root){
  node *Node = createNode(data);
  if(root==NULL)
    return createNode(data);
  if(root->data > data){
    root->left = push(data, root->left); 
    root->left->parent = root;
  }
  else{
    root->right = push(data, root->right); 
    root->right->parent = root;
  }
  return root;
}

void printTree(node *root){
  if(root==NULL)
    return;
  cout<<root->data<<"====>"; 
  printTree(root->left);
  printTree(root->right);
}

node* nextNode(int data, node *root){
  if(root == NULL)
    return 0;
  if(root->data==data){
   cout<<"Printing from calle \n"<<root->data<<"\n";
   return root;
  }
     
  if(root->data > data)
   return nextNode(data, root->left);
  else
    return nextNode(data, root->right);
}

node *nextLargest(int data, node* root){
  node* temp= nextNode(data,root);
  if(temp==NULL){
    cout<<"Invalid input\n";
    return NULL;
  }
  node *ans = temp->right;
  if(ans){
    while(ans->left!=NULL){
        ans=ans->left;
    }
    return ans;
  }
  node *par = temp->parent;
  while(par!=NULL){
   if(temp == par->left)
     return par;
   temp= par;
   par= par->parent;
  }
 }
  




int main(){
  node *root=NULL;
  root = push(10,root); 
  root = push(20,root); 
  root = push(5,root); 
  root = push(25,root); 
  printTree(root);
  node* temp= nextLargest(5,root);
  cout<<"\n"<<temp->data<<"\n";
}
 
  

  
