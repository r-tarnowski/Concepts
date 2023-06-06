
#ifndef CONSTRAINING_MEMBER_FUNCTION_H
#define CONSTRAINING_MEMBER_FUNCTION_H

#include <iostream>
#include <ranges>

template<typename T>
class ValOrColl {
    T value;
public:
    ValOrColl( const T & val )
       : value { val } {
    }

    ValOrColl( T && val )
       : value { std::move( val ) } {
    }

    void print() const {
        std::cout << "ValOrColl::print() method WITHOUT constraint is called:" << std::endl;
        std::cout << value << std::endl;
    }

    void print() const requires std::ranges::range<T> {
        std::cout << "ValOrColl::print() method WITH constraint is called:" << std::endl;
        for ( auto const & elem : value ) {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

};


#endif
