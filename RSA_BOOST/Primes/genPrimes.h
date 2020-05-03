#pragma once
#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>

using namespace boost::multiprecision;
using namespace std;

typedef struct Euclid_result
{
    cpp_int d;
    cpp_int x;
    cpp_int y;
} eucl_res;

eucl_res extendEucl(cpp_int const &a, cpp_int const &m);

cpp_int modPow(cpp_int const &a, cpp_int const &pow, cpp_int const &m)
{
    cpp_int u = 1;
    cpp_int v = a;
    for (cpp_int i = 1; i < pow; i <<= 1)
    {
        if (pow & i)
            u = (u * v) % m;
        v = (v * v) % m;
    }
    return u;
}

cpp_int modPowMul(cpp_int const &a, cpp_int const &b, cpp_int const &r,
                  cpp_int const &r1, cpp_int const &n1, cpp_int const &n)
{
    cpp_int t = a * b;
    cpp_int u = ((t + n * ((t * n1) % r + r) % r)) / r; // деление на r?!
    return u % n;
}

cpp_int modPowMontg(cpp_int const &a_c, cpp_int const &pow, cpp_int const &n_c)
{
    cpp_int n(n_c);
    cpp_int a(a_c);
    cpp_int one = 1;
    int l = 1, up = 1;
    //Find k(up)
    while ((one << up) < n)
    {
        l = up;
        up *= 2;
    }
    while (l + 1 <= up)
    {
        int m = (l + up) >> 1;
        if ((one << m) > n)
            up = m;
        else
            l = m + 1;
    }
    //modPow
    cpp_int r = (one << up);
    cpp_int a1 = (a * r) % n;
    cpp_int x1 = r % n;
    eucl_res res = extendEucl(r, n);
    cpp_int pow_clone = pow;
    vector<bool> degs;
    while (pow_clone)
    {
        degs.push_back((pow_clone % 2 == 1));
        pow_clone /= 2;
    }

    for (int i = degs.size() - 1; i >= 0; i--)
    {
        x1 = modPowMul(x1, x1, r, res.x, -res.y, n);
        if (degs[i])
            x1 = modPowMul(x1, a1, r, res.x, -res.y, n);
    }
    cpp_int result = modPowMul(x1, one, r, res.x, -res.y, n);
    return result;
}

int lejandr(cpp_int u, cpp_int n)
{ 
    /*
    	
Rules To Find Legendre Symbol
(a/n) = (b/n) if a = b mod n.
(1/n) = 1 and (0/n) = 0.
(2m/n) = (m/n) if n = ±1 mod 8. Otherwise (2m/n) = -(m/n).
(Quadratic reciprocity) 
If m and n are both odd, then (m/n) = (n/m) unless both m and n are congruent to 3 mod 4,
in which case (m/n) = -(n/m).
    */
    int t = 1;
    while (n > 1)
    {
        if (u == 0)
            return 0;
        if (u == 1)
            return t;
        int s = 0;
        cpp_int k = u;
        while (k % 2 == 0)
        {
            s++;
            k = k / 2;
        }
        if (s % 2 == 1 && !(n % 8 == 1 || n % 8 == 7))
            t *= -1;
        if (n % 4 == 3 && k % 4 == 3)
            t *= -1;
        u = n % k;
        n = k;
    }
    return t;
}

eucl_res extendEucl(cpp_int const &a, cpp_int const &m)
{
    cpp_int x_0(1);
    cpp_int y_0(0);
    cpp_int x_1(0);
    cpp_int y_1(1);
    cpp_int r_0(a);
    cpp_int r_1(m);
    while (r_1 != 0)
    {
        cpp_int quotitent = r_0 / r_1;
        cpp_int tmp = r_0 - quotitent * r_1;
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

cpp_int genPrime(int l, bool (*pvmt_func)(int, cpp_int const &, int));
bool checkPrimeFerma(int l, cpp_int const &n, int d);
bool checkPrimeRabin(int l, cpp_int const &n, int d);
bool checkPrimeSolovei(int l, cpp_int const &n, int d);

cpp_int genRand(int l)
{
    cpp_int res = 1;
    cpp_int deg = 2;
    for (int i = 1; i < l - 1; i++)
    {
        if (rand() % 2)
            res += deg;
        deg *= 2;
    }
    res += deg;
    return res;
}

cpp_int genRandMod(int l,cpp_int const& n)
{
    cpp_int a;
    do
    {
        a = genRand(l+1)%n;
    } while (a==0);
    return a;
}

cpp_int genPrime(int l, bool (*pvmt_func)(int, cpp_int const &, int))
{
    const int d = 100;
    int i = 0;
    cpp_int n = genRand(l);
    while (!pvmt_func(l, n, d))
    {
        cout << i++ << ": " << n << endl;
        n = genRand(l);
    }
    return n;
}

bool checkPrimeFerma(int len, cpp_int const &n, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        cpp_int a = genRandMod(len, n);
        eucl_res res = extendEucl(a, n);
        if (res.d != 1 || modPow(a, n - 1, n) != 1)
        {
            cout << a << endl;
            cout << n << endl;
            cout << res.d << endl;
            cout << modPow(a, n - 1, n) << endl;
            return false;
        }
    }
    return true;
}

bool checkPrimeRabin(int len, cpp_int const &n, int dim)
{
    int s = 0;
    cpp_int r = n - 1;
    while (r % 2 == 0)
    {
        r /= 2;
        s++;
    }
    for (int i = 0; i < dim; i++)
    {
        cpp_int a = genRandMod(len, n);
        eucl_res res = extendEucl(a, n);
        if (res.d != 1)
            return false;
        cpp_int v = modPow(a, r, n);
        if (v == 1)
            continue;
        bool isCorrect = false;
        for (int i = 0; i < s; i++)
        {
            if (v == -1 || v == n - 1)
            {
                isCorrect = true;
                break;
            }
            v = (v * v) % n;
        }
        if (!isCorrect)
            return false;
    }
    return true;
}

bool checkPrimeSolovei(int len, cpp_int const &n, int dim)
{
    for (int i = 0; i < dim; i++)
    {
        cpp_int a = genRandMod(len, n);
        eucl_res res = extendEucl(a, n);
        cpp_int b = (modPow(a, (n - 1) / 2, n) - lejandr(a, n));
        if (res.d != 1 || (b != 0 && b != n))
        {
            return false;
        }
    }
    return true;
}
