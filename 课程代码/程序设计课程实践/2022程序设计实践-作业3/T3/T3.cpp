#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

const int MAXN=1e5;
const int siz=8;
const long long MOD=1e8;//MOD=10^siz

char ch1[MAXN],ch2[MAXN];
bool f1,f2,f;//0为非负，1为负
long long n;
long long a[MAXN>>2],b[MAXN>>2],s[MAXN>>2];
long long cp[MAXN>>2],lt[MAXN>>2],wsd[MAXN>>2];

void write(long long num[]);//输出高精度数
void clear(long long num[]);//数组重置
void ry(long long num[]);//>>右移一位
void ly(long long num[]);//<<左移一位
void cpy(long long num1[],long long num2[]);//num1=num2
int cmp(long long num1[],long long num2[]);//compare num1 and num2
void pls(long long a[],long long b[]);//plus加法
void mnu(long long a[],long long b[]);//minus减法
void mul(long long a[],long long b[]);//multiply乘法
void div(long long a[],long long b[]);//divided除法

void write(long long num[])
{
	if(f) putchar('-'),f=0;
	printf("%lld",num[num[0]]);
	for(int i=num[0]-1;i;--i) printf("%08lld",num[i]);
	puts("");
}

void clear(long long num[])
{
	for(int i=num[0];i;--i) num[i]=0;
	num[0]=1;
}

void ry(long long num[])
{
	for(int i=num[0];i;--i){
		if((num[i]&1)&&i>1) num[i-1]+=MOD;//将1借到下一位
		num[i]>>=1;
	}if(!num[num[0]]&&num[0]>1) --num[0];
}

void ly(long long num[])
{
	++num[0];
	for(int i=1;i<=num[0];++i){
		num[i]<<=1;
		if(num[i-1]>=MOD) num[i-1]-=MOD,++num[i];//进位，注意后效性
	}if(!num[num[0]]&&num[0]>1) --num[0];
	return;
}

void cpy(long long num1[],long long num2[])
{
	for(int i=num1[0];i>num2[0];--i) num1[i]=0;
	for(int i=0;i<=num2[0];++i) num1[i]=num2[i];
}

int cmp(long long num1[],long long num2[])
{
	if(num1[0]>num2[0]) return 1;
	if(num1[0]<num2[0]) return -1;
	for(int i=num1[0];i;--i){
		if(num1[i]>num2[i]) return 1;
		if(num1[i]<num2[i]) return -1;
	}return 0;
}

void init()
{
	scanf("%s%s",ch1,ch2);
	if(ch1[0]=='-') ch1[0]='0',f1=1;
	if(ch2[0]=='-') ch2[0]='0',f2=1;//符号处理
	int l1=strlen(ch1),l2=strlen(ch2);
	for(int i=l1-1;i>=0;i-=siz){
		long long pw=1;++a[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			a[a[0]]+=(ch1[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}for(int i=l2-1;i>=0;i-=siz){
		long long pw=1;++b[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			b[b[0]]+=(ch2[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}return;//反序读入存储
}

void pls(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,mnu(b,a),f1^=1;//a+b=b-(-a)
		if(f2) f2^=1,mnu(a,b),f2^=1;//a+b=a-(-b)
		return;
	}if(f1&f2){
		f1=f2=0,f^=1,pls(a,b);//两个负数绝对值相加，符号为负
		f1=f2=1;return;
	}clear(s);
	s[0]=max(a[0],b[0])+1;
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]+b[i];
		if(s[i]>=MOD) s[i]-=MOD,++s[i+1];//进位
	}if(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mnu(long long a[],long long b[])
{
	if(f1^f2){
		if(f1) f1^=1,f^=1,pls(a,b);//a-b=-(-a+b)
		if(f2) f2^=1,pls(a,b);//a-b=a+(-b)
		return;
	}if(f1&f2){
		f1=f2=0,mnu(b,a);//a-b=-b-(-a)
		f1=f2=1;return;
	}if(cmp(a,b)==-1) swap(a,b),f^=1;//绝对值相减，符号与绝对值大的数符号相同
	clear(s);
	s[0]=max(a[0],b[0]);
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]-b[i];
		if(s[i]<0) s[i]+=MOD,--s[i+1];//借位
	}while(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mul(long long a[],long long b[])//模拟竖式乘法
{
	if(f1^f2) f^=1;
	clear(s);
	s[0]=a[0]+b[0];
	for(int i=1;i<=a[0];++i){
		for(int j=1;j<=b[0];++j){
			s[i+j-1]+=a[i]*b[j];
			if(s[i+j-1]>=MOD) s[i+j]+=s[i+j-1]/MOD,s[i+j-1]%=MOD;//进位
		}
	}if(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void div(long long a[],long long b[])
{
	if(f1^f2) f^=1;
	clear(cp),cp[1]=1;clear(lt);
	while(cmp(a,b)!=-1) ly(b),ly(cp);//将除数倍增到不小于被除数，确定商二进制最高位
	while(cp[0]>1||cp[1]){
		if(cmp(a,b)!=-1){
			mnu(a,b),cpy(a,s);//a-=b
			pls(lt,cp),cpy(lt,s);//lt+=cp
		}ry(b),ry(cp);//b>>=1,cp>>=1
	}cpy(s,lt),cpy(lt,a);//s=lt,lt=a，此时，s是商，lt是余数
	return;
}

int main(){
	init();
	clear(s);
	pls(a,b);
	write(s);
	mnu(a,b);
	write(s);
	mul(a,b);
	write(s);
	div(a,b);
	write(s);
	write(lt);
	return 0;
}