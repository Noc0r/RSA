#pragma once
#include <vector>
#include <string>

using namespace std;

class BigInteger
{
private:
    bool signum;
    vector<int> nums;
    int arifm_system_base;
    pair<BigInteger,BigInteger> divMod(BigInteger const &val, int arifm_sys) const;
    int compare(BigInteger const& val) const;
    void createVector(long long i);
    void createFromString(string str);
    int nextNumber(int final);
    BigInteger mulToArifmSystem() const;
    BigInteger divToArifmSystem() const;

public:
    BigInteger(int i, int arifm_sys);
    BigInteger(long long i, int arifm_sys);
    BigInteger();
    BigInteger(string s, int arifm_sys);
    BigInteger(BigInteger const &b);
    BigInteger(vector<int> b, int arifm_sys);
    int getASB() const;
    bool getSignum() const;
    vector<int> getVector() const;
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
    BigInteger mulToChar(int c) const;
    BigInteger divToChar(int c) const;
    BigInteger operator+(BigInteger const &val) const;
    BigInteger operator-(BigInteger const &val) const;
    BigInteger operator-() const;
    BigInteger operator*(BigInteger const &val) const;
    BigInteger operator/(BigInteger const &val) const;
    BigInteger operator%(BigInteger const &val) const;
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
    friend BigInteger inverse(BigInteger a, BigInteger m);
    friend istream &operator>>(istream &s, BigInteger b);
    friend ostream &operator<<(ostream &s, BigInteger b);
};