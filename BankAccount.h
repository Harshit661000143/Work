#include "global.h"

class BankAccount{
  int __balance;
  public:
  int Deposit(int amount){
   __balance+=amount;
   return 1;
  }
  int Withdraw(int amount){
   __balance-=amount;
   return 1;
  }
};
  
