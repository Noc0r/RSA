#pragma once
#include "../BigInteger/BigInteger.h"
#include "../Primes/genPrimes.h"

struct rsa_params
{
    BigInteger e;
    BigInteger N;
    BigInteger d;
};

class RSA
{
    rsa_params params;
    BigInteger p;
    BigInteger q;
    BigInteger p_inv;
    BigInteger q_inv;

public:
    RSA(int l, bool (*pvmt_func)(int, BigInteger const &, int));
    rsa_params getParams() const;
    BigInteger encrypt(BigInteger x);
    BigInteger decrypt(BigInteger y);
};

RSA::RSA(int l, bool (*pvmt_func)(int, BigInteger const &, int))
{
    int q_size = l / 2;
    int p_size = l / 2 + l % 2;
    params.e = BigInteger(65537, 10);
    do
    {
        p = genPrime(p_size, pvmt_func);
        q = genPrime(q_size, pvmt_func);
    } while (p == q || extendEucl(p - 1, params.e).d != 1 || extendEucl(q - 1, params.e).d != 1);
    params.N = p * q;
    eucl_res inv = extendEucl(p, q);
    p_inv = (inv.x + q) % q;
    q_inv = (inv.y + p) % p;
    BigInteger phi = (p - 1) * (q - 1);
    params.d = (extendEucl(params.e, phi).x + phi) % phi;
}

rsa_params RSA::getParams() const
{
    return params;
}

BigInteger RSA::encrypt(BigInteger x)
{
    BigInteger cpy(x);
    cpy.convert(10);
    return modPow(cpy, params.e, params.N);
}

BigInteger RSA::decrypt(BigInteger y)
{
    BigInteger cpy(y);
    cpy.convert(10);
    BigInteger x1 = modPow(cpy, params.d % (p - 1), p);
    BigInteger x2 = modPow(cpy, params.d % (q - 1), q);
    return (q_inv * q * x1 + p_inv * p * x2) % params.N;
}