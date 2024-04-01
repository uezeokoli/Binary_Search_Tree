//-----------------------------------------------------------------------------
// Ugonna Ezeokoli
// uezeokoli
// 2024 Winter CSE101 PA7
// DictionaryTest.cpp
// A test client for the Dictionary ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"
#include<cassert>

using namespace std;

void TestFunctions(){
    Dictionary D, C;

    cout<<endl;
    cout<<"Access functions --------------------------------------------------------"<<endl;
    cout<<endl;

    //test size()
    assert(D.size() == 0);
    D.setValue("first",1);
    D.setValue("second", 2);
    assert(D.size() == 2);
    D.clear();
    cout << "size() works!\n";

    //test contains()
    assert(!D.contains("first"));
    D.setValue("first",1);
    assert(D.contains("first"));
    D.clear();
    cout << "contains() works!\n";

    //test getValue()
    D.setValue("first",1);
    assert(D.getValue("first") == 1);
    D.clear();
    cout << "getValue() works!\n";

    //test hasCurrent()
    D.setValue("first",1);
    D.setValue("second", 2);
    assert(!D.hasCurrent());
    D.begin();
    assert(D.hasCurrent());
    D.clear();
    cout << "hasCurrent() works!\n";

    //test currentKey() 
    D.setValue("first",1);
    D.setValue("second", 2);
    D.begin();
    assert(D.currentKey() == "first");
    D.clear();
    cout << "currentKey() works!\n";

    //test currentVal()
    D.setValue("first",1);
    D.setValue("second", 2);
    D.begin();
    assert(D.currentVal() == 1);
    D.clear();
    cout << "currentVal() works!\n";

    cout<<endl;
    cout<<"Manipulation procedures -------------------------------------------------"<<endl;
    cout<<endl;

    //test clear()
    assert(D.size() == 0);
    D.setValue("first",1);
    D.setValue("second", 2);
    assert(D.size() == 2);
    D.clear();
    assert(D.size() == 0);
    cout << "clear() works!\n";

    //test setValue()
    assert(D.size() == 0);
    D.setValue("first",1);
    D.setValue("second", 2);
    assert(D.size() == 2);
    D.clear();
    cout << "setValue() works!\n";

    //test remove()
    assert(D.size() == 0);
    D.setValue("first",1);
    D.setValue("second", 2);
    assert(D.size() == 2);
    D.remove("second");
    assert(D.size() == 1);
    D.clear();
    cout << "remove() works!\n";

    //test begin()
    D.setValue("first",1);
    D.setValue("second", 2);
    D.begin();
    assert(D.currentKey() == "first");
    assert(D.currentVal() == 1);
    D.clear();
    cout << "begin() works!\n";

    //test end()
    D.setValue("first",1);
    D.setValue("second", 2);
    D.end();
    assert(D.currentKey() == "second");
    assert(D.currentVal() == 2);
    D.clear();
    cout << "end() works!\n";

    //test next()
    D.setValue("first",1);
    D.setValue("second", 2);
    D.begin();
    D.next();
    assert(D.currentKey() == "second");
    assert(D.currentVal() == 2);
    D.clear();
    cout << "next() works!\n";
    
    //test prev()
    D.setValue("first",1);
    D.setValue("second", 2);
    D.end();
    D.prev();
    assert(D.currentKey() == "first");
    assert(D.currentVal() == 1);
    D.clear();
    cout << "prev() works!\n";

    cout<<endl;
    cout<<"Overloaded Operators ----------------------------------------------------"<<endl;
    cout<<endl;

    //test operator==()
    D.setValue("first",1);
    D.setValue("second", 2);

    C.setValue("second", 2);
    C.setValue("first",1);
    assert(C == D);
    C.clear();
    D.clear();
    cout << "operator==() works!\n";

    //test operator=()
    D.setValue("first",1);
    D.setValue("second", 2);
    C = D;
    assert(C == D);
    D.clear();
    C.clear();
    cout << "operator=() works!\n";
}

int main(int argc, char* argv[]){

    TestFunctions();

    cout<<endl;
    cout << "All Functions are working!\n";
}
