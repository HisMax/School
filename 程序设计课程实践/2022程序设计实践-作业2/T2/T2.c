//可能会存在C和Java版本的提交 Mozi
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define MAXN 2023 //最多报数2022轮
#define re register //循环变量放入寄存器
struct Num{
    int v;//节点键值
    struct Num *next;//指向下一个节点的指针
};
struct Num *head[MAXN];//头节点数组

struct Num* Opt(int opt){//opt表示选择哪个链表
    if(opt>=1&&opt<=MAXN)return head[opt-1];
    return head[0];
}
struct Num* End(int opt){//获取尾节点
    struct Num *p = Opt(opt);
    while(p->next!=NULL){
        if(p->next==Opt(opt))return p;
        p = p->next;
    }
    return p;
}
void InsertIn(struct Num *p,int v){//插入指定节点后 p指定节点，v为值
    struct Num *new = (struct Num*)malloc(sizeof(struct Num));//申请内存空间
    new->v = v;// 赋值
    new->next = p->next; // 节点结构变更
    p->next = new;// 节点结构变更
}
void InsertEnd(int opt,int v){//插入指定链表的尾节点后 opt指定链表，v为值
    struct Num *new = (struct Num*)malloc(sizeof(struct Num));//申请内存空间
    struct Num *p = End(opt);
    new->v = v;// 赋值
    new->next = p->next; // 节点结构变更
    p->next = new;// 节点结构变更
}
void Free(){//释放内存
    for(re int i = 1;i <= MAXN;++i){
        struct Num *p = Opt(i);
        struct Num *fr = p;// 用来释放的指针
        while(p->next!=NULL){
            fr = p;
            p=p->next;
            free(fr);
        }
        free(p);// 释放空表头节点或者是非空表的尾节点
    }
    return;
}
void Re(){// 初始化并申请空间
    for(re int i = 0;i < MAXN;++i){
        head[i]= (struct Num *)malloc(sizeof(struct Num));
        head[i]->next = NULL;
        head[i]->v = -1;//头节点置-1
    }
    return;
}
void Set(int opt,int n){
    struct Num *p = Opt(opt);
    for(re int i = 1;i <= n;++i){
        //InsertEnd(p,i); 低效写法 O(n^2)
        InsertIn(p,i);p = p->next;
    }
    return;
}
int main(void){
    int n,a[128],cnt = 0;// n个数 cnt次报数 分别为 a1 a2 ……
    struct Num *p = NULL,*q = NULL;// 工具人（指针（bushi

    scanf("%d",&n);
    while(scanf("%d",&a[++cnt])!=EOF);//读入
    cnt--;//细节处理

    Re();
    Set(1,n);//初始化列表

    for(re int i = 1;i <= cnt;++i){//每次报数
        int x = 1,sum = 0;
        p = Opt(i);q = Opt(i+1);//当前表与报数后的表
        End(i)->next = p;//首尾相接

        while(sum!=n){//开始报数
            //printf("#### %d %d %d\n",sum,x,p->v); //进行一个调试
            if(p->v==-1){p = p->next;continue;}//跳过头节点
            if(p->v==-2){p = p->next;continue;}//跳过已出列节点
            
            if(x%a[i]==0){
                InsertIn(q,p->v);
                p->v = -2;
                q = q->next;
                sum++;
            }
            x++;
            p = p->next;
        }

        End(i)->next = NULL; //解开首尾，便于Free()
    }

    //输出最后的列表
    p = Opt(cnt+1);
    while(p->next!=NULL){
        if(p->v!=-1)printf("%4d",p->v);
        p = p->next;
    }
    printf("%4d",p->v);
    //释放内存空间
    Free();
    return 0;
}