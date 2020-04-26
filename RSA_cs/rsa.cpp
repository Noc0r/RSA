#pragma once
#include "rsa.h"
#include "../Primes/genPrimes.h"

RSA::RSA(int l, bool (*pvmt_func)(int, BigInteger, int))
{
    int q_size = l / 2;
    int p_size = l / 2 + l % 2;
    params.e = 65537;
    do
    {
        p = genPrime(p_size, pvmt_func);
        q = genPrime(q_size, pvmt_func);
    } while (extendEucl(p - 1, params.e).d != 1 || extendEucl(q - 1, params.e).d != 1);
    params.N = p * q;
    eucl_res inv = extendEucl(p, q);
    p_inv = inv.x;
    q_inv = inv.y;
    BigInteger phi = (p - 1) * (q - 1);
    params.d = extendEucl(params.e, phi).x;
}

BigInteger RSA::encrypt(BigInteger x)
{
    return modPow(x, params.e, params.N);
}

BigInteger RSA::decrypt(BigInteger y)
{
    BigInteger x1 = modPow(y, params.d % (p - 1), p);
    BigInteger x2 = modPow(y, params.d % (q - 1), q);
    return (q_inv * q * x1 + p_inv * p * x2) % params.N;
}