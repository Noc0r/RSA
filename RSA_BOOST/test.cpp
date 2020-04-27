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
    {
        cout << "Fuck you!" << endl;
    }
    else
        cout << "EEEEEEEEEEEEEEEEEEE boy";
    RSA rsa_test1(1024, &checkPrimeSolovei);
    //RSA rsa_test2(10, &checkPrimeRabin);
    //RSA rsa_test3(10, &checkPrimeSolovei);
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
}