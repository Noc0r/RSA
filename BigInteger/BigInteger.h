#pragma once
#include <vector>
#include <string>

using namespace std;

class BigInteger
{
private:
    vector<unsigned int> nums;
    bool sign;
    void createVector(long long i);
    void createFromString(string str);

public:
    BigInteger(int i);
    BigInteger(long long i);
    BigInteger();
    BigInteger(string s);
    BigInteger(BigInteger const &b);
    BigInteger(vector<unsigned int> b);
    void resize(int size);
    vector<unsigned int> getVector() const;
    void trim();
    BigInteger inverse(BigInteger n);
    BigInteger sum(BigInteger const &value) const;
    BigInteger div(BigInteger const &value) const; //TO DO
    BigInteger sub(BigInteger const &value) const; //TO DO
    BigInteger mul(BigInteger const &value) const;
    BigInteger mulToInt(long long c) const;

    BigInteger operator+(BigInteger &val) const; //TO DO
    BigInteger operator-(BigInteger &val) const; //TO DO
    BigInteger operator*(BigInteger &val) const; //TO DO
    BigInteger operator/(BigInteger &val) const; //TO DO
    BigInteger operator+(long long val) const;   //TO DO
    BigInteger operator-(long long val) const;   //TO DO
    BigInteger operator*(long long val) const;
    BigInteger operator/(long long val) const; //TO DO

    BigInteger operator+=(BigInteger &val); //TO DO
    BigInteger operator-=(BigInteger &val); //TO DO
    BigInteger operator*=(BigInteger &val); //TO DO
    BigInteger operator/=(BigInteger &val); //TO DO
    BigInteger operator+=(long long val);   //TO DO
    BigInteger operator-=(long long val);   //TO DO
    BigInteger operator*=(long long val);
    BigInteger operator/=(long long val); //TO DO

    bool operator>(BigInteger &val) const;  //TO DO
    bool operator<(BigInteger &val) const;  //TO DO
    bool operator>=(BigInteger &val) const; //TO DO
    bool operator<=(BigInteger &val) const; //TO DO
    bool operator==(BigInteger &val) const; //TO DO
    bool operator!=(BigInteger &val) const; //TO DO

    bool operator>(long long val) const;  //TO DO
    bool operator<(long long val) const;  //TO DO
    bool operator>=(long long val) const; //TO DO
    bool operator<=(long long val) const; //TO DO
    bool operator==(long long val) const; //TO DO
    bool operator!=(long long val) const; //TO DO

    friend istream &operator>>(istream &s, BigInteger b);
    friend ostream &operator<<(ostream &s, BigInteger b);
};