#include <iostream>
#include <tr1/functional> 

struct B
{
  std::tr1::function <void ()> _callback;

  void reg_callback(std::tr1::function <void ()> callback)
  {
    _callback = callback;
  }

  void unreg_callback()
  {
    _callback = NULL;
  }

  void process() {
    // simply calls callback
    if (_callback)
      _callback();
  }
};

struct A 
{ 
  B * _b;

  A(B * b) :
    _b(b)
  {
    std::tr1::function<void()> callback;
    callback = std::tr1::bind(&A::callback, this);
    b->reg_callback(callback);
  }

  ~A()
  {
    _b->unreg_callback();
  }

  void callback() {
    std::cout << "A::callback called\n";
  }

  void process() {
    _b->process();
  }
}; 

int main() 
{ 
  B * b = new B();
  A * a = new A(b); 

  // the following is example where object b calls 
  // back into a method
  // in object a
  a->process();

  // now delete object a, and verify the callback 
  // in B does not crash or still get called
  delete a;

  // now b should not execute the callback
  b->process();
} 


