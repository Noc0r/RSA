#include <iostream>
#include "BigInteger/BigInteger.cpp"
#include "RSA_cs/rsa.h"
#include "Primes/genPrimes.h"

using namespace std;

int main()
{
    BigInteger a(22, 10);
    BigInteger b(3, 10);
    cout << (a.mul(b, 3)) << endl;
    cout << (b.sub(a, 5)) << endl;
    cout << (a.div(b, 10)) << endl;
    eucl_res res = extendEucl(a, b);
    cout << res.d << " " << res.x << " " << res.y << endl;
    RSA rsa_test1(5, &checkPrimeFerma);
    RSA rsa_test2(5, &checkPrimeRabin);
    RSA rsa_test3(5, &checkPrimeSolovei);
    BigInteger a_1 = rsa_test1.encrypt(a);
    BigInteger a_2 = rsa_test1.decrypt(a_1);
    if (a == a_2)
        cout << "Cool" << endl;
    else
    {
        cout << "Error" << endl;
    }
}