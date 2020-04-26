#pragma once
#include "../BigInteger/BigInteger.h"
#include <ctime>
#include <cmath>

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger const &, int));
bool checkPrimeFerma(int l, BigInteger const &n, int d);
bool checkPrimeRabin(int l, BigInteger const &n, int d);
bool checkPrimeSolovei(int l, BigInteger const &n, int d);

BigInteger genRand(BigInteger const &start, int l)
{
    BigInteger random(start);
    for (int i = 1; i < l; i++)
        if (rand() % 2)
            random += start << i;
    random.convert(10);
    return random;
}

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger const &, int))
{
    const int d = 1;
    BigInteger one(1, 2);
    BigInteger l_rand = one << l - 1;
    l_rand.convert(10);
    BigInteger n = l_rand + genRand(one, l - 1);
    while (!pvmt_func(l, n, d))
    {
        n = l_rand + genRand(one, l - 1);
    }
    return n;
}

bool checkPrimeFerma(int len, BigInteger const &n, int dim)
{
    BigInteger one(1, 2);
    for (int i = 0; i < dim; i++)
    {
        BigInteger a = genRand(one, len);
        eucl_res res = extendEucl(a, n);
        if (res.d != one || modPow(a, n - one, n) != one)
            return false;
    }
    return true;
}

bool checkPrimeRabin(int len, BigInteger const &n, int dim)
{
    BigInteger one(1, 2);
    for (int i = 0; i < dim; i++)
    {
        BigInteger a = genRand(one, len);
        eucl_res res = extendEucl(a, n);
        int s = 0;
        BigInteger r = n - 1;
        if (res.d != 1)
            return false;
        while (!(r.getVector()[0] & 1))
        {
            r = r >> 1;
            s++;
        }
        BigInteger v = modPow(a, r, n);
        if (v == 1)
            continue;
        bool isCorrect = false;
        for (int i = 0; i < s; i++)
        {
            if (v == -1)
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

bool checkPrimeSolovei(int len, BigInteger const &n, int dim)
{
    BigInteger one(1, 2);
    for (int i = 0; i < dim; i++)
    {
        BigInteger a = genRand(one, len);
        eucl_res res = extendEucl(a, n);
        if (res.d != 1 || modPow(a, (n - 1) / 2, n) != lejandr(a, n))
            return false;
    }
    return true;
}