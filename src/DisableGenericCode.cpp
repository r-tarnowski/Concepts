#include <iostream>

#include <vector>

using std::cout;
using std::endl;

void printHeader() {
    cout << endl;
    cout << "================================================" << endl;
    cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
    cout << "                  Concepts                      " << endl;
    cout << "            Disable Generic Code                " << endl;
    cout << "================================================" << endl;
    cout << endl;
}

template<typename Coll, typename T>
void add( Coll & coll, const T & val ) {
    std::cout << "Method add for generic value types called" << std::endl;
    coll.push_back( val );
}

template<typename Coll, typename T>
requires std::floating_point<T>
void add( Coll & coll, const T & val ) {
    std::cout << "Method add for generic floating point types called" << std::endl;
    coll.push_back( val );
}

template<typename Coll >
void add( Coll & coll, double val ) {
    std::cout << "Method add for double value type called" << std::endl;
    coll.push_back( val );
}



int main(int argc, char *argv[]) {
    printHeader();

    std::vector<int> iVec;
    add( iVec, 42 );

    std::vector<double> dVec;
    add( dVec, 0.7 );

    float floatVal = 0.7;
    add( dVec, floatVal );

    return 0;
}