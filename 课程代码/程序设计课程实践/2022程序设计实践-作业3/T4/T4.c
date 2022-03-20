#include <stdio.h>
void hanoi(int n,char x,char y,char z){
    if(n==1)
        printf("%c->%c\n",x,z);
    else{
        hanoi(n-1,x,z,y);
        printf("%c->%c\n",x,z);//基础汉诺塔
        hanoi(n-1,y,x,z);
    }
}
int main(void){
    int n;
    scanf("%d",&n);
    hanoi(n,'A','B','C');
    return 0;
}
