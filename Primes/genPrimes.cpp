#pragma once
#include "genPrimes.h"
#include <ctime>

BigInteger genRand(BigInteger start, int l)
{
    BigInteger random(start);
    for (int i = 1; i < l; i++)
        if (rand() % 2)
            random += start << i;
}

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger, int))
{
    const int d = 5;
    BigInteger one(1, 2);
    BigInteger l_rand = one << l - 1;
    BigInteger n = l_rand + genRand(one, l - 1);
    while (pvmt_func(l, n, d))
    {
        n = l_rand + genRand(one, l - 1);
    }
}

bool checkPrimeFerma(int l, BigInteger n, int d)
{
    BigInteger one(1, 2);
    for (int i = 0; i < d; i++)
    {
        BigInteger a = genRand(one, l);
        eucl_res res = extendEucl(a, n);
        if (res.d != one || modPow(a, n - one, n) != one)
            return false;
    }
    return true;
}

bool checkPrimeRabin(int l, BigInteger n, int d)
{
    BigInteger one(1, 2);
    for (int i = 0; i < d; i++)
    {
        BigInteger a = genRand(one, l);
        eucl_res res = extendEucl(a, n);
        int s = 0;
        BigInteger r = n - one;
        if (res.d != one)
            return false;
        while (!r.getVector()[0])
        {
            r = r >> 1;
            s++;
        }
        BigInteger v = modPow(a, r, n);
        if (v == one)
            continue;

        bool isCorrect = false;
        for (int i = 0; i < s; i++)
        {
            if (v == -one)
            {
                isCorrect = true;
                break;
            }
            v = (v * v) % n;
        }
        if (!isCorrect)
            return false;
    }
    return true;
}

bool checkPrimeSolovei(int l, BigInteger n, int d)
{
    BigInteger one(1, 2);
    for (int i = 0; i < d; i++)
    {
        BigInteger a = genRand(one, l);
        eucl_res res = extendEucl(a, n);
        if (res.d != one || modPow(a, (n - one) / 2, n) != lejandr(a, n))
            return false;
    }
    return true;
}