#include "BigInteger/BigInteger.h"

BigInteger genPrime(int l, bool (*pvmt_func)(int, BigInteger, int));
bool checkPrimeFerma(int l, BigInteger n, int d);
bool checkPrimeRabin(int l, BigInteger n, int d);
bool checkPrimeSolovei(int l, BigInteger n, int d);