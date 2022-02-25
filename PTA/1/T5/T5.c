#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
struct Num{
    int v;//用来存放具体的值
    struct Num *next;//下一个节点
};
struct Num *head;//头节点
void Insert(struct Num *p,int v){//插入节点
    struct Num *new = (struct Num*)malloc(sizeof(struct Num));
    new->v = v;
    new->next = p->next;
    p->next = new;//常规操作，插入一个节点。
}
int main(void){
    int m,d,cnt = 0;
    struct Num *p,*q,*fr;
    head = (struct Num*)malloc(sizeof(struct Num));
    head->v = 1;head->next = NULL;//这里要注意
    p = head;
    scanf("%d%d",&m,&d);
    for(int i = 2;i <= m;++i,p = p->next)Insert(p,i);
    p->next = head;//将首尾连起来就好
    p = head,q = head;
    while(p->next!=NULL){
        cnt++;
        if(cnt%d==0){//判断是否剔除该节点
            printf("%4d",p->v);
            q->next = p->next;
            fr = p;q = p;
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