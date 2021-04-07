//g++ lValu.cpp -o ./exes/lValu -O0 -g -fno-elide-constructors
//above command to compile the code
#include <iostream>

using namespace std;

class A{
    public:
    A() {
        cout << "default" << endl;
    }

    A(const A& a){
        cout << "Copy" <<endl;
    }

    A(A&& a ){
        cout << "Move" <<endl;
    }

    A & operator = (const A& a){
        cout << "Assgn" <<endl;
        return * this;
    }

    void print(){
        cout << "print" << endl;
    }
};

//When the below fn will be called to copy construct an object
//it will result in 2 calls to copy constructor
//first call to create a temporary from the object as it is returned by value (just after the return statement)
//second call will be to copy create the object
//Incase we have move Ctor implemented, we'll see 2 calls to move Ctor instead of copy Ctor.
A obj(){
    A a;
    return a;
}

//When the below fn is called to copy construct an object
//it will only result in one call to copy Ctor as we are returning a reference 
//hence there is no need to create a temporary object.
A& obj1(){
    A a;
    return a;
}

void example_1(){
    // two calls to the copy Ctor, or move Ctor (if it's implemented)
    A a1 = obj();
}

void example_2(){
    // will result in one call to copy Ctor, will only call copy Ctor even if move Ctor is implemented
    A a2 = obj1();

    // will result in one call to move Ctor
    A a3 = std::move(obj1());
}

int main(){
    example_1();
    example_2();
    return 0;

}