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
    BigInteger r = genPrime(5, &checkPrimeSolovei);
    BigInteger test_pow = modPow(b, b, BigInteger(5, 10));
    BigInteger test_mod = BigInteger(-115, 10) % BigInteger(288, 10);
    BigInteger test_div = BigInteger("38921371267364392018391872389129391274678123981293812548789128856712839821831283012974801280982108312956128983127127586173938210938213012976192389012784681829730127874912831471824981284907918293802138129830912830812038019247801274097124912847120974907120470182740812093809218309812093821097480127340971209382117264751746197981283091287371247816564812485718497581749651479218398213812831283818123128458216378612763851412683612", 10) / BigInteger("3892137126736382193012093890128381028309812038124781741827284671267939218381239812470814812907312839127468785628390281938218380128381207478749809812038291083082193821098312749874082183147681231284582137281963712674567125512645671253652153761523651273612", 10);
    cout << test_div << endl;
    cout << test_pow << endl;
    cout << test_mod << endl;
    r.convert(10);
    cout << r << endl;
    RSA rsa_test1(100, &checkPrimeFerma);
    //RSA rsa_test2(10, &checkPrimeRabin);
    //RSA rsa_test3(10, &checkPrimeSolovei);
    BigInteger a_1 = rsa_test1.encrypt(a);
    BigInteger a_2 = rsa_test1.decrypt(a_1);
    if (a == a_2)
        cout << "Cool" << endl;
    else
    {
        cout << "Error" << endl;
    }
}