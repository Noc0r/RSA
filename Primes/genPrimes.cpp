#include "genPrimes.h"
#include <ctime>

BigInteger genRand(BigInteger start, int l)
{
    BigInteger random(start);
    for (int i = 1; i < l; i++)
        if (rand() % 2)
            random += start << i;
}

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger))
{
    const int d = 5;
    BigInteger one(1, 2);
    BigInteger l_rand = one << l - 1;
    bool end = false;
    while (end)
    {
        end = true;
        BigInteger n = l_rand + genRand(one, l - 1);
        for (int i = 0; i < d; i++)
        {
            if (!pvmt_func(l, n))
            {
                end = false;
                break;
            }
        }
    }
}

bool checkPrimeFerma(int l, BigInteger n)
{
    BigInteger one(1, 2);
    BigInteger a = genRand(one, l);
    eucl_res res = extendEucl(a, n);
    if (res.d != one)
        return false;
    return (modPow(a, n - one, n) == one);
}

bool checkPrimeRabin(int l, BigInteger n)
{
    BigInteger one(1, 2);
    BigInteger a = genRand(one, l);
    eucl_res res = extendEucl(a, n);
    if (res.d != one)
        return false;
    int s;
    BigInteger r = n - one;
    while (!r.getVector()[0])
    {
        r = r >> 1;
        s++;
    }
    BigInteger v = modPow(a, r, n);
    if (v == one)
        return true;
    for (int i = 0; i < s; i++)
    {
        if (v == -one)
            return true;
        v = (v * v) % n;
    }
    return false;
}

bool checkPrimeSolovei(int l, BigInteger n)
{
}