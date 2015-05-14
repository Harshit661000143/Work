#include "global.h"

void reverse(string* s){

string *t=s;
for(int i=0,j=s->size()-1;i<j;i++,j--){
cout<<"i=\t"<<i<<"\tj=\t"<<j<<endl;
string temp;
temp=s[i];
cout<<temp<<endl;
s[i]=s[j];
s[j]=temp;
}
#if 0
while(*s!=NULL){

cout<<*s;
s++;

}
#endif
}

int main(){
string s= "fuck";
int *ptr= new int[10];


reverse(&s);
cout<<"Reversed  "<<s;
 return 0;
}

