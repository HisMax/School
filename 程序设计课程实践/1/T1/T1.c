#include<stdio.h>
#include <stdlib.h>
#include <stddef.h>
struct Num{
    int v;//用来存放具体的值
    struct Num *next;//指向下一个节点的指针
};
struct Num *head_1,*head_2;//头节点

void Insert(struct Num *p,int v){//p为新节点的上一级节点
    struct Num *new = (struct Num*)malloc(sizeof(struct Num));//用malloc声明变量，方便之后释放内存
    new->v = v;//存储数据
    new->next = p->next;//让新节点的next指向原来p的next
    p->next = new;//再将p的next指向new节点
}
struct Num* Opt(int opt){//opt表示选择哪个链表
    switch (opt){
        case 1:return head_1;
        case 2:return head_2;
        default:printf("Error List");//假如传入了错误的参数
                return head_1;//默认返回head_1
    }
}
void PrintNum(int opt){
    struct Num *p = Opt(opt)->next;//获取头节点的next
    while(p!=NULL){//遍历列表
        if(p->next!=NULL)printf("%d->",p->v);//注意最后一个节点不需要输出 ->
        else printf("%d",p->v);
        struct Num *temp = p;//这里需要用一个临时变量存一下p
        p = p->next;
        free(temp);
        /*********************
         * 你肯定不想这样写
         * free(p);
         * p = p->next;
         * *******************/
    }
    printf("\n");//这里换行原本是在循环里面的，但是很恶心的发现，正数空表时，答案依然给输出换了一个行
    return;
}
void Sort(int v,int opt){//遍历链表，寻找比v大的第一个节点,然后插入
    struct Num *p = Opt(opt);//获取头节点
    while(p->next!=NULL){
        if(v<(p->next)->v){//当v小于p下一个节点的v时，在p后面新建节点
            Insert(p,v);return;
        }
        p = p->next;
    }
    Insert(p,v);//循环结束依然没有插进去，那就直接插到末尾。省一个AddEnd()
}

int main(void){
    int x = 0;
    head_1 = (struct Num*)malloc(sizeof(struct Num));
    head_2 = (struct Num*)malloc(sizeof(struct Num));//申请内存
    head_1->next = NULL;head_2->next = NULL;//注意头节点初始化，next要赋NULL
    while(scanf("%d",&x)!=EOF){
        if(x>0)Sort(x,1);
        else Sort(x,2);//很简单的一个判断
    }
    PrintNum(1);PrintNum(2);//输出答案
    free(head_1);free(head_2);//最后别忘了释放两个头节点
    return 0;
}
