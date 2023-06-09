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
void add( Coll & coll, const double & val ) {
    std::cout << "Method add for reference to const double called" << std::endl;
    coll.push_back( val );
}

/*
template<typename Coll >
void add( Coll & coll, double val ) {
    std::cout << "Method add for double value type called" << std::endl;
    coll.push_back( val );
}
*/

int main(int argc, char *argv[]) {
    printHeader();

    std::vector<int> iVec;
    int intVal = 42;
    std::cout  << "add( iVec, intVal ) -> ";
    add( iVec, intVal );

    std::vector<double> dVec;
    double doubleVal = 0.7;
    std::cout  << "add( dVec, doubleVal ) -> ";
    add( dVec, doubleVal );

    float floatVal = 0.7;
    std::cout  << "add( dVec, floatVal ) -> ";
    add( dVec, floatVal );


    std::vector<std::vector<int>> vecOfIntVec;
    std::vector< int > intVec = { 1, 2, 3, 4, 5};
    std::cout  << "add( vecOfIntVec, intVec ) -> ";
    add( vecOfIntVec, intVec );

    std::vector<std::vector<float>> vecOfFloatVec;
    std::vector< float > floatVec = { 1.0, 2.0, 3.0 };
    std::cout  << "add( vecOfFloatVec, floatVec ) -> ";
    add( vecOfFloatVec, floatVec );

    std::cout  << "add( iVec, 1.9 ) -> ";
    add( iVec, 1.9 );
    std::cout  << "add( dVec, 1.9 ) -> ";
    add( dVec, 1.9 );

    return 0;
}