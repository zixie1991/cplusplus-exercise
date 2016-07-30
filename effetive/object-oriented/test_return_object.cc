#include <iostream>

using namespace std;

class Cat {
  public:
    Cat() {
      cout << "Cat()" << endl; 
    }

    Cat(const Cat& cat) {
      cout << "Cat copy" << endl;
    }

    ~Cat() {
      cout << "~Cat()" << endl;
    }
};


Cat GetCatObject() {
  return Cat();
}

int main() {
  const Cat& cat = GetCatObject();
  Cat cat2 = GetCatObject();
  return 0;
}
