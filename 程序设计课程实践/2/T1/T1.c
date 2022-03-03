#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
struct Num{
    int v;
    struct Num *next;
};
struct Num *head_1,*head_2;
void Insert(struct Num *p,int v){
    struct Num *new = (struct Num*)malloc(sizeof(struct Num));
    new->v = v;
    new->next = p->next;
    p->next = new;
}

int main(void){
    int m,d,k,cnt = 0;
    struct Num *p,*q,*fr;
    head_1 = (struct Num*)malloc(sizeof(struct Num));
    head_2 = (struct Num*)malloc(sizeof(struct Num));
    head_1->v = 1;head_1->next = NULL;
    //初始化变量
    p = head_1;
    scanf("%d%d%d",&m,&d,&k);
    for(int i = 2;i <= m;++i,p = p->next)Insert(p,i);
    p->next = head_1;//将首尾连起来就好
    p = head_1,q = head_1;
    while(p->next!=NULL){
        cnt++;
        if(cnt%(d*k+1)-1==0){//将该节点插入第二个列表中
            printf("%4d",p->v);
            q->next = p->next;
            fr = p;
            q = p;
            p = p->next;
            free(fr);
            continue;
        }
        q = p;
        p = p->next;
        if(p==p->next)break;//如果已经自己指向自己了，那么说明已经结束了
    }
    printf("%4d",p->v);
    free(p);
    return 0;
}