#include <iostream>
class Node{
  int data;
  Node* left;
  Node* right;
  Node* parent;
public:
  Node(){
    data=-1;
    left=NULL;
    right= NULL;
    parent= NULL;
  };
  ~Node();
  void setData(int d){
    data=d;
  };
  int getData(){
    return data;
  };
  Node* getParent(){
    return parent;
  };
  Node* getLeft(){
    return left;
  };
  Node* getRight(){
    return right;
  };
  void setParent(Node* par){
    parent= par;
  };
  void setLeft(Node* par){
    left = par ;
  };
  void setRight(Node* par){
     right= par;
  };
};
class Tree{
  Node* root;

  public:
  Tree(){root=NULL;};
  ~Tree();
  Node* Root(){
    return root;
  };
  void addNode(int key);
    Node* findNode(int key, Node* parent);
    void walk(Node* node);
    void deleteNode(int key);
    Node* min(Node* node);
    Node* max(Node* node);
    Node* successor(int key, Node* parent);
    Node* predecessor(int key, Node* parent);
private:
    void addNode(int key, Node* leaf);
    void freeNode(Node* leaf);
};
void Tree:: addNode(int key){
  if(root==NULL){
    Node* temp= new Node();
    temp->setData(key);
    root= temp;
    return;
  }
  else{
      addNode(key,root);
  }  
}
void Tree:: addNode(int key, Node* root){
  if(root->getData()>key){
    if(root->getRight()!=NULL){
      addNode(key,root->getRight());
    }
    else{
      Node* temp= new Node();
      temp->setData(key);
      root->setRight(temp);
    }
  }
  else{
    if(root->getLeft()!=NULL){
      addNode(key,root->getLeft());
    }
    else{
      Node* temp;
      temp->setData(key);
      root->setLeft(temp);
    }
  }
}
int main(){
  Tree *tr= new Tree();
  tr->addNode(10);
  tr->addNode(20);
  tr->addNode(15);
  tr->addNode(12);
}

