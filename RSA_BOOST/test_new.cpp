#include <iostream>
#include "RSA_cs/rsa.h"
#include "Primes/genPrimes.h"

using namespace std;

int main()
{
    cpp_int a = 1000;
    srand(time(NULL));
    cpp_int a_p = modPow(a, 200000, 10000);
    cpp_int a_p1 = modPowMontg(a, 200000, 10000);
    if (a_p != a_p1)
        cout << "Wrong modPowMontg" << endl;
    RSA rsa_test1(1536, &checkPrimeFerma);
    RSA rsa_test2(1536, &checkPrimeRabin);
    RSA rsa_test3(1536, &checkPrimeSolovei);
    cpp_int a_1 = rsa_test1.encrypt(a);
    cpp_int a_2 = rsa_test1.decrypt(a_1);
    if (a == a_2)
        cout << "Cool" << endl;
    else
    {
        cout << "Error" << endl;
        cout << rsa_test1.getParams().N << endl;
        cout << rsa_test1.getParams().d << endl;
        cout << rsa_test1.getParams().e << endl;
    }
    a_1 = rsa_test2.encrypt(a);
    a_2 = rsa_test2.decrypt(a_1);
    if (a == a_2)
        cout << "Cool" << endl;
    else
    {
        cout << "Error" << endl;
        cout << rsa_test2.getParams().N << endl;
        cout << rsa_test2.getParams().d << endl;
        cout << rsa_test2.getParams().e << endl;
    }
    rsa_test3.encrypt(a);
    rsa_test3.decrypt(a_1);
    if (a == a_2)
        cout << "Cool" << endl;
    else
    {
        cout << "Error" << endl;
        cout << rsa_test3.getParams().N << endl;
        cout << rsa_test3.getParams().d << endl;
        cout << rsa_test3.getParams().e << endl;
    }
    cout << "END" << endl;
}
