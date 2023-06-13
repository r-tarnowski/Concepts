#include <iostream>

#include <vector>
#include <set>
#include <ranges>
#include <map>
#include <list>

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
void add( Coll & coll, const T & val ) {
    std::cout << "add() for single value, ";
    if constexpr (SupportsPushBack_WithOneParameter<Coll>) {
        std::cout << "for collection that supports push_back() called"
                  << std::endl;
        coll.push_back( val );
    } else {
        std::cout << "for collection that DOES NOT support push_back() called"
                  << std::endl;
        coll.insert( val );
    }
}


// Doesn't work vector of vectors. TO DO: check why.
template<typename Coll, std::ranges::input_range T>
requires SupportsPushBack_WithOneParameter<Coll>
void add( Coll & coll, const T & val ) {
    std::cout << "add() for multiple value that supports push_back called" << std::endl;
    coll.insert( coll.end(), std::ranges::begin( val ), std::ranges::end( val ) );
}

template<typename Coll, std::ranges::input_range T>
void add( Coll & coll, const T & val ) {
    std::cout << "add() for for multiple value that DOSE NOT support push_back called" << std::endl;
    coll.insert( val.begin(), val.end() );
}


/*
// add for multiple value
template<typename Coll, std::ranges::input_range T>
void add( Coll & coll, const T & val ) {
    std::cout << "add() for multiple value, ";
    if constexpr ( SupportsPushBack_WithOneParameter<Coll> ) {
        std::cout << "for collection that supports push_back() called"
                  << std::endl;
        coll.insert( coll.end(),
                     std::ranges::begin( val ), std::ranges::end( val ) );
    }
    else {
        std::cout << "for collection that DOES NOT support push_back() called"
                  << std::endl;
        coll.insert( std::ranges::begin( val ), std::ranges::end( val ) );
    }
}
*/

int main(int argc, char *argv[]) {
    printHeader();

    std::vector<int> iVec;
    int intVal = 42;
    std::cout  << "add( iVec, intVal ) -> ";
    add( iVec, intVal );

    std::list<int> iList;
    std::cout  << "add( iList, intVal ) -> ";
    add( iList, intVal );

    std::list<int> iList2 = { 1, 2, 3 };
    std::cout  << "add( iList, iList2 ) -> ";
    add( iList, iList2 );

    std::map<int, int> iMap;
    std::cout  << "add( iMap, std::make_pair( 1, 2 ) ) -> ";
    add( iMap, std::make_pair( 1, 2 ) );

    std::map<int, int> iMap2 = { std::make_pair( 4, 5) };
    std::cout  << "add( iMap, iMap2 ) -> ";
    add( iMap, iMap2 );

    std::set< int > iSet;
    std::cout << "add( iSet, 42 ) -> ";
    add( iSet, 42 );

    std::cout << "add( iVec, iSet ) -> ";
    add( iVec, iSet );
    std::cout << "add( iSet, iVec ) -> ";
    add( iSet, iVec );


    std::vector< std::vector<int> > vecOfIntVec = { { 1, 5 }, { 1, 2 }, { 1, 2, 3 } };
    //std::cout  << "add( vecOfIntVec, iVec ) -> ";
    add( vecOfIntVec, iVec ); //ERROR but I don't know why :-(

    std::vector< std::vector<int> > vecOfIntVec2 = { { 1 }, { 1, 2 }, { 1, 2, 3 } };
    std::cout  << "add( vecOfIntVec, vecOfIntVec2 ) -> ";
    add( vecOfIntVec, vecOfIntVec2 );



    return 0;
}
