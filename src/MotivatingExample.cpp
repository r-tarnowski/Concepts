#include <iostream>



using std::cout;
using std::endl;

void printHeader() {
   cout << endl;
   cout << "================================================" << endl;
   cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
   cout << "                  Concepts                      "<< endl;
   cout << "================================================" << endl;
   cout << endl;
}

template< typename T >
concept IsPointer = std::is_pointer_v<T>;

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

int main(int argc, char *argv[]) {
   printHeader();

   int x = 100;
   int y = 102;

   int * pX = & x;
   int * pY = & y;

   std::cout << "Max value of " << x << " and " << y << " : "
             << maxVal( x, y ) << std::endl;
   std::cout << "Max value pointed by " << & x << " and " << & y << " : "
             << maxVal( & x, & y ) << std::endl;
   std::cout << "Max value double pointed by " << & pX << " and " << & pY << " : "
             << maxVal( & pX, & pY ) << std::endl;

   return 0;
}
