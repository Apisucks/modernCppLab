#include <iostream>
#include <memory>

using namespace std;

class A{
    public:
        virtual void print(){ cout << __PRETTY_FUNCTION__ << endl;}
};

class B: public A {
    public:
        void print(){
            cout << __PRETTY_FUNCTION__ << endl;
        }
};

class C: public A {
    
};

int main(){

    A *ab = new B();

    B *b = dynamic_cast<B*>(ab);
    if (b){
        cout << "Casting B -> B successful" << endl;
    }

    // Below cast would not succeed as the class heirarchy is different 
    A *ac = new C();
    B *bc = dynamic_cast<B*>(ac);
    if (bc){
        cout << "Casting C -> B successful" << endl;
    }
    return 0;
}