#include <iostream>

using namespace std;

class Singleton
{
public:
	static Singleton *getInstance(int);
        int getCount();
        int count;
	Singleton(int i) {count=i;
          getInstance(count);}
	static Singleton *instance;
};

Singleton* Singleton::instance = 0;
Singleton* Singleton::getInstance(int i) {
		if(!instance) {
			instance = new Singleton(i);
			cout << "getInstance(): First instance\n";
			return instance;
		}
		else {
			cout << "getInstance(): previous instance\n";
			return instance;
		}
}
int Singleton::getCount(){
return count;
}

int main()
{
	Singleton* s1 = new Singleton(5);
	Singleton* s2 = new Singleton(5);


	return 0;
}
