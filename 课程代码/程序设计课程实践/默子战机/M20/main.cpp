#include "m20.h"
//ͷ�ļ�������������ͷ�ļ�����������
int main(void) {
	initgraph(Map_Width,Map_High);
	BeginBatchDraw();
	Start();
	closegraph();
	return 0;
}