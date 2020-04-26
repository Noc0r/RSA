#include <iostream>
#include "BigInteger.cpp"

using namespace std;

int main()
{
    BigInteger a(24,10);
    BigInteger b(3,10);
    cout << (a.mul(b,3)) << endl;
    cout << (b.sub(a,5)) << endl;
    cout << (a.div(b,10)) << endl;
}