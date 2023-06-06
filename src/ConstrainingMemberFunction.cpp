#include <ConstrainingMemberFunction.h>

#include <vector>

using std::cout;
using std::endl;

void printHeader() {
    cout << endl;
    cout << "================================================" << endl;
    cout << "  C++20 The Complete Guide by Nicolai Josuttis  " << endl;
    cout << "                  Concepts                      " << endl;
    cout << "          Constraining Member Function          " << endl;
    cout << "================================================" << endl;
    cout << endl;
}


int main(int argc, char *argv[]) {
    printHeader();

    ValOrColl val = 42;
    val.print();

    ValOrColl coll = std::vector<int> { 1, 2, 3, 4 };
    coll.print();

    return 0;
}