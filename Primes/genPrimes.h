#pragma once
#include "../BigInteger/BigInteger.h"

extern BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger, int));
extern bool checkPrimeFerma(int l, BigInteger n, int d);
extern bool checkPrimeRabin(int l, BigInteger n, int d);
extern bool checkPrimeSolovei(int l, BigInteger n, int d);