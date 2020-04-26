#pragma once
#include "../BigInteger/BigInteger.h"

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
    RSA(int l, bool (*pvmt_func)(int, BigInteger, int));
    rsa_params getParams() const;
    BigInteger encrypt(BigInteger x);
    BigInteger decrypt(BigInteger y);
};