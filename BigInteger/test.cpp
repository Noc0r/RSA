#include <iostream>
#include "BigInteger.cpp"

using namespace std;

int main()
{
    BigInteger a(1002);
    BigInteger b("345123");
    cout << (a.mul(b));
}