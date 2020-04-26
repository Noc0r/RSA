#include <iostream>
#include "BigInteger.cpp"

using namespace std;

int main()
{
    BigInteger a(4,10);
    BigInteger b(3,10);
    /*b.convert(2);
    cout << b ;*/
    cout << (a.mul(b,3)) << endl;
    cout << (b.sub(a,10)) << endl;
}