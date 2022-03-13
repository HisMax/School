#include <stdio.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))
#define max(a,b) (((a) > (b)) ? (a) : (b))
//题目要求二分+递归
//
int num[20480];
int cnt = 0;
int maxn(int l,int r){//求最大值，用l和r
    if(l==r)return num[l];//最小单位
    int mid = (l+r)>>1;
    return  max(maxn(l,mid),maxn(mid+1,r));

}
int minn(int l,int r){
    if(l==r)return num[l];//最小单位
    int mid = (l+r)>>1;
    return  min(minn(l,mid),minn(mid+1,r));
}
int main(void){
    while(scanf("%d",&num[cnt++])!=EOF);
    printf("%d %d",minn(0,cnt-2),maxn(0,cnt-2));
    return 0;
}