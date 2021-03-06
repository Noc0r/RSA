#pragma once
#include <vector>
#include <string>

using namespace std;

class BigInteger
{
private:
    bool signum;
    vector<long long> nums;
    int arifm_system_base;
    int compare(BigInteger const &val) const;
    void createVector(long long i);
    void createFromString(string str);
    int nextNumber(int final);
    BigInteger mulToArifmSystem(unsigned int k) const;
    BigInteger divToArifmSystem(unsigned int k) const;

public:
    BigInteger(int i, int arifm_sys);
    BigInteger(long long i, int arifm_sys);
    BigInteger();
    BigInteger(string s, int arifm_sys);
    BigInteger(BigInteger const &b);
    BigInteger(vector<long long> b, int arifm_sys);
    int getASB() const;
    bool getSignum() const;
    vector<long long> getVector() const;
    void setSigned(bool sign);
    void resize(int size);
    void trim();
    void convert(int arifmBase);
    bool isZero();
    BigInteger sum(BigInteger const &value, int arifmSys) const;
    BigInteger mul(BigInteger const &value, int arifmSys) const;
    BigInteger sub(BigInteger const &value, int arifmSys) const;
    BigInteger div(BigInteger const &value, int arifmSys) const;
    BigInteger mod(BigInteger const &value, int arifmSys) const;
    pair<BigInteger, BigInteger> divMod(BigInteger const &val, int arifm_sys) const;
    BigInteger mulToChar(int c) const;
    BigInteger divToChar(int c) const;
    BigInteger operator-() const;
    BigInteger operator+(BigInteger const &val) const;
    BigInteger operator-(BigInteger const &val) const;
    BigInteger operator*(BigInteger const &val) const;
    BigInteger operator/(BigInteger const &val) const;
    BigInteger operator%(BigInteger const &val) const;
    BigInteger operator<<(unsigned int k) const;
    BigInteger operator>>(unsigned int k) const;
    BigInteger operator+=(BigInteger const &val);
    BigInteger operator-=(BigInteger const &val);
    BigInteger operator*=(BigInteger const &val);
    BigInteger operator/=(BigInteger const &val);
    BigInteger operator%=(BigInteger const &val);
    bool operator<=(BigInteger const &val) const;
    bool operator<(BigInteger const &val) const;
    bool operator>(BigInteger const &val) const;
    bool operator>=(BigInteger const &val) const;
    bool operator==(BigInteger const &val) const;
    bool operator!=(BigInteger const &val) const;
    BigInteger operator=(BigInteger const &val);
    BigInteger operator+(long long val) const;
    BigInteger operator-(long long val) const;
    BigInteger operator*(long long val) const;
    BigInteger operator/(long long val) const;
    BigInteger operator%(long long val) const;
    BigInteger operator+=(long long val);
    BigInteger operator-=(long long val);
    BigInteger operator*=(long long val);
    BigInteger operator/=(long long val);
    BigInteger operator%=(long long val);
    bool operator<=(long long val) const;
    bool operator<(long long val) const;
    bool operator>(long long val) const;
    bool operator>=(long long val) const;
    bool operator==(long long val) const;
    bool operator!=(long long val) const;
    BigInteger operator=(long long val);
    friend int lejandr(BigInteger u, BigInteger v);
    friend BigInteger modPow(BigInteger const &a, BigInteger const &pow, BigInteger const &m);
    friend BigInteger modPowMul(BigInteger const &a, BigInteger const &b, BigInteger const &r,
                                BigInteger const &r1, BigInteger const &n1, BigInteger const &n);
    friend BigInteger modPowMontg(BigInteger const &a, BigInteger const &pow, BigInteger const &m);
    friend istream &operator>>(istream &s, BigInteger b);
    friend ostream &operator<<(ostream &s, BigInteger b);
};

typedef struct Euclid_result
{
    BigInteger d;
    BigInteger x;
    BigInteger y;
} eucl_res;

eucl_res extendEucl(BigInteger const &a, BigInteger const &m);