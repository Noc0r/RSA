#pragma once
#include "BigInteger.h"

const short int arifmSystemBase = 10;

void BigInteger::createVector(long long i)
{
    do
    {
        nums.push_back(i % 10);
        i /= 10;
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

BigInteger::BigInteger(vector<char> vec) : nums(vec)
{
}

void BigInteger::createFromString(string str)
{
    nums.clear();
    for (auto i = str.rbegin(); i != str.rend(); i++)
    {
        nums.push_back(*i - '0');
    }
}

BigInteger::BigInteger(string str)
{
    createFromString(str);
}

BigInteger::BigInteger(BigInteger const &bi) : nums(bi.getVector())
{
}

vector<char> BigInteger::getVector() const
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
    if (this->nums.size() < val.getVector().size())
        return val.sum(*this);
    vector<char> vec;
    vec.resize(nums.size() + 1);
    for (size_t i = 0; i < val.getVector().size(); i++)
    {
        vec[i] += nums[i] + val.getVector()[i];
        if (vec[i] >= arifmSystemBase)
        {
            vec[i] %= arifmSystemBase;
            ++vec[i + 1];
        }
    }
    for (size_t i = val.getVector().size(); i < nums.size(); i++)
    {
        vec[i] += nums[i];
        if (vec[i] >= arifmSystemBase)
        {
            vec[i] %= arifmSystemBase;
            ++vec[i + 1];
        }
    }
    BigInteger res(vec);
    res.trim();
    return res;
}

void BigInteger::addVector(vector<char> source, vector<char> &dist) const
{
    for (size_t i = 0; i < source.size(); i++)
        dist.push_back(source[i]);
}

void BigInteger::resize(int size)
{
    nums.resize(size);
}

BigInteger BigInteger::mulToChar(char c) const
{
    BigInteger res(*this);
    res.nums.push_back(0);
    char needAdd = 0;
    for (size_t i = 0; i < res.nums.size(); i++)
    {
        res.nums[i] *= c;
        res.nums[i] += needAdd;
        needAdd = res.nums[i] / arifmSystemBase;
        res.nums[i] %= arifmSystemBase;
    }
    res.trim();
    return res;
}

BigInteger BigInteger::mul(BigInteger const &val) const
{
    BigInteger res(0);
    res.resize(nums.size() + val.getVector().size());
    for (int i = 0; i < val.getVector().size(); i++)
    {
        vector<char> mul = this->mulToChar(val.getVector()[i]).getVector();
        vector<char> elem;
        for (int j = 0; j < i; j++)
            elem.push_back(0);
        addVector(mul, elem);
        BigInteger b(elem);
        res = res.sum(b);
    }
    res.trim();
    return res;
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
        tmp = t - quotitent * newT;
        t = newT;
        newT = tmp;

        tmp = r - quotitent * newR;
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

BigInteger BigInteger::operator*(long long val) const
{
    BigInteger res(val);
    BigInteger answ = res.mul(*this);
    return answ;
}

istream &operator>>(istream &s, BigInteger b)
{
    //TO DO
    string str;
    s >> str;
    b.createFromString(str);
    return s;
}
ostream &operator<<(ostream &s, BigInteger b)
{
    string str = "";
    for (int i = b.getVector().size() - 1; i >= 0; i--)
        str += (char)('0' + b.getVector()[i]);
    s << str;
    return s;
}
