#pragma once
#include "BigInteger.h"
#include <iostream>
void BigInteger::createVector(long long i)
{
    do
    {
        nums.push_back(i % arifm_system_base);
        i /= arifm_system_base;
    } while (i > 0);
}

BigInteger::BigInteger(int i, int arifm_sys) : BigInteger((long long)i, arifm_sys)
{
}

BigInteger::BigInteger() : BigInteger(0, 2)
{
}

BigInteger::BigInteger(long long i, int arifm_sys) : signum(false), arifm_system_base(arifm_sys)
{
    if (i < 0)
    {
        signum = true;
        i *= -1;
    }
    createVector(i);
}

BigInteger::BigInteger(vector<int> vec, int arifm_sys) : nums(vec), signum(false), arifm_system_base(arifm_sys)
{
}

void BigInteger::createFromString(string str)
{
    nums.clear();
    for (auto i = str.rbegin(); i != str.rend(); i++)
    {
        int shift = 0;
        if ('A' <= *i && *i <= 'F')
            shift = 7;
        nums.push_back(*i - '0' - shift);
    }
}

BigInteger::BigInteger(string str, int arifm_sys) : signum(false), arifm_system_base(arifm_sys)
{
    if (str.size() != 0 && str[0] == '-')
    {
        signum = true;
        str = str.substr(1, str.size() - 1);
    }
    createFromString(str);
}

BigInteger::BigInteger(BigInteger const &bi) : nums(bi.nums), signum(bi.signum), arifm_system_base(bi.arifm_system_base)
{
}

vector<int> BigInteger::getVector() const
{
    return nums;
}

void BigInteger::trim()
{
    while (nums.size() > 1 && nums[nums.size() - 1] == 0)
        nums.pop_back();
}

void BigInteger::setSigned(bool sign)
{
    signum = sign;
}

int BigInteger::getASB() const
{
    return arifm_system_base;
}

bool BigInteger::getSignum() const
{
    return signum;
}

bool BigInteger::isZero()
{
    trim();
    return (nums.size() == 1 && nums[0] == 0);
}

int BigInteger::nextNumber(int final)
{
    int temp = 0;
    for (int i = 0; i < this->nums.size(); i++)
    {
        temp = temp * this->arifm_system_base + this->nums[i];
        nums[i] = temp / final;
        temp = temp % final;
    }
    return temp;
}

void BigInteger::convert(int newArifmBase)
{
    if (newArifmBase != arifm_system_base)
    {
        vector<int> b;
        do
        {
            b.push_back(this->nextNumber(newArifmBase));
        } while (!this->isZero());
        nums = b;
        arifm_system_base = newArifmBase;
    }
}

BigInteger inverse(BigInteger a, BigInteger m)
{
    BigInteger zero(0, a.getASB());
    BigInteger one(1, a.getASB());
    BigInteger t(zero);
    BigInteger r(m);
    BigInteger newT(one);
    BigInteger newR(a);
    BigInteger tmp(zero);
    int count = 0;
    while (newR != zero)
    {
        pair<BigInteger, BigInteger> quotitent = r.divMod(newR, a.getASB());
        std::cout << count++ << std::endl;
        tmp = t - quotitent.first * newT;
        t = newT;
        newT = tmp;

        tmp = quotitent.second;
        r = newR;
        newR = tmp;
    }
    if (r > one)
    {
        one.setSigned(true);
        return one;
    }
    if (t.getSignum())
        t += m;
    return t;
}

BigInteger BigInteger::sum(BigInteger const &v, int arifm_sys) const
{
    if (signum == v.signum)
    {
        BigInteger res = v;
        res.convert(arifm_system_base);

        for (int i = 0, carry = 0; i < (int)max(nums.size(), v.nums.size()) || carry; ++i)
        {
            if (i == (int)res.nums.size())
                res.nums.push_back(0);
            res.nums[i] += carry + (i < (int)nums.size() ? nums[i] : 0);
            carry = res.nums[i] >= arifm_sys;
            if (carry)
                res.nums[i] -= arifm_sys;
        }
        res.convert(arifm_sys);
        return res;
    }
    return *this - (-v);
}

BigInteger BigInteger::operator-() const
{
    BigInteger res(*this);
    res.signum ^= 1;
    return res;
}

void BigInteger::resize(int size)
{
    nums.resize(size);
}

BigInteger BigInteger::mulToArifmSystem() const
{
    BigInteger res(*this);
    res.nums.push_back(0);
    for (int i = res.nums.size() - 1; i > 0; i--)
    {
        res.nums[i] = res.nums[i - 1];
    }
    res.nums[0] = 0;
    res.trim();
    return res;
}

BigInteger BigInteger::mulToChar(int c) const
{
    if (c == arifm_system_base)
        return mulToArifmSystem();
    BigInteger res(*this);
    res.nums.push_back(0);
    char needAdd = 0;
    for (int i = 0; i < res.nums.size(); i++)
    {
        res.nums[i] *= c;
        res.nums[i] += needAdd;
        needAdd = res.nums[i] / arifm_system_base;
        res.nums[i] %= arifm_system_base;
    }
    res.trim();
    return res;
}

BigInteger BigInteger::mul(BigInteger const &val, int arifm_sys) const
{
    BigInteger res(0,val.arifm_system_base);
    BigInteger tmp(*this);
    tmp.convert(val.arifm_system_base);
    for (int i = val.nums.size() - 1; i >= 0; i--)
    {
        res += tmp.mulToChar(val.nums[i]);
        if(i != 0)
            res = res.mulToArifmSystem();
    }
    res.signum = signum ^ val.signum;
    res.trim();
    res.convert(arifm_sys);
    return res;
}

BigInteger BigInteger::divToArifmSystem() const
{
    BigInteger res(*this);
    for (int i = 1; i < res.nums.size(); i++)
    {
        res.nums[i-1] = res.nums[i];
    }
    res.nums.pop_back();
    res.trim();
    return res;
}

BigInteger BigInteger::divToChar(int c) const
{
    if(c == arifm_system_base)
        return divToArifmSystem();
    BigInteger res(*this);
    char needAdd = 0;
    for (int i = res.nums.size() - 1; i >= 0; i--)
    {
        long long cur = res.nums[i] + needAdd * arifm_system_base;
        res.nums[i] = cur / c;
        needAdd = cur % c;
    }
    res.trim();
    return res;
}

pair<BigInteger, BigInteger> BigInteger::divMod(BigInteger const &val, int arifm_sys) const
{
    BigInteger res(0, arifm_sys);
    res.resize(nums.size());
    BigInteger curValue(0, arifm_sys);
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        curValue = curValue.mulToArifmSystem();
        curValue.nums[0] = nums[i];
        // подбираем максимальное число x, такое что b * x <= curValue
        int x = 0;
        int l = 0, r = arifm_sys;
        while (l <= r)
        {
            int m = (l + r) >> 1;
            BigInteger cur = val.mulToChar(m);
            if (cur <= curValue)
            {
                x = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        res.nums[i] = x;
        curValue = curValue - val.mulToChar(x);
    }
    res.signum = signum ^ val.signum;
    res.trim();
    curValue.trim();
    curValue = res.signum ? curValue + val : curValue;
    return make_pair(res, curValue);
}

BigInteger BigInteger::div(BigInteger const &val, int arifm_sys) const
{
    return divMod(val, arifm_sys).first;
}

BigInteger BigInteger::mod(BigInteger const &val, int arifm_sys) const
{
    return divMod(val, arifm_sys).second;
}

BigInteger BigInteger::sub(BigInteger const &v, int arifm_sys) const
{
    if (signum == v.signum)
    {
        if (*this >= v)
        {
            BigInteger res = *this;
            res.convert(v.arifm_system_base);
            for (int i = 0, carry = 0; i < (int)v.nums.size() || carry; ++i)
            {
                res.nums[i] -= carry + (i < (int)v.nums.size() ? v.nums[i] : 0);
                carry = res.nums[i] < 0;
                if (carry)
                    res.nums[i] += arifm_sys;
            }
            res.trim();
            res.convert(arifm_sys);
            return res;
        }
        return -(v - *this);
    }
    return *this + (-v);
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
    string str = b.signum ? "-" : "";
    for (int i = b.nums.size() - 1; i >= 0; i--)
    {
        int shift = 0;
        if (b.nums[i] >= 10)
            shift += 7;
        str += (char)('0' + b.nums[i] + shift);
    }
    s << str;
    return s;
}

int BigInteger::compare(BigInteger const &val) const
{
    if (nums.size() < val.nums.size())
        return 1;
    if (nums.size() > val.nums.size())
        return -1;
    for (int i = nums.size() - 1; i >= 0; i--)
    {
        if (nums[i] > val.nums[i])
            return -1;
        if (nums[i] < val.nums[i])
            return 1;
    }
    return 0;
}

bool BigInteger::operator<=(BigInteger const &val) const
{
    return compare(val) >= 0;
}

bool BigInteger::operator==(BigInteger const &val) const
{
    return compare(val) == 0;
}

bool BigInteger::operator!=(BigInteger const &val) const
{
    return !(*this == val);
}

bool BigInteger::operator<(BigInteger const &val) const
{
    return compare(val) > 0;
}

bool BigInteger::operator>=(BigInteger const &val) const
{
    return !(*this < val);
}

bool BigInteger::operator>(BigInteger const &val) const
{
    return !(*this <= val);
}

BigInteger BigInteger::operator=(BigInteger const &val)
{
    if (this != &val)
    {
        nums.clear();
        nums = val.nums;
        signum = val.signum;
        arifm_system_base = val.arifm_system_base;
    }
    return *this;
}

BigInteger BigInteger::operator+(BigInteger const &val) const
{
    return this->sum(val, arifm_system_base);
}

BigInteger BigInteger::operator*(BigInteger const &val) const
{
    return this->mul(val, arifm_system_base);
}

BigInteger BigInteger::operator-(BigInteger const &val) const
{
    return this->sub(val, arifm_system_base);
}

BigInteger BigInteger::operator/(BigInteger const &val) const
{
    return this->div(val, arifm_system_base);
}

BigInteger BigInteger::operator%(BigInteger const &val) const
{
    return this->mod(val, arifm_system_base);
}

BigInteger BigInteger::operator+=(BigInteger const &val)
{
    return *this = this->sum(val, arifm_system_base);
}

BigInteger BigInteger::operator*=(BigInteger const &val)
{
    return *this = this->mul(val, arifm_system_base);
}

BigInteger BigInteger::operator-=(BigInteger const &val)
{
    return *this = this->sub(val, arifm_system_base);
}

BigInteger BigInteger::operator/=(BigInteger const &val)
{
    return *this = this->div(val, arifm_system_base);
}

BigInteger BigInteger::operator%=(BigInteger const &val)
{
    return *this = this->mod(val, arifm_system_base);
}