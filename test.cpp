#include <iostream>
#include "BigInteger/BigInteger.cpp"
#include "RSA_cs/rsa.h"
#include "Primes/genPrimes.h"

using namespace std;

int main()
{
    BigInteger a(22, 10);
    BigInteger b(3, 10);
    srand(time(NULL));
    cout << (a.mul(b, 3)) << endl;
    cout << (b.sub(a, 5)) << endl;
    cout << (a.div(b, 10)) << endl;
    eucl_res res = extendEucl(a, b);
    cout << res.d << " " << res.x << " " << res.y << endl;
    BigInteger r = genPrime(100, &checkPrimeSolovei);
    BigInteger test_pow = modPow(b, a, BigInteger(5, 10));
    BigInteger test_powM = modPowMontg(b, a, BigInteger(5, 10));
    BigInteger test_mod = BigInteger(-115, 10) % BigInteger(288, 10);
    cout << test_pow << endl;
    cout << test_powM << endl;
    cout << test_mod << endl;
    r.convert(10);
    cout << r << endl;
    RSA rsa_test1(150, &checkPrimeRabin);
    //RSA rsa_test2(10, &checkPrimeRabin);
    //RSA rsa_test3(10, &checkPrimeSolovei);
    BigInteger a_1 = rsa_test1.encrypt(a);
    BigInteger a_2 = rsa_test1.decrypt(a_1);
    if (a == a_2)
        cout << "Cool" << endl;
    else
    {
        cout << "Error" << endl;
        cout << rsa_test1.getParams().N << endl;
        cout << rsa_test1.getParams().d << endl;
        cout << rsa_test1.getParams().e << endl;
    }
}