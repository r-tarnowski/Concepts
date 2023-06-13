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
    cout << "            The Example as a Whole              " << endl;
    cout << "================================================" << endl;
    cout << endl;
}

//concept for container with push_back():
template<typename Coll>
concept SupportsPushBack = requires( Coll coll, Coll::value_type val ) {
    coll.push_back( val );
};

//concept to disable narrowing conversions:
template<typename From, typename To>
concept ConvertsWithoutNarrowing =
   std::convertible_to<From, To> &&
   requires ( From && x ) {
       { std::type_identity_t<To[]>{std::forward<From>(x)} }
          ->std::same_as<To[1]>;
   };

//add() for single value
template<typename Coll, typename T>
requires ConvertsWithoutNarrowing< T, typename Coll::value_type>
void add ( Coll & coll, const T & val ) {
    std::cout << "add() for single value, ";
    if constexpr ( SupportsPushBack<Coll> ) {
        std::cout << "for collection that supports push_back() called"
                  << std::endl;
        coll.push_back( val );
    }
    else {
        std::cout << "for collection that DOES NOT support push_back() called"
                  << std::endl;
        coll.insert( val );
    }
}

// add for multiple value
template<typename Coll, std::ranges::input_range T>
requires ConvertsWithoutNarrowing< std::ranges::range_value_t<T>, typename Coll::value_type >
void add( Coll & coll, const T & val ) {
     std::cout << "add() for multiple value, ";
    if constexpr ( SupportsPushBack<Coll> ) {
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

int main(int argc, char *argv[]) {
    printHeader();

    std::vector< int > iVec;
    std::cout << "add( iVec, 42 ) -> ";
    add( iVec, 42 );

    std::set< int > iSet;
    std::cout << "add( iSet, 42 ) -> ";
    add( iSet, 42 );

    short int s = 42;
    std::cout << "add( iVec, s ) -> ";
    add( iVec, s );

    long long l2 = 42;
    //add( iVec, l2 ); //ERROR: ConvertsWithoutNarrowing constraints not satisfied
    //add( iVec, 7.7 ); //ERROR: ConvertsWithoutNarrowing constraints not satisfied

    std::vector<double> dVec;
    std::cout << "add( dVec, 0.7 ) -> ";
    add( dVec, 0.7 );
    std::cout << "add( dVec, 0.7f ) -> ";
    add( dVec, 0.7f );
    //add( dVec, 7 ); //ERROR: ConvertsWithoutNarrowing constraints not satisfied

    //insert collections
    std::cout << "add( iVec, iSet ) -> ";
    add( iVec, iSet );
    std::cout << "add( iSet, iVec ) -> ";
    add( iSet, iVec );

    //can even insert a raw array:
    int vals[] = { 0, 8, 18 };
    std::cout << "add( iVec, vals ) -> ";
    add( iVec, vals );
    //add( dVec, vals ); //ERROR: ConvertsWithoutNarrowing constraints not satisfied

    //my own tests start here
    std::vector< std::vector<int> > vecOfIntVec = { { 1, 5 }, { 1, 2 }, { 1, 2, 3 } };
    std::cout  << "add( vecOfIntVec, iVec ) -> ";
    add( vecOfIntVec, iVec ); //NO ERROR and I don't know why ;-) !!!

    std::vector< std::vector<int> > vecOfIntVec2 = { { 1 }, { 1, 2 }, { 1, 2, 3 } };
    std::cout  << "add( vecOfIntVec, vecOfIntVec2 ) -> ";
    add( vecOfIntVec, vecOfIntVec2 );

    std::map<int, int> iMap;
    std::cout  << "add( iMap, std::make_pair( 1, 2 ) ) -> ";
    add( iMap, std::make_pair( 1, 2 ) );

    std::map<int, int> iMap2 = { std::make_pair( 4, 5) };
    std::cout  << "add( iMap, iMap2 ) -> ";
    add( iMap, iMap2 );

    std::list<int> iList;
    int intVal = 44;
    std::cout  << "add( iList, intVal ) -> ";
    add( iList, intVal );

    std::list<int> iList2 = { 1, 2, 3 };
    std::cout  << "add( iList, iList2 ) -> ";
    add( iList, iList2 );

    return 0;
}

