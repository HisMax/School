#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#define MAXN 2048
struct stack{//顺序栈
    int v[MAXN];
    int top;
};
struct node{
    int v;
    struct node *next;
};
struct queue{//链式队列
    struct node *front;//队头
    struct node *reer;//队尾
};
int sempty(struct stack *s){//判断栈是否为空
    return s->top==0;
}
int sfull(struct stack *s){//判断栈是否满了
    return s->top==MAXN-1;
}
void spush(struct stack *s,int vi){//压入栈
    if(sfull(s))exit(-1);
    s->v[++s->top]=vi;
}
int spop(struct stack *s){//弹出栈
    if(s->top==0)
        return -0x80000000;
    return s->v[s->top--];
}
struct node *qnew(int v){//新建一个node节点
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->v = v;
    p->next = NULL;
    return p;
}
void qbuild(struct queue *q){//初始化队列
    q->front = NULL;
    q->reer = NULL;
}
void qpush(struct queue *q,int v){//压入队尾
    struct node *p = qnew(v);
    if(q->front==NULL)
        q->front=q->reer=p;//队列为空的情况
    else{
        q->reer->next = p;
        q->reer = p;
    }
    
}
int qempty(struct queue *q){//判断队列是否为空
    return q->front == NULL;
}
int qpop(struct queue *q){//弹出队头
    if(qempty(q))return 0;
    struct node *p = q->front->next;
    int x = q->front->v;
    free(q->front);//释放内存
    q->front = p;
    return x;
}



int main(void){
    int x;
    struct stack *s = (struct stack*)malloc(sizeof(struct stack));//栈
    s->top = 0;
    struct queue *q = (struct queue*)malloc(sizeof(struct queue));//队列
    qbuild(q);
    while(scanf("%d",&x)!=EOF){
        if(x>0)spush(s,x);
        else qpush(q,x);
    }
    while(!sempty(s))printf("%5d",spop(s));
    printf("\n");
    while(!qempty(q))printf("%5d",qpop(q));
    printf("\n");//当栈和队列均为空时
    free(s);//释放内存
    return 0;
}