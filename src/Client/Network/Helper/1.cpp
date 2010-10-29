#include <iostream>

using namespace std;

class A {
  public:
    int i;
};

class B {
  public:
    A * get();
};

A * B::get() {
  A a;
//  a.i = 10;

  return &a;
}

int main() {

  B b;
  A * a = b.get();

  cout << a -> i << endl;

  return 0;
}
