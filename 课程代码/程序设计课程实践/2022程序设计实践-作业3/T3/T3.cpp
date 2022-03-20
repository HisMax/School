#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
#define ll long long
const int MAXN=1e4;
const int siz=7;
const ll MOD=1e7;
char ch1[MAXN],ch2[MAXN];
int f1,f2,f,f3,f4;
ll n;
ll a[MAXN],b[MAXN],s[MAXN];
ll cp[MAXN],lt[MAXN],wsd[MAXN];

void write(ll ub[]);
void clear(ll ub[]);
void ry(ll ub[]);
void ly(ll ub[]);
void cpy(ll num1[],ll num2[]);
int cmp(ll num1[],ll num2[]);
void pls(ll a[],ll b[]);
void mnu(ll a[],ll b[]);
void mul(ll a[],ll b[]);
void write(ll ub[]){
	if(f)putchar('-'),f=0;
	printf("%lld",ub[ub[0]]);
	for(int i=ub[0]-1;i;--i)
		printf("%08lld",ub[i]);
	puts("");
}

void clear(ll ub[]){
	for(int i=ub[0];i;--i) ub[i]=0;
	ub[0]=1;
}

void ry(ll ub[]){
	for(int i=ub[0];i;--i){
		if((ub[i]&1)&&i>1) ub[i-1]+=MOD;//将1借到下一位
		ub[i]>>=1;
	}if(!ub[ub[0]]&&ub[0]>1) --ub[0];
}

void ly(ll ub[]){
	++ub[0];
	for(int i=1;i<=ub[0];++i){
		ub[i]<<=1;
		if(ub[i-1]>=MOD) ub[i-1]-=MOD,++ub[i];//进位，注意后效性
	}if(!ub[ub[0]]&&ub[0]>1) --ub[0];
	return;
}

void cpy(ll num1[],ll num2[]){
	for(int i=num1[0];i>num2[0];--i) num1[i]=0;
	for(int i=0;i<=num2[0];++i) num1[i]=num2[i];
}

int cmp(ll num1[],ll num2[]){
	if(num1[0]>num2[0]) return 1;
	if(num1[0]<num2[0]) return -1;
	for(int i=num1[0];i;--i){
		if(num1[i]>num2[i]) return 1;
		if(num1[i]<num2[i]) return -1;
	}return 0;
}

void init(){
	scanf("%s%s",ch1,ch2);
	if(ch1[0]=='-')ch1[0]='0',f1=1,f3=1;
	if(ch2[0]=='-')ch2[0]='0',f2=1,f4=1;
	int l1=strlen(ch1),l2=strlen(ch2);
	for(int i=l1-1;i>=0;i-=siz){
		ll pw=1;++a[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			a[a[0]]+=(ch1[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}for(int i=l2-1;i>=0;i-=siz){
		ll pw=1;++b[0];
		for(int j=i;j>i-siz&&j>=0;--j){
			b[b[0]]+=(ch2[j]^48)*pw;
			pw=(pw<<3)+(pw<<1);
		}
	}return;
}

void pls(ll a[],ll b[]){
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

void mnu(ll a[],ll b[]){
	if(f1^f2){
		if(f1) f1^=1,f^=1,pls(a,b);
		if(f2) f2^=1,pls(a,b);
		return;
	}if(f1&f2){
		f1=f2=0,mnu(b,a);
		f1=f2=1;return;
	}if(cmp(a,b)==-1) swap(a,b),f^=1;
	clear(s);
	s[0]=max(a[0],b[0]);
	for(int i=1;i<=s[0];++i){
		s[i]+=a[i]-b[i];
		if(s[i]<0) s[i]+=MOD,--s[i+1];
	}while(!s[s[0]]&&s[0]>1) --s[0];
	return;
}

void mul(ll a[],ll b[]){
	f1 = f3;f2 = f4;
	if(f1^f2)f^=1;
	clear(s);
	s[0]=a[0]+b[0];
	for(int i=1;i<=a[0];++i){
		for(int j=1;j<=b[0];++j){
			s[i+j-1]+=a[i]*b[j];
			if(s[i+j-1]>=MOD) s[i+j]+=s[i+j-1]/MOD,s[i+j-1]%=MOD;
		}
	}if(!s[s[0]]&&s[0]>1) --s[0];
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
	return 0;
}