#pragma once
#include "../Primes/genPrimes.h"

struct rsa_params
{
    cpp_int e;
    cpp_int N;
    cpp_int d;
};

class RSA
{
    rsa_params params;
    cpp_int p;
    cpp_int q;
    cpp_int p_inv;
    cpp_int q_inv;

public:
    RSA(int l, bool (*pvmt_func)(int, cpp_int const &, int));
    rsa_params getParams() const;
    cpp_int encrypt(cpp_int x);
    cpp_int decrypt(cpp_int y);
};

RSA::RSA(int l, bool (*pvmt_func)(int, cpp_int const &, int))
{
    int q_size = l / 2;
    int p_size = l / 2 + l % 2;
    params.e = 65537;
    do
    {
        p = genPrime(p_size, pvmt_func);
        q = genPrime(q_size, pvmt_func);
    } while (p == q || extendEucl(p - 1, params.e).d != 1 || extendEucl(q - 1, params.e).d != 1);
    params.N = p * q;
    eucl_res inv = extendEucl(p, q);
    p_inv = (inv.x + q) % q;
    q_inv = (inv.y + p) % p;
    cpp_int phi = (p - 1) * (q - 1);
    params.d = (extendEucl(params.e, phi).x + phi) % phi;
}

rsa_params RSA::getParams() const
{
    return params;
}

cpp_int RSA::encrypt(cpp_int x)
{
    return modPow(x, params.e, params.N);
}

cpp_int RSA::decrypt(cpp_int y)
{
    cpp_int x1 = modPow(y, params.d % (p - 1), p);
    cpp_int x2 = modPow(y, params.d % (q - 1), q);
    return (q_inv * q * x1 + p_inv * p * x2) % params.N;
}