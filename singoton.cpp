#include <iostream>

class Singleton {
 public:
  static Singleton* get_instance() {
    if (instance == nullptr) {
      //instance = new Singleton();
    }
    return instance;
  }
 private:
//  Singleton() {}
  static Singleton *instance;// = nullptr;
};

Singleton* Singleton::instance = nullptr;

int main() {
  //int *t = Singleton<int>::getInstance();
  //Singleton *t = Singleton::getInstance();
  Singleton::get_instance();
  return 0;
}

