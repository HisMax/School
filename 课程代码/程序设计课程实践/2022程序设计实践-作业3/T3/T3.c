//人生苦短 可惜Python更短 Mozi
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#define Int struct BigNumber
#define Num struct num

/***************************************************************************
 *   默子将代码进行了一个缩写
 *   Int 大整数类型(是一个结构体，有三个属性：数字位数，头结点，尾结点)
 *   *p 一般都是工具人
 ***************************************************************************/

/**************************************************************************
 *   声明函数 来自 Ex1.4样例程序 做了些许修改与补充注释
 **************************************************************************/

//功能                  返回值      参数                        样例程序原名

Int Read ();
//读入数字               Int类型    无参数                       InputUBN()

void Puts (Int a);
//输出数字               无返回值    需要输出的数字a              PrintUBN()

Int _Add (Int *a, Int *b);
//内部加法                   Int类型    两个加数a和b               AddUBN()

void Free (Int *a);
//内存释放              无返回值     被释放的数a                 DestoryUBN()

Num *New ();
//申请新Num结点      Num结点    无参数                          _NewNode()

void Build (Int *a);
//初始化一个Int          无返回值    a被初始化                  _InitUBN()

void AddEnd (Int *a, int v);
//读入时末尾新添数字      无返回值   在a的末尾新添v                _AppendDigit()

void AddFront (Int *a, int v);
//计算时的进位           无返回值    在a的前面进一位v              _AppendFrontDigit()

void NoZero (Int *a);
//去除前导零             无返回值    删除a前面多余的零             _Normalize()

/**************************************************************************
 *   声明函数 来自 默子 题目要求的函数
 **************************************************************************/

Int _Minus(Int *a, Int *b);
//内部减法                   Int类型    a减去b
Int Minus(Int *a, Int *b);
//减法                      Int类型    a减去b
Int Add(Int *a, Int *b);
//加法                      Int类型    a加上b
Int Mul(Int *a,Int *b);
//乘法                      Int类型    a乘b
Int _Mul(Int *a, Int *b);
//内部乘法                  Int类型    a乘b
int Com(Int *a, Int *b);
//比较                   int类型    被比较的两数


Num{//每一位一个结点
    int v;//具体的值 (范围0-9) 大于等于10将进位
    Num *next, *pre;//指向前后Num结点
};

Int{
    int f;//正负
    int len; //位数，这里用长度length来表示
    Num *Head, *End; //头结点与尾结点
};
int Com(Int *a, Int *b){
    /*
    1 a<b
    2 a=b
    3 a>b
    很难不承认，这个Com很恶心
    */
    if(a->f>b->f)return 3;
    else if(a->f==b->f){
        if(a->f<0){
            if(a->len<b->len)return 3;
            else if(a->len==b->len){
                Num *p = a->Head->next;
                Num *q = b->Head->next;
                while(p != a->End){
                    if(p->v < q->v)return 3;
                    else return 1;
                }
                return 2;
            }
            else return 1;
        }
        else{
            if(a->len<b->len)return 1;
            else if(a->len==b->len){
                Num *p = a->Head->next;
                Num *q = b->Head->next;
                while(p != a->End){
                    if(p->v < q->v)return 1;
                    else return 3;
                }
                return 2;
            }
            else return 3;
        }
    }else return 1;
}
Int Read (){//读入数字
    Int ans;
    Build(&ans);//初始化一个Int
    char ch;//一位一位用字符的方式读入
    do{
        ch = getchar ();
        if(ch=='-')ans.f = -1;
    }while (ch < '0' || ch > '9');//排除非数字 比如负号
    while (ch >= '0' && ch <= '9'){
        AddEnd (&ans, ch - '0');//读一位添一位
        ch = getchar ();//继续读
    }
    NoZero(&ans);//去除前导零
    return ans;
}

Num *New (){
    Num *p;//工具人
    p = (Num *) malloc (sizeof (Num));//申请空间
    if (p == NULL){printf ("Error : out of memory\n");exit (-1);}//失败秒退
    return p;//成功返回
}
void Build (Int *a){//初始化一个Int
    Num *p = New ();          //申请新Num结点
    p->next  = p->pre  = NULL;//初始化该结点
    a->Head = a->End = p;     //Int首尾结点初始化
    a->len  = 0;              //初始为0位
    a->f    = 1;              //初始为正数
}
void AddEnd (Int *a, int v)
{
    if (a->len == 1 && a->End->v == 0){//原只有一个高位0
        a->End->v = v; //位数不变，数值赋值为v
        return;
    }
    Num *p = New ();   //申请新Num结点
    //如果理解困难，Google找张双向列表的图来理解
    p->v            = v;        //赋值
    p->next         = NULL;     //p结点是尾结点，所以置NULL
    p->pre          = a->End;   //p结点的pre是该数字的尾结点
    a->End->next    = p;        //该数字原来的尾结点将自己的next指向p结点
    a->End          = p;        //该数字的尾结点替换为p
    a->len          ++;         //位数++
}

void Puts (Int a){//输出数字
    assert (a.len > 0 && a.Head->next != NULL);//至少有1位数字
    Num *p = a.Head->next;
    if(a.f<0)printf("-");
    while (p){
        printf ("%d", p->v);
        p = p->next;
    }
}
Int _Add (Int *a, Int *b){//   高精度的奥义就是模拟手算 手算yyds
    Int ans, *p = &ans;//ans 存答案
    Build(&ans);
    int x = 0; //x是进位
    Num *p1, *p2;
    p1 = a->End; //从低位开始处理
    p2 = b->End;
    while (p1 != a->Head && p2 != b->Head){
        int v = p1->v + p2->v + x;
        x = v / 10;v %= 10;AddFront (p, v);//实现手算的进位操作
        p1 = p1->pre;p2 = p2->pre;
    }
    while (p1 != a->Head){
        int v = p1->v + x;
        x = v / 10;v %= 10;AddFront (p, v);//同理
        p1 = p1->pre;
    }
    while (p2 != b->Head){
        int v = p2->v + x;
        x = v / 10;v %= 10;AddFront (p, v);//同理
        p2 = p2->pre;
    }
    if (x != 0)AddFront (p, x);
    return ans;
}
Int _Minus(Int *a, Int *b){
    Int ans, *p = &ans;//ans 存答案
    Build(&ans);
    int x = 0; //x是借数
    Num *p1, *p2;
    p1 = a->End; //从低位开始处理
    p2 = b->End;
    //默子在这里使用了一个非常取巧的办法
    //对着Add复制粘贴就出来了Minus
    //手算时候这样主动借尾是比较傻的
    //不过写代码的时候就比较省地方
    while (p1 != a->Head && p2 != b->Head){
        int v = p1->v - p2->v + x + 10;//每次不管够不够都主动借一个10
        x = v / 10 - 1;//每次前一位自动失误1
        v %= 10;
        AddFront (p,v);
        p1 = p1->pre;p2 = p2->pre;
    }
    while (p1 != a->Head){
        int v = p1->v + x +10;
        x = v / 10 - 1;v %= 10;AddFront (p, v);//同理
        p1 = p1->pre;
    }
    while (p2 != b->Head){
        int v = p2->v + x +10;
        x = v / 10 - 1;v %= 10;AddFront (p, v);//同理
        p2 = p2->pre;
    }
    if (x != 0)AddFront (p, x);
    NoZero(&ans);
    return ans;
}
void AddFront (Int *a, int v){
    Num *p = New ();          //申请新结点
    p->v = v;                 //设置结点数值
    p->next = a->Head->next;  //修改双链表，添加在头结点后
    if (p->next != NULL)p->next->pre = p;

    p->pre = a->Head;
    a->Head->next = p;

    if (a->End == a->Head)a->End = p;
    ++a->len;           //修改位数
}
//无符号大数规范表示，去除高位多余0，至少含一位数字
void NoZero (Int *a){
    if (a->len == 0)AddEnd (a, 0);//特判一个0
    while (a->len > 1 && a->Head->next->v == 0){
        Num *p;
        p = a->Head->next; //待删除的结点
        a->Head->next = p->next; //正向链表中删除
        p->next->pre = a->Head; //反向链表中删除
        free (p);               //释放结点
        --a->len;               //调整位数
    }
}
void Free (Int *a){
    while (a->Head != NULL)  //清空后应该只剩一个头结点
    {
        Num *p =  a->Head;  //待删除结点
        a->Head = p->next;          //尾指针前移
        free (p);                       //释放结点
    }
}

Int Add(Int *a, Int *b){
    Int ans;
    int x = Com(a,b);
    switch(x){
        case 1:
            if(a->f<0){
                if(b->f<0){
                    ans = _Add(a,b);
                    ans.f = -1;
                    return ans;
                }
                else{
                    a->f = 1;
                    x = Com(a,b);
                    switch(x){
                        case 1:
                            ans = _Minus(b,a);
                            return ans;
                        case 2:
                            ans = _Minus(a,b);
                            return ans;
                        case 3:
                            ans = _Minus(a,b);
                            ans.f = -1;
                            return ans;
                    }
                }
            }
            else{
                ans = _Add(a,b);
                return ans;
            }
        case 2:
            if(a->f<0){
                ans = _Add(a,b);
                ans.f = -1;
                return ans;
            }
            else{
                ans = _Add(a,b);
                return ans;
            }
        case 3:
            if(a->f<0){
                ans = _Add(a,b);
                ans.f = -1;
                return ans;
            }
            else{
                if(b->f<0){
                    b->f = 1;
                    x = Com(a,b);
                    switch(x){
                        case 1:
                            ans = _Minus(b,a);
                            ans.f = -1;
                            return ans;
                        case 2:
                            ans = _Minus(a,b);
                            return ans;
                        case 3:
                            ans = _Minus(a,b);
                            return ans;
                    }
                }
                else{
                    ans = _Add(a,b);
                    return ans;
                }
            }
    }
}
Int Minus(Int *a, Int *b){
    Int ans;
    int x = Com(a,b);
    switch(x){
        case 1:
            if(a->f<0){
                if(b->f<0){
                    ans = _Minus(a,b);
                    ans.f = -1;
                    return ans;
                }
                else{
                    ans = _Add(a,b);
                    ans.f = -1;
                    return ans;
                }
            }
            else{
                if(b->f<0){
                    ans = _Add(a,b);
                    return ans;
                }
                else{
                    ans = _Minus(b,a);
                    ans.f = -1;
                    return ans;
                }
            }
        case 2:
            ans = _Minus(a,b);
            return ans;
        case 3:
            if(a->f<0){
                ans = _Minus(a,b);
                ans.f = -1;
                return ans;
            }
            else{
                if(b->f<0){
                    ans = _Add(a,b);
                    return ans;
                }
                else{
                    ans = _Minus(a,b);
                    return ans;
                }
            }
    }
}
Int _Mul(Int *a,Int *b){
    
}
Int Mul(Int *a,Int *b){
    Int ans;int f;
    if((a->f+b->f)%2!=0)f = -1;
    a->f=0;b->f=0;
    if(Com(a,b)==1)
        ans = _Mul(a,b);
    else
        ans = _Mul(b,a);
    
    return ans;
}
int main (){
    Int A, B, C, D, A1, B1;
    A = Read ();B = Read ();
    A1 = A;B1 = B;C = Add (&A, &B);D = Minus(&A1, &B1);
    Puts (C);printf("\n");Puts (D);
    Free (&A);
    Free (&B);
    Free (&C);
    Free (&D);
    return 0;
}