#pragma once
#include "../BigInteger/BigInteger.h"
#include <ctime>
#include <cmath>

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger const &, int));
bool checkPrimeFerma(int l, BigInteger const &n, int d);
bool checkPrimeRabin(int l, BigInteger const &n, int d);
bool checkPrimeSolovei(int l, BigInteger const &n, int d);

BigInteger genRand(int l)
{
    string str = "1";
    for (int i = 1; i < l - 1; i++)
        if (rand() % 2)
            str += "1";
        else
            str += "0";
    str += "1";
    BigInteger random(str, 2);
    random.convert(10);
    return random;
}

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger const &, int))
{
    const int d = 100;
    int i = 0;
    BigInteger n = genRand(l);
    while (!pvmt_func(l, n, d))
    {
        cout << i++ << ": " << n << endl;
        n = genRand(l);
    }
    return n;
}

bool checkPrimeFerma(int len, BigInteger const &n, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        BigInteger a = genRand(len - 1);
        eucl_res res = extendEucl(a, n);
        if (res.d != 1 || modPow(a, n - 1, n) != 1)
            return false;
    }
    return true;
}

bool checkPrimeRabin(int len, BigInteger const &n, int dim)
{
    int s = 0;
    BigInteger r = n - 1;
    while (!(r.getVector()[0] & 1))
    {
        r /= 2;
        s++;
    }
    for (int i = 0; i < dim; i++)
    {
        BigInteger a = genRand(len - 1);
        eucl_res res = extendEucl(a, n);
        if (res.d != 1)
            return false;
        BigInteger v = modPow(a, r, n);
        if (v == 1)
            continue;
        bool isCorrect = false;
        for (int i = 0; i < s; i++)
        {
            if (v == -1 || v == n - 1)
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
    for (int i = 0; i < dim; i++)
    {
        BigInteger a = genRand(len - 1);
        eucl_res res = extendEucl(a, n);
        BigInteger b = (modPow(a, (n - 1) / 2, n) - lejandr(a, n));
        if (res.d != 1 || (b != 0 && b != n))
        {
            return false;
        }
    }
    return true;
}