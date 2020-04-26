#pragma once
#include "BigInteger.h"
#include <iostream>
#include <algorithm>

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
    for (int i = this->nums.size() - 1; i >= 0; i--)
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

BigInteger modPow(BigInteger const &a, BigInteger const &pow, BigInteger const &m)
{
    BigInteger u(1, m.arifm_system_base);
    BigInteger v(a);
    v.convert(m.arifm_system_base);
    BigInteger powBin(pow);
    powBin.convert(2);
    for (int i = 0; i < powBin.getVector().size(); i++)
    {
        if (powBin.getVector()[i])
            u = (u * v) % m;
        v = (v * v) % m;
    }
    return u;
}

BigInteger modPowMul(BigInteger const &a, BigInteger const &b, BigInteger const &r,
                     BigInteger const &r1, BigInteger const &n1, BigInteger const &n)
{
    BigInteger t = a * b;
    BigInteger u = (t + n * ((t * n1) % r)) * r1;
    while (u >= n)
    {
        u -= n;
    }
    return u;
}

BigInteger modPowMontg(BigInteger const &a, BigInteger const &pow, BigInteger const &n)
{
    int l = 1, up = n.arifm_system_base;
    //Find k(up)
    while (BigInteger(1, a.arifm_system_base).mulToArifmSystem(up) < n)
    {
        l = up;
        up *= n.arifm_system_base;
    }
    while (l + 1 <= up)
    {
        int m = (l + up) >> 1;
        if (BigInteger(1, a.arifm_system_base).mulToArifmSystem(m) > n)
            up = m;
        else
            l = m;
    }
    //modPow
    BigInteger r = BigInteger(1, a.arifm_system_base).mulToArifmSystem(up);
    BigInteger a1 = (a * r) % n;
    BigInteger x1 = r % n;
    eucl_res res = extendEucl(r, n);
    BigInteger powBin(pow);
    powBin.convert(2);
    for (int i = powBin.nums.size() - 1; i >= 0; i++)
    {
        x1 = modPowMul(x1, x1, r, res.x, res.y, n);
        if (powBin.nums[i])
            x1 = modPowMul(x1, a1, r, res.x, res.y, n);
    }
    return modPowMul(x1, BigInteger(1, n.arifm_system_base), r, res.x, res.y, n);
}

BigInteger BigInteger::sum(BigInteger const &v, int arifm_sys) const
{
    if (signum == v.signum)
    {
        BigInteger res = v;
        res.convert(arifm_system_base);
        for (int i = 0, carry = 0; i < (int)max(nums.size(), res.nums.size()) || carry; ++i)
        {
            if (i == (int)res.nums.size())
                res.nums.push_back(0);
            res.nums[i] += carry + (i < (int)nums.size() ? nums[i] : 0);
            carry = res.nums[i] >= arifm_system_base;
            if (carry)
                res.nums[i] -= arifm_system_base;
        }
        res.convert(arifm_sys);
        return res;
    }
    return this->sub(-v, arifm_sys);
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

BigInteger BigInteger::mulToArifmSystem(unsigned int k) const
{
    vector<int> res_vec(k);
    fill(res_vec.begin(), res_vec.end(), 0);
    res_vec.insert(res_vec.end(), nums.begin(), nums.end());
    BigInteger res(res_vec, arifm_system_base);
    res.signum = signum;
    res.trim();
    return res;
}

BigInteger BigInteger::mulToChar(int c) const
{
    if (c == arifm_system_base)
        return mulToArifmSystem(1);
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
    BigInteger res(0, val.arifm_system_base);
    BigInteger tmp(*this);
    tmp.convert(val.arifm_system_base);
    for (int i = val.nums.size() - 1; i >= 0; i--)
    {
        res += tmp.mulToChar(val.nums[i]);
        if (i != 0)
            res = res.mulToArifmSystem(1);
    }
    res.signum = signum ^ val.signum;
    res.trim();
    res.convert(arifm_sys);
    return res;
}

BigInteger BigInteger::divToArifmSystem(unsigned int k) const
{
    if (k > nums.size())
        return BigInteger(0, arifm_system_base);
    vector<int> res_vec(nums.begin() + k, nums.end());
    BigInteger res(res_vec, arifm_system_base);
    res.signum = signum;
    return res;
}

BigInteger BigInteger::divToChar(int c) const
{
    if (c == arifm_system_base)
        return divToArifmSystem(1);
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

pair<BigInteger, BigInteger> BigInteger::divMod(BigInteger const &denominator, int arifm_sys) const
{
    BigInteger numerator(*this);
    BigInteger res(0, denominator.arifm_system_base);
    res.resize(nums.size());
    BigInteger curValue(0, denominator.arifm_system_base);
    for (int i = numerator.nums.size() - 1; i >= 0; i--)
    {
        curValue = curValue.mulToArifmSystem(1);
        curValue.nums[0] = numerator.nums[i];
        // подбираем максимальное число x, такое что b * x <= curValue
        int x = 0;
        int l = 0, r = denominator.arifm_system_base;
        while (l <= r)
        {
            int m = (l + r) >> 1;
            BigInteger cur = denominator.mulToChar(m);
            if (cur <= curValue)
            {
                x = m;
                l = m + 1;
            }
            else
                r = m - 1;
        }
        res.nums[i] = x;
        curValue = curValue - denominator.mulToChar(x);
    }
    res.signum = signum ^ denominator.signum;
    res.trim();
    curValue.trim();
    curValue = res.signum ? curValue + denominator : curValue;
    res.convert(arifm_sys);
    curValue.convert(arifm_sys);
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
        return -v.sub(*this, arifm_sys);
    }
    return this->sum(-v, arifm_sys);
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
    BigInteger cpy(*this);
    cpy.convert(val.arifm_system_base);
    if (cpy.nums.size() < val.nums.size())
        return 1;
    if (cpy.nums.size() > val.nums.size())
        return -1;
    for (int i = cpy.nums.size() - 1; i >= 0; i--)
    {
        if (cpy.nums[i] > val.nums[i])
            return -1;
        if (cpy.nums[i] < val.nums[i])
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

BigInteger BigInteger::operator<<(unsigned int k) const
{
    return mulToArifmSystem(k);
}
BigInteger BigInteger::operator>>(unsigned int k) const
{
    return divToArifmSystem(k);
}

bool BigInteger::operator<=(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return compare(v) >= 0;
}

bool BigInteger::operator==(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return compare(v) == 0;
}

bool BigInteger::operator!=(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return !(*this == v);
}

bool BigInteger::operator<(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return compare(v) > 0;
}

bool BigInteger::operator>=(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return !(*this < v);
}

bool BigInteger::operator>(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return !(*this <= v);
}

BigInteger BigInteger::operator=(long long val)
{
    BigInteger v(val, arifm_system_base);
    if (this != &v)
    {
        nums.clear();
        nums = v.nums;
        signum = v.signum;
        arifm_system_base = v.arifm_system_base;
    }
    return *this;
}

BigInteger BigInteger::operator+(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return this->sum(v, arifm_system_base);
}

BigInteger BigInteger::operator*(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return this->mul(v, arifm_system_base);
}

BigInteger BigInteger::operator-(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return this->sub(v, arifm_system_base);
}

BigInteger BigInteger::operator/(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return this->div(v, arifm_system_base);
}

BigInteger BigInteger::operator%(long long val) const
{
    BigInteger v(val, arifm_system_base);
    return this->mod(v, arifm_system_base);
}

BigInteger BigInteger::operator+=(long long val)
{
    BigInteger v(val, arifm_system_base);
    return *this = this->sum(v, arifm_system_base);
}

BigInteger BigInteger::operator*=(long long val)
{
    BigInteger v(val, arifm_system_base);
    return *this = this->mul(v, arifm_system_base);
}

BigInteger BigInteger::operator-=(long long val)
{
    BigInteger v(val, arifm_system_base);
    return *this = this->sub(v, arifm_system_base);
}

BigInteger BigInteger::operator/=(long long val)
{
    BigInteger v(val, arifm_system_base);
    return *this = this->div(v, arifm_system_base);
}

BigInteger BigInteger::operator%=(long long val)
{
    BigInteger v(val, arifm_system_base);
    return *this = this->mod(v, arifm_system_base);
}

int lejandr(BigInteger u, BigInteger n)
{
    BigInteger one(1, u.arifm_system_base);
    int t = 1;
    while (n > one)
    {
        if (u.isZero())
            return 0;
        if (u == one)
            return 1;
        BigInteger s(0, u.arifm_system_base);
        BigInteger k = u;
        while (k.nums[0] & 1 == 0)
        {
            s += one;
            k = k / 2;
        }
        if (s % 2 == 1 && (n % 8 == 3 || n % 8 == 5))
            t *= -1;
        if (n % 4 == 3 && k % 4 == 3)
            t *= -1;
        u = n % k;
        n = k;
    }
    return t;
}

eucl_res extendEucl(BigInteger const &a, BigInteger const &m)
{
    BigInteger zero(0, a.getASB());
    BigInteger one(1, a.getASB());
    BigInteger x_0(one);
    BigInteger y_0(zero);
    BigInteger x_1(zero);
    BigInteger y_1(one);
    BigInteger r_0(m);
    BigInteger r_1(a);
    while (r_1 != zero)
    {
        BigInteger quotitent = r_0.div(r_1, a.getASB());
        BigInteger tmp = r_0 - quotitent * r_1;
        r_0 = r_1;
        r_1 = tmp;
        tmp = x_0 - quotitent * x_1;
        x_0 = x_1;
        x_1 = tmp;
        tmp = y_0 - quotitent * y_1;
        y_0 = y_1;
        y_1 = tmp;
    }
    eucl_res res = {r_0, x_0, y_0};
    return res;
}
