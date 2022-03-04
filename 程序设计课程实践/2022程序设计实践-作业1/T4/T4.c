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
void Sort(  int v,int opt){//遍历链表，寻找比v大的第一个节点,然后插入
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
void Re(int opt){
    struct Num *p = Opt(opt)->next;
    struct Num *a = p,*b = p->next,*c = NULL;//辅助变量
    a->next = NULL;
    while(b!=NULL){
        c = b->next;
        b->next = a;
        a = b;
        b = c;//就是进行了一堆交换，画个图可以更好的理解
    }
    Opt(opt)->next = a;
}
void split(void){
    struct Num *p = head_1->next;
    struct Num *temp = head_2,*fr,*q = head_1,*g;
    while(p!=NULL&&p->next!=NULL){
        if(p->v%2==0){
            while(p->v%2==0){
                Insert(temp,p->v);
                temp = temp->next;
                fr = p;
                if(p->next!=NULL){
                    p = p->next;g = p;
                    free(fr);
                }else{
                    g = NULL;
                    break;
                }
            }
            q->next = g;
        }
        q = p;
        p = p->next;
    }
}
int main(void){
    int x = 0;
    head_1 = (struct Num*)malloc(sizeof(struct Num));head_1->next = NULL;
    head_2 = (struct Num*)malloc(sizeof(struct Num));head_2->next = NULL;
    //反正会用到俩个表，直接一块
    while(scanf("%d",&x)!=EOF)Sort(x,1);//读入数字并排序
    PrintNum(1,0);//进行一个输出
    split();
    PrintNum(1,1);
    PrintNum(2,1);
    free(head_1);
    free(head_2);
    return 0;
}