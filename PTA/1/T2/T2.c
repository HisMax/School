#include<stdio.h>
#include <stdlib.h>
#include <stddef.h>
struct Num{
    int v;//用来存放具体的值
    struct Num *next;//下一个节点
};
struct Num *head_1,*head_2;
void Insert(struct Num *p,int v){//插入节点
    struct Num *new = (struct Num*)malloc(sizeof(struct Num));
    new->v = v;
    new->next = p->next;
    p->next = new;//常规操作，插入一个节点。
}
struct Num* Opt(int opt){//opt表示选择哪个链表，对于这道题，完全可以直接写在一起，还可以省一个参数。
    switch (opt){
        case 1:return head_1;
        case 2:return head_2;
        default:printf("Error List");
    }
}
void PrintNum(int opt,int flag){
    struct Num *p = Opt(opt)->next;
    while(p!=NULL){//遍历列表
        if(p->next!=NULL)printf("%d->",p->v);
        else printf("%d",p->v);
        struct Num *temp = p;
        p = p->next;
        if(flag)free(temp);//内存释放要这样
    }
    printf("\n");
    return;
}
void Sort(int v,int opt){//遍历链表，寻找比v大的第一个节点,然后插入
    struct Num *p = Opt(opt);
    while(p->next!=NULL){
        if(v<(p->next)->v){
            Insert(p,v);
            return;
        }
        p = p->next;
    }
    Insert(p,v);//尾节点特殊待遇
}

int main(void){
    int x = 0;
    head_1 = (struct Num*)malloc(sizeof(struct Num));
    head_2 = (struct Num*)malloc(sizeof(struct Num));//申请内存
    head_1->next = NULL;head_2->next = NULL;
    while(scanf("%d",&x)!=EOF){
        if(x>0)Sort(x,1);
        else Sort(x,2);
    }
    PrintNum(1,0);
    PrintNum(2,0);
    struct Num *p = head_2;
    while(p->next!=NULL)p = p->next;
    p->next = head_1->next;//这里直接跳过head_1这个节点，然后把两个表拼接起来
    PrintNum(2,1);
    free(head_1);
    free(head_2);
    return 0;
}