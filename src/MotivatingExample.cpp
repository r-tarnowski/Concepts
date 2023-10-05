#include <iostream>
#include <memory>



using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
   cout << "                  Concepts                      " << endl;
   cout << "             Motivating Example                 " << endl;
   cout << "================================================" << endl;
   cout << endl;
}

template< typename T >
concept IsRawPointer = std::is_pointer_v<T>;

template< typename T >
concept IsPointer = requires ( T p ) {
                       *p;                                // operator * has to be valid
                       p == nullptr;                      // can compare with nullptr
                       { p < p } -> std::same_as< bool >; // yields bool
                    };

template< typename T >
requires ( ! IsPointer<T> )
T maxVal( T a, T b ) {
   std::cout << "Calling maxVal for NON pointers -> " << std::endl;
   return b < a ? a : b;
}

template< typename T >
requires IsPointer<T>
//Note the trick with auto return value
auto maxVal( T a, T b ) {
   std::cout << "Calling maxVal for pointers -> " << std::endl;
   return maxVal( * a, * b );
}

template < typename A, typename B >
auto minVal( A a, B b ) {
   std::cout << "Calling minVal for NON pointers -> " << std::endl;
   return b < a ? b : a;
}

template <IsPointer T>
auto minVal( T a, T b ) {
   std::cout << "Calling minVal for pointers of the same type -> " << std::endl;
   return minVal( *a, *b );
}

auto minVal( IsPointer auto a, IsPointer auto b )
requires std::totally_ordered_with< decltype( *a ), decltype( *b ) > {
   std::cout << "Calling minVal for pointers of different types -> " << std::endl;
   return minVal( *a, *b );
}

int main(int argc, char *argv[]) {
   printHeader();

   int x = 100;
   int y = 102;
   double z = 101.1;

   int * pX = & x;
   int * pY = & y;
   double * pZ = & z;

   std::shared_ptr<double> sharedPtrZ = std::make_shared<double>( z );
   std::shared_ptr<int> sharedPtrY = std::make_shared<int>( y );


   std::cout << "Max value of " << x << " and " << y << " : "
             << maxVal( x, y ) << std::endl;
   std::cout << "Max value pointed by " << & x << " and " << & y << " : "
             << maxVal( & x, & y ) << std::endl;
   std::cout << "Max value double pointed by " << & pX << " and " << & pY << " : "
             << maxVal( & pX, & pY ) << std::endl;

   std::cout << std::endl;
   std::cout << "Min value of " << x << " and " << y << " : "
             << minVal( x, y ) << std::endl;
   std::cout << "Min value pointed by " << pX << " and " << pY << " : "
             << minVal( pX, pY ) << std::endl;
   std::cout << "Min value pointed by " << pY << " and " << pZ << " : "
             << minVal( pY, pZ ) << std::endl;

   std::cout << std::endl;
   std::cout << "Min value pointed by " << sharedPtrZ << " and " << sharedPtrY << " : "
             << minVal( sharedPtrZ, sharedPtrY ) << std::endl;


   return 0;
}
