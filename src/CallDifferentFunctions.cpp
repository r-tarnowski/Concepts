#include <iostream>

#include <vector>
#include <list>
#include <map>

using std::cout;
using std::endl;

void printHeader() {
    cout << endl;
    cout << "================================================" << endl;
    cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
    cout << "                  Concepts                      " << endl;
    cout << "           Call Different Functions             " << endl;
    cout << "================================================" << endl;
    cout << endl;
}

template<typename Coll, typename T>
concept SupportsPushBack = requires( Coll c, T v ) {
   c.push_back( v );
};

template<typename Coll>
concept SupportsPushBack_WithOneParameter = requires( Coll c, Coll::value_type val ) {
   c.push_back( val );
};

template<typename Coll>
concept SupportsPushBack_WithDeclval = requires( Coll c ) {
   c.push_back( std::declval<typename Coll::value_type&>() );
};

template<typename Coll>
concept SupportsPushBack_WithDeclvalAndRanges = requires( Coll c ) {
    c.push_back( std::declval<std::ranges::range_value_t<Coll>>() );
};

template<typename Coll, typename T>
requires SupportsPushBack_WithOneParameter<Coll>
void add( Coll & coll, const T & val ) {
    std::cout << "Method add for generic value types that supports push_back called" << std::endl;
    coll.push_back( val );
}

template<typename Coll, typename T>
void add( Coll & coll, const T & val ) {
    std::cout << "Method add for generic value types that DOES NOT support push_back called" << std::endl;
    coll.insert( val );
}

int main(int argc, char *argv[]) {
    printHeader();

    std::vector<int> iVec;
    int intVal = 42;
    std::cout  << "add( iVec, intVal ) -> ";
    add( iVec, intVal );

    std::list<int> iList;
    std::cout  << "add( iList, intVal ) -> ";
    add( iList, intVal );

    std::map<int, int> iMap;
    std::cout  << "add( iMap, (intVal, intVal ) -> ";
    add( iMap, std::make_pair( 1, 2 ) );

    return 0;
}
