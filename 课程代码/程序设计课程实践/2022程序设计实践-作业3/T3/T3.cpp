//实现了加减乘除取余，乘法可用FFT函数
#include<bits/stdc++.h>
using namespace std;
#ifdef LOCAL
FILE* FP = freopen("text.in", "r", stdin);
//FILE*fp=freopen("text.out","w",stdout);
#endif
struct BigIntTiny {
    int sign;
    std::vector<int> v;

    BigIntTiny() : sign(1) {}
    BigIntTiny(const std::string &s) { *this = s; }
    BigIntTiny(int v) {
        char buf[21];
        sprintf(buf, "%d", v);
        *this = buf;
    }
    void zip(int unzip) {
        if (unzip == 0) {
            for (int i = 0; i < (int)v.size(); i++)
                v[i] = get_pos(i * 4) + get_pos(i * 4 + 1) * 10 + get_pos(i * 4 + 2) * 100 + get_pos(i * 4 + 3) * 1000;
        } else
            for (int i = (v.resize(v.size() * 4), (int)v.size() - 1), a; i >= 0; i--)
                a = (i % 4 >= 2) ? v[i / 4] / 100 : v[i / 4] % 100, v[i] = (i & 1) ? a / 10 : a % 10;
        setsign(1, 1);
    }
    int get_pos(unsigned pos) const { return pos >= v.size() ? 0 : v[pos]; }
    BigIntTiny &setsign(int newsign, int rev) {
        for (int i = (int)v.size() - 1; i > 0 && v[i] == 0; i--)
            v.erase(v.begin() + i);
        sign = (v.size() == 0 || (v.size() == 1 && v[0] == 0)) ? 1 : (rev ? newsign * sign : newsign);
        return *this;
    }
    std::string to_str() const {
        BigIntTiny b = *this;
        std::string s;
        for (int i = (b.zip(1), 0); i < (int)b.v.size(); ++i)
            s += char(*(b.v.rbegin() + i) + '0');
        return (sign < 0 ? "-" : "") + (s.empty() ? std::string("0") : s);
    }
    bool absless(const BigIntTiny &b) const {
        if (v.size() != b.v.size()) return v.size() < b.v.size();
        for (int i = (int)v.size() - 1; i >= 0; i--)
            if (v[i] != b.v[i]) return v[i] < b.v[i];
        return false;
    }
    BigIntTiny operator-() const {
        BigIntTiny c = *this;
        c.sign = (v.size() > 1 || v[0]) ? -c.sign : 1;
        return c;
    }
    BigIntTiny &operator=(const std::string &s) {
        if (s[0] == '-')
            *this = s.substr(1);
        else {
            for (int i = (v.clear(), 0); i < (int)s.size(); ++i)
                v.push_back(*(s.rbegin() + i) - '0');
            zip(0);
        }
        return setsign(s[0] == '-' ? -1 : 1, sign = 1);
    }
    bool operator<(const BigIntTiny &b) const {
        return sign != b.sign ? sign < b.sign : (sign == 1 ? absless(b) : b.absless(*this));
    }
    bool operator==(const BigIntTiny &b) const { return v == b.v && sign == b.sign; }
    BigIntTiny &operator+=(const BigIntTiny &b) {
        if (sign != b.sign) return *this = (*this) - -b;
        v.resize(std::max(v.size(), b.v.size()) + 1);
        for (int i = 0, carry = 0; i < (int)b.v.size() || carry; i++) {
            carry += v[i] + b.get_pos(i);
            v[i] = carry % 10000, carry /= 10000;
        }
        return setsign(sign, 0);
    }
    BigIntTiny operator+(const BigIntTiny &b) const {
        BigIntTiny c = *this;
        return c += b;
    }
    void add_mul(const BigIntTiny &b, int mul) {
        v.resize(std::max(v.size(), b.v.size()) + 2);
        for (int i = 0, carry = 0; i < (int)b.v.size() || carry; i++) {
            carry += v[i] + b.get_pos(i) * mul;
            v[i] = carry % 10000, carry /= 10000;
        }
    }
    BigIntTiny operator-(const BigIntTiny &b) const {
        if (sign != b.sign) return (*this) + -b;
        if (absless(b)) return -(b - *this);
        BigIntTiny c;
        for (int i = 0, borrow = 0; i < (int)v.size(); i++) {
            borrow += v[i] - b.get_pos(i);
            c.v.push_back(borrow);
            c.v.back() -= 10000 * (borrow >>= 31);
        }
        return c.setsign(sign, 0);
    }
    BigIntTiny operator*(const BigIntTiny &b) const {
        if (b < *this) return b * *this;
        BigIntTiny c, d = b;
        for (int i = 0; i < (int)v.size(); i++, d.v.insert(d.v.begin(), 0))
            c.add_mul(d, v[i]);
        return c.setsign(sign * b.sign, 0);
    }
    BigIntTiny operator/(const BigIntTiny &b) const {
        BigIntTiny c, d;
        d.v.resize(v.size());
        double db = 1.0 / (b.v.back() + (b.get_pos((unsigned)b.v.size() - 2) / 1e4) +
                           (b.get_pos((unsigned)b.v.size() - 3) + 1) / 1e8);
        for (int i = (int)v.size() - 1; i >= 0; i--) {
            c.v.insert(c.v.begin(), v[i]);
            int m = (int)((c.get_pos((int)b.v.size()) * 10000 + c.get_pos((int)b.v.size() - 1)) * db);
            c = c - b * m, d.v[i] += m;
            while (!(c < b))
                c = c - b, d.v[i] += 1;
        }
        return d.setsign(sign * b.sign, 0);
    }
    BigIntTiny operator%(const BigIntTiny &b) const { return *this - *this / b * b; }
    bool operator>(const BigIntTiny &b) const { return b < *this; }
    bool operator<=(const BigIntTiny &b) const { return !(b < *this); }
    bool operator>=(const BigIntTiny &b) const { return !(*this < b); }
    bool operator!=(const BigIntTiny &b) const { return !(*this == b); }
};
//FFT部分 
const double PI = acos(-1);
typedef complex<double> Complex;
const int maxn = 3e6 + 10;

Complex a[maxn], b[maxn];
int m, n;
int bit = 2, rev[maxn];
int ans[maxn];

void get_rev(){
    memset(rev, 0, sizeof(rev));
    while(bit <= n + m) bit <<= 1;
    for(int i = 0; i < bit; ++i) {
        rev[i] = (rev[i >> 1] >> 1) | (bit >> 1) * (i & 1);
    }
}

void FFT(Complex *a, int op) {
    for(int i = 0; i < bit; ++i) {
        if(i < rev[i]) swap(a[i], a[rev[i]]);
    }
    for(int mid = 1; mid < bit; mid <<= 1) {
        Complex wn = Complex(cos(PI / mid), op * sin(PI / mid));
        for(int j = 0; j < bit; j += mid<<1) {
            Complex w(1, 0);
            for(int k = 0; k < mid; ++k, w = w * wn) {
                Complex x = a[j + k], y = w * a[j + k + mid];
                a[j + k] = x + y, a[j + k + mid] = x - y;
            }
        }
    }
}

string fftmul(string s1,string s2){
	//cout<<s1<<endl<<s2<<endl;
	    n = s1.size(), m = s2.size();
        memset(a, 0, sizeof(a));
        memset(b, 0, sizeof(b));
        for(int i = 0; i < n; ++i) {
            a[i] = s1[n - i - 1] - '0';
        }
        for(int i = 0; i < m; ++i) {
            b[i] = s2[m - i - 1] - '0';
        }
        get_rev();
        FFT(a, 1);
        FFT(b, 1);
        for(int i = 0; i <= bit; ++i) {
            a[i] *= b[i];
        }
        FFT(a, -1);
        for(int i = 0; i < n + m; ++i) {
            ans[i] = (int)(a[i].real() / bit + 0.5);
        }
        for(int i = 1; i < n + m; ++i) {
            ans[i] = ans[i] + ans[i - 1] / 10;
            ans[i - 1] = ans[i - 1] % 10;
        }
        int s = n + m - 1;
        for(; s >= 0; --s) {
            if(ans[s]) break;
        }
        string ret;
        if(s < 0) ret.push_back('0');//printf("0\n");
        else {
            for(int i = s; i >= 0; --i) {
                ret.push_back(ans[i]+'0');//printf("%d", ans[i]);
            }
            //printf("\n");
        }
        return ret;
}

BigIntTiny fastmul(BigIntTiny b1,BigIntTiny b2){
	//cout<<b1.to_str()<<'\n'<<b2.to_str()<<endl;
	//cout<<fftmul(b1.to_str(),b2.to_str())<<endl;
	bool flag=0;//要不要变负,1负
	if(b1<0)b1=-b1,flag^=1;
	if(b2<0)b2=-b2,flag^=1;
	BigIntTiny ans=fftmul(b1.to_str(),b2.to_str());
	return flag?-ans:ans;
}

//FFT结束 
signed main(){
	int t;
	scanf("%d",&t);
	while(t--){
		string s1,s2;
		cin>>s1>>s2;
		BigIntTiny a(s1),b(s2);
		//cout<<(a*b).to_str()<<endl;
		cout<<fastmul(a,b).to_str()<<endl;
	}
}