// A very bad example of std::initializer_list usage in cpp
#include <iostream>

using namespace std;

class A{
    int &rInt;
    const int cInt;
    public:
    //below syntax would stop the compiler from creating a default Ctor
    A() = delete;
    //below default Ctor wont even compile
    //A(){ cout << __PRETTY_FUNCTION__ << endl; }

    A(int rInt, int cInt):rInt(rInt), cInt(cInt){
        cout << __PRETTY_FUNCTION__ << endl;
    }

    void print(){
        cout << "Ref Int: " << rInt << endl;
        cout << "Const Int: " << cInt << endl;
    }
};

class B:public A{
    public:
    //initialization of the base class in the initialization list is mandatory as Base class does not 
    //have a default Ctor
    B():A(0,0)
    {
        cout << __PRETTY_FUNCTION__ << endl;
    }
};

int main(){
    A a1(3, 5);
    a1.print();
    B b1;
    b1.print();
    return 0;
}