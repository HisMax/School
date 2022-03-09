//
#include <bits/stdc++.h>
#define _for(i, a, b) for (int i = (a); i < (b); ++i)
#define _rep(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;

struct BigInteger
{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> s; // increase significance order
    int flag;

    BigInteger(long long num = 0) : flag(1) { *this = num; }

    BigInteger(const BigInteger &b)
    {
        s = b.s;
        flag = b.flag;
    }
    BigInteger(BigInteger &&b)
    {
        s = move(b.s);
        flag = b.flag;
    }
    BigInteger &operator=(const BigInteger &b)
    {
        s = b.s;
        flag = b.flag;
        return *this;
    }
    BigInteger &operator=(BigInteger &&b)
    {
        s = move(b.s);
        flag = b.flag;
        return *this;
    }

    BigInteger operator=(long long num)
    {
        s.clear();
        if (num < 0)
        {
            num = -num;
            flag = -1;
        }
        do
        {
            s.push_back(num % BASE);
            num /= BASE;
        } while (num != 0);
        return *this;
    }
    BigInteger operator=(const char *str)
    {
        s.clear();
        if (str[0] == '-')
        {
            flag = -1;
            str++;
        }
        int x, slen = strlen(str), len = slen / WIDTH; // 不同常见的-1+1，这里整除要正好放在这里处理
        for (int i = 0; i < len; i++)
        {
            int start = slen - (i + 1) * WIDTH;
            sscanf(str + start, "%8d", &x);
            s.push_back(x);
        }
        int more = slen % WIDTH;
        if (more != 0)
        {
            char t[WIDTH];
            memcpy(t, str, more);
            t[more] = '\0';
            sscanf(t, "%d", &x);
            s.push_back(x);
        }
        return *this;
    }
    BigInteger operator=(const string &str)
    {
        return BigInteger::operator=(str.c_str());
    }
    bool operator<(const BigInteger &b) const
    {
        if (flag != b.flag)
            return flag < b.flag;
        if (s.size() != b.s.size())
            return (s.size() < b.s.size()) ^ (flag < 0);
        for (int i = s.size() - 1; i >= 0; i--)
            if (s[i] != b.s[i])
                return (s[i] < b.s[i]) ^ (flag < 0);
        return false;
    }
    bool operator>(const BigInteger &b) const
    {
        return b < *this;
    }
    bool operator==(const BigInteger &b) const
    {
        return !(*this < b) && !(*this > b);
    }
    bool operator<=(const BigInteger &b) const
    {
        return !(*this < b);
    }
    bool operator>=(const BigInteger &b) const
    {
        return !(*this > b);
    }
    BigInteger operator-() const
    {
        BigInteger c = *this;
        c.flag = -c.flag;
        return c;
    }

    void delete_leading_zero()
    {
        while (!s.empty() && s.back() == 0)
            s.pop_back();
    }
    BigInteger operator+(const BigInteger &b) const
    {
        BigInteger c;
        c.s.clear();
        int flag_a = flag, flag_b = b.flag;
        if (*this < -b) // a + b < 0
        {
            c.flag = -1;
            flag_a = -flag_a;
            flag_b = -flag_b;
        } // assert(a + b > 0)
        for (int i = 0, g = 0;; i++)
        {
            if (g == 0 && i >= s.size() && i >= b.s.size())
                break;
            int x = g;
            if (i < s.size())
                x += s[i] * flag_a;
            if (i < b.s.size())
                x += b.s[i] * flag_b;
            g = x / BASE;
            if (x < 0)
            {
                x += BASE;
                g--;
            }
            c.s.push_back(x % BASE);
        }
        c.delete_leading_zero();
        return c;
    }
    BigInteger operator-(const BigInteger &b) const
    {
        return *this + (-b);
    }
};

ostream &operator<<(ostream &out, const BigInteger &x)
{
    if (x.flag < 0)
        out << '-';
    out << x.s.back();
    for (int i = x.s.size() - 2; i >= 0; i--)
    {
        char buf[20];
        sprintf(buf, "%08d", x.s[i]);
        for (int j = 0; j < strlen(buf); j++)
            out << buf[j];
    }
    return out;
}

istream &operator>>(istream &in, BigInteger &x)
{
    string s;
    if (!(in >> s))
        return in;
    x = s;
    return in;
}

void solve()
{
    BigInteger a, b;
    while (cin >> a >> b)
    {
        cout << a + b << endl;
        cout << a - b << endl;
    }
}

int main()
{
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef _DEBUG
    freopen("i", "r", stdin);
    // freopen("o", "w", stdout);
#endif

    solve();
}
