#pragma once
#include "BigInteger.h"

const int arifmSystemBase = 1000000000;

void BigInteger::createVector(long long i)
{
    sign = false;
    if (i < 0)
    {
        sign = true;
        i *= -1;
    }
    do
    {
        nums.push_back(i % arifmSystemBase);
        i /= arifmSystemBase;
    } while (i > 0);
}

BigInteger::BigInteger(int i)
{
    createVector(i);
}

BigInteger::BigInteger()
{
    createVector(0);
}

BigInteger::BigInteger(long long i)
{
    createVector(i);
}

BigInteger::BigInteger(vector<unsigned int> vec) : nums(vec), sign(false)
{
}

void BigInteger::createFromString(string str)
{
    nums.clear();
    int begin = 0;
    sign = false;
    if (str[0] == '-')
    {
        sign = true;
        begin = 1;
    }
    for (int i = str.length(); i > begin; i -= 9)
        if (i < 9)
            nums.push_back(atoi(str.substr(begin, i).c_str()));
        else
            nums.push_back(atoi(str.substr(i - 9, 9).c_str()));
}

BigInteger::BigInteger(string str)
{
    createFromString(str);
}

BigInteger::BigInteger(BigInteger const &bi) : nums(bi.getVector()), sign(bi.sign)
{
}

vector<unsigned int> BigInteger::getVector() const
{
    return nums;
}

void BigInteger::trim()
{
    while (nums.size() > 0 && nums[nums.size() - 1] == 0)
        nums.pop_back();
}

BigInteger BigInteger::sum(BigInteger const &val) const
{
    BigInteger res(*this);
    int sign_mul = val.sign ? -1 : 1;
    int needAdd = 0;
    for (size_t i = 0; i < max(res.nums.size(), val.nums.size()) || needAdd; ++i)
    {
        if (i == res.nums.size())
            res.nums.push_back(0);
        long long tmp = (i < val.nums.size() ? val.nums[i] : 0);
        res.nums[i] += sign_mul * (needAdd + tmp);
        needAdd = (res.nums[i] >= arifmSystemBase) || (res.nums[i] <= 0);
        if (needAdd)
            res.nums[i] -= sign_mul * arifmSystemBase;
    }
    res.trim();
    return res;
}

BigInteger BigInteger::sub(BigInteger const &val) const
{
    BigInteger copy(val);
    copy.sign ^= true;
    return sum(copy);
}

BigInteger BigInteger::div(BigInteger const &val) const
{
}

void BigInteger::resize(int size)
{
    nums.resize(size);
}

BigInteger BigInteger::mulToInt(long long c) const
{
    BigInteger sec(c);
    return this->mul(sec);
}

BigInteger BigInteger::mul(BigInteger const &val) const
{
    BigInteger res(0);
    res.sign = sign ^ val.sign;
    res.resize(nums.size() + val.getVector().size());
    for (size_t i = 0; i < nums.size(); ++i)
        for (size_t j = 0, needAdd = 0; j < val.nums.size() || needAdd; ++j)
        {
            long long tmp = (j < val.nums.size() ? val.nums[j] : 0);
            long long cur = res.nums[i + j] + nums[i] * 1ll * tmp + needAdd;
            res.nums[i + j] = int(cur % arifmSystemBase);
            needAdd = int(cur / arifmSystemBase);
        }
    res.trim();
    return res;
}

BigInteger BigInteger::operator+(long long val) const
{
    return mulToInt(val);
}

BigInteger BigInteger::operator-(long long val) const
{
    return mulToInt(val);
}

BigInteger BigInteger::operator/(long long val) const
{
    return mulToInt(val);
}

BigInteger BigInteger::operator*(long long val) const
{
    return mulToInt(val);
}

BigInteger BigInteger::operator+(BigInteger &val) const
{
}

BigInteger BigInteger::operator-(BigInteger &val) const
{
}

BigInteger BigInteger::operator/(BigInteger &val) const
{
}

BigInteger BigInteger::operator*(BigInteger &val) const
{
}

BigInteger BigInteger::operator+=(long long val)
{
    return mulToInt(val);
}

BigInteger BigInteger::operator-=(long long val)
{
    return mulToInt(val);
}

BigInteger BigInteger::operator/=(long long val)
{
    return mulToInt(val);
}

BigInteger BigInteger::operator*=(long long val)
{
    return mulToInt(val);
}

BigInteger BigInteger::operator+=(BigInteger &val)
{
}

BigInteger BigInteger::operator-=(BigInteger &val)
{
}

BigInteger BigInteger::operator/=(BigInteger &val)
{
}

BigInteger BigInteger::operator*=(BigInteger &val)
{
}

bool BigInteger::operator>(BigInteger &val) const
{
}

bool BigInteger::operator<(BigInteger &val) const
{
}

bool BigInteger::operator>=(BigInteger &val) const
{
}

bool BigInteger::operator<=(BigInteger &val) const
{
}

bool BigInteger::operator!=(BigInteger &val) const
{
}

bool BigInteger::operator==(BigInteger &val) const
{
}

bool BigInteger::operator>(long long val) const
{
}

bool BigInteger::operator<(long long val) const
{
}

bool BigInteger::operator>=(long long val) const
{
}

bool BigInteger::operator<=(long long val) const
{
}

bool BigInteger::operator!=(long long val) const
{
}

bool BigInteger::operator==(long long val) const
{
}

istream &operator>>(istream &s, BigInteger b)
{
    string str;
    s >> str;
    b.createFromString(str);
    return s;
}
ostream &operator<<(ostream &s, BigInteger b)
{
    if(b.sign)
        s << "-";
    for (int i = b.getVector().size() - 1; i >= 0; i--)
        s << b.getVector()[i];
    return s;
}

BigInteger BigInteger::inverse(BigInteger m)
{
    BigInteger t(1);
    BigInteger r(m);
    BigInteger newT(1);
    BigInteger newR(this->getVector());
    BigInteger tmp(0);
    while (newR != 0)
    {
        BigInteger quotitent = r / newR;
        tmp = t.sub(quotitent * newT);
        t = newT;
        newT = tmp;

        tmp = r.sub(quotitent * newR);
        r = newR;
        newR = tmp;
    }
    if (r > 1)
    {
        return -1;
    }
    if (t < 0)
        t += m;
    return t;
}