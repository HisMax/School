#include "m20.h"
int main(void) {
	initgraph(Map_Width,Map_High);
	BeginBatchDraw();
	Start();
	closegraph();
	return 0;
}