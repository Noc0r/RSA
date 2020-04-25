#pragma once
#include <vector>
#include <string>

using namespace std;

class BigInteger
{
private: 
    vector<char> nums;
    void createVector(long long i);
    void createFromString(string str);
    void addVector(vector<char> source, vector<char>& dist) const;
public:
    BigInteger(int i);
    BigInteger(long long i);
    BigInteger();
    BigInteger(string s);
    BigInteger(BigInteger const& b);
    BigInteger(vector<char> b);
    void resize(int size);
    vector<char> getVector() const;
    void trim();
    BigInteger inverse(BigInteger n);
    BigInteger sum(BigInteger const & value) const;
    BigInteger div(BigInteger const& value) const;//TO DO
    BigInteger sup(BigInteger const& value) const;//TO DO
    BigInteger mul(BigInteger const& value) const;
    BigInteger mulToChar(char c) const;

    BigInteger operator+(BigInteger &val) const;//TO DO
    BigInteger operator-(BigInteger &val) const;//TO DO
    BigInteger operator*(BigInteger &val) const;//TO DO
    BigInteger operator/(BigInteger &val) const;//TO DO
    BigInteger operator+(long long val) const;//TO DO
    BigInteger operator-(long long val) const;//TO DO
    BigInteger operator*(long long val) const;
    BigInteger operator/(long long val) const;//TO DO

    BigInteger operator+=(BigInteger &val) const;//TO DO
    BigInteger operator-=(BigInteger &val) const;//TO DO
    BigInteger operator*=(BigInteger &val) const;//TO DO
    BigInteger operator/=(BigInteger &val) const;//TO DO
    BigInteger operator+=(long long val) const;//TO DO
    BigInteger operator-=(long long val) const;//TO DO
    BigInteger operator*=(long long val) const;
    BigInteger operator/=(long long val) const;//TO DO
    
    BigInteger operator>(BigInteger val) const;//TO DO
    BigInteger operator<(BigInteger val) const;//TO DO
    BigInteger operator>=(BigInteger val) const;//TO DO
    BigInteger operator<=(BigInteger val) const;//TO DO
    BigInteger operator==(BigInteger val) const;//TO DO
    BigInteger operator!=(BigInteger val) const;//TO DO

    BigInteger operator>(long long val) const;//TO DO
    BigInteger operator<(long long val) const;//TO DO
    BigInteger operator>=(long long val) const;//TO DO
    BigInteger operator<=(long long val) const;//TO DO
    BigInteger operator==(long long val) const;//TO DO
    BigInteger operator!=(long long val) const;//TO DO
    
    friend istream& operator >>(istream& s,BigInteger b);
    friend ostream& operator <<(ostream& s,BigInteger b);
};