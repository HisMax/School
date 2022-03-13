#include<stdio.h>
int main(void){
    int hh,mm,ss;
    scanf("%d:%d:%d",&hh,&mm,&ss);
    hh = (hh+(mm=(mm+(++ss)/60))/60);
    return printf("%02d:%02d:%02d",hh%24,mm%60,ss%60);
}