#include <iostream>
#include "BigInteger.cpp"

using namespace std;

int main()
{
    BigInteger a(1000);
    BigInteger b("3451238294728329382803");
    cout << (a.mul(b));
}