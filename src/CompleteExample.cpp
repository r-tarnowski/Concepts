#include <iostream>



using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
   cout << "                  Concepts                      " << endl;
   cout << "              Complete Example                  " << endl;
   cout << "================================================" << endl;
   cout << endl;
}


template< typename T >
concept IsPointer = requires ( T p ) {
   *p;                                // operator * has to be valid
   p == nullptr;                      // can compare with nullptr
   { p < p } -> std::convertible_to< bool >; // yields bool
};

// maxValue() for plain values
auto maxVal( auto a, auto b ) {
   std::cout << "Calling maxVal for plain values -> " << std::endl;
   return b < a ? a : b;
}

auto maxVal( IsPointer auto a, IsPointer auto b )
requires std::totally_ordered_with< decltype( *a ), decltype( *b ) > {
   std::cout << "Calling maxVal for pointers of different types -> " << std::endl;
   return maxVal( *a, *b ); //return the maximum value of where the pointers refer to
}


int main(int argc, char *argv[]) {
   printHeader();

   int x = 42;
   int y = 77;
   std::cout << "Max value of " << x << " and " << y << " : "
             << maxVal( x, y ) << std::endl;           // maximum value of ints
   std::cout << "Max value pointed by " << & x << " and " << & y << " : "
             << maxVal( & x, & y ) << std::endl;      // maximum value of where the pointers point to

   int * pX = & x;
   int * pY = & y;
   std::cout << "Max value double pointed by " << & pX << " and " << & pY << " : "
             << maxVal( & pX, & pY ) << std::endl;   // maximum value of pointer to pointer

   double d = 49.9;
   std::cout << "Max value pointed by " << pX << " and " << & d << " : "
             << maxVal( pX, & d ) << std::endl;      // maximum value of int and double

   return 0;
}
