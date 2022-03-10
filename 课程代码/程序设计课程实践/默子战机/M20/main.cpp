#include "m20.h"
//头文件里有引用其他头文件和声明函数
int main(void) {
	initgraph(Map_Width,Map_High);
	BeginBatchDraw();
	Start();
	closegraph();
	return 0;
}