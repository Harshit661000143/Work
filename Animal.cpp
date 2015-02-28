#include "global.h"
class Animal
{
 int height;
 double speed;
 double weight;
 string sound;
 
 public:
 string name;
  void setName(string n){ name = n;}
virtual   void setName()=0;
 string getName(){ return name;}
 void setheight(int h){ height = h;}
 void setSound(string s){ sound = s;}
 void setSpeed(double sp){ speed = sp;}
 int getheight( ){ return height;}
 string getSound(){ return sound;}
 double getSpeed(){ return speed;}
 void setWeight(int newWeight){
	        if (newWeight > 0){
	            weight = newWeight;
	        } else {
	            cout<<("Weight must be bigger than 0")<<"\n";
	        }
	    }
double getWeight(){ return weight; }
};
class Dog :public Animal{

   
 public:
   void digHole(){
      cout<<("Dug a hole")<<"\n";
  }
  void setName(){ name = "MAD";}
  
  void changeVar(int randNum){
      randNum = 12;
      cout<<"randNum in method value: "<<randNum<<"\n";
  }
  /* This private method can only be accessed through using other

   * methods in the class */
  private: void bePrivate(){
      cout<<"In a private method"<<"\n";
  }
public:
   void accessPrivate(){
      bePrivate();
  }
  // The constructor initializes all objects
   Dog(){
      setSound("Bark");
  }
};
class Cat :public Animal{
  // The constructor initializes all objects
public:  
 Cat(){
      // Executes the parents constructor
      // Every class has a constructor whether you make it or not
      //super();
      // Sets bark for all Dog objects by default
      setSound("Meow");
  }
  // If you want to make sure a method isn't overridden mark it as Final
   void attack(){
      // Do stuff that can never change
  }
  void setName(){ name = "MAD";}
  // A field marked with final can't be changed
//  static  double FAVNUMBER = 3.14;
  // A class labeled as final can't be extended

   

};




void changeObjectName(Animal &dog)
 {
   dog.setName("Interview");
 }
 int  main(){
  Animal *dog = new Dog;
  Animal *kitty = new Cat;
  dog->setName("Grover");
  cout<<dog->getName()<<"\n";
  cout<<dog->getSound()<<"\n";
  kitty->setName("kitty");
  kitty->setName();
  cout<<kitty->getName()<<"\n";
  cout<<kitty->getSound()<<"\n";
  ((Dog *)dog)->digHole();
  dog->setWeight(-1);
  int randNum = 10;
  ((Dog *) dog)->changeVar(randNum);
  cout<<"After method "<<randNum<<"\n";
 // return 0;
  changeObjectName(*dog);
  cout<<dog->getName()<<"\n";
 }
