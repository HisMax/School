//运用线性回归法解决房价预测问题，运用最大最小标准化进行特征数据归一化，运用数学公式(XT)Y=(XT)XW结合高斯亚当消元法求解线性回归方程
//的系数矩阵w【此处(XT)为特征数据X矩阵的转置，（XT）X为此方程的系数矩阵，（XT）Y为此方程的常数矩阵，以下如此称呼】）
#include<stdio.h>
#include<stdlib.h>
#include<cstring>
#include<math.h>
#define bool int
#define true 1
#define false 0
#define FeatureMax 20						//宏定义特征最多数
#define DataMax 600							//宏定义数据最大个数，
double max[FeatureMax];					    //定义最大，最小数矩阵，用于数据归一化处理
double min[FeatureMax];
struct node {						//用于求解相关系数
	double sumx[FeatureMax];				//sum求和
	double sumxy[FeatureMax];
	double sumy;
	double ex[FeatureMax];					//e求均值
	double ey;
	double Variancex[FeatureMax];			//方差
	double Variancey;
	double CorrelationCoefficient[FeatureMax];
};
struct node CC;
struct answer {
	char* name[FeatureMax];
	double coefficient[FeatureMax];
};											//存储线性方程答案
struct answer result1, result2;
double Data[DataMax][FeatureMax];			//存储数据
double data[DataMax][FeatureMax];			//用于计算线性方程
double radio[FeatureMax][FeatureMax];		//系数矩阵
double constant[FeatureMax];				//常数矩阵
int DataNum;
int FeatureNum;
int n;
int p;
bool Init() {
	int i;
	for (i = 0; i < 20; ++i) {
		result1.name[i] = (char*)malloc(sizeof(char) * 10);
		result2.name[i] = (char*)malloc(sizeof(char) * 10);
	}
	char fname[256];
	printf("请输入数据存放的文件名（housing.txt）:\n");
	scanf("%s", fname);
	printf("\n请输入数据个数(506):\n");
	scanf("%d", &DataNum);
	printf("\n请输入特征个数(13):\n");
	scanf("%d", &FeatureNum);
	n = FeatureNum + 1;
	FILE* fp;
	fp = fopen(fname, "rb");
	if (fp == NULL) {
		printf("\n未能打开文件\n");
		return false;
	}
	*result1.name[0] = '\0';
	*result2.name[0] = '\0';
	for (i = 1; i < n+1; ++i) {
		fscanf(fp, "%s", result1.name[i]);
	}
	int j;
	memset(max, 0, sizeof(max));
	memset(min, 0x7f7f7f7f, sizeof(min));
	for (i = 0; i < DataNum; ++i) {
    		//将数据放入矩阵
		Data[i][0] = 1;					//矩阵第一列赋值为1
		for (j = 1; j < n+1; ++j) {
			fscanf(fp, "%lf",&Data[i][j]);
			if (Data[i][j] > max[j])max[j] = Data[i][j];
			if (Data[i][j] < min[j])min[j] = Data[i][j];
        }
	}
	for (i = 0; i < DataNum; ++i)
		for (j = 1; j < n ; ++j)
			Data[i][j] /= (max[j] - min[j]);
	return 0;
}
void sortCC() {
	int i, j;
	CC.sumy = 0;
	for (i = 0; i < DataNum; ++i) {
		CC.sumy += Data[i][n];
	}
	for (i = 1; i <n; ++i) {
    
		CC.sumx[i] = 0;
		CC.sumxy[i] = 0;
		for (j = 0; j < DataNum; ++j) {
    
			CC.sumx[i] += Data[j][i];
			CC.sumxy[i] += Data[j][i] * Data[j][n];
		}
	}
	CC.ey = CC.sumy / DataNum;
	double t=0;
	for (i = 0; i < DataNum; ++i) {
    
		t += pow(CC.ey - Data[i][n],2);
	}
	CC.Variancey = t / DataNum;
	for (i = 1; i < n; ++i) {
    
		CC.ex[i] = CC.sumx[i] / DataNum;
		t = 0;
		for (j = 0; j < DataNum; ++j) {
    
			t += pow(CC.ex[i] - Data[j][i],2);
		}
		CC.Variancex[i] = t/DataNum;
	}
	printf("\n相关系数:\n");
	for (i = 1; i < n; ++i) {
		CC.CorrelationCoefficient[i] = (CC.sumxy[i] / DataNum - CC.ex[i] * CC.ey)/sqrt(CC.Variancex[i]*CC.Variancey);
		printf("%s\t%lf\n", result1.name[i], CC.CorrelationCoefficient[i]);
	}
	double temp[FeatureMax];
	for (i = 1; i < n; ++i) temp[i] = fabs(CC.CorrelationCoefficient[i]);
	printf("\n请输入你要选择最相关维度的个数(1<=p<=13);\n");
	scanf("%d", &p);
	int k;
	i = 1;
	int test = 1;
	while (i <= p) {
		int t = 1;
		double max = 0;
		for (j = 1; j < n; ++j) {
			if (temp[j] > max) {
				max = temp[j];
				t = j;
			}
		}
		temp[t] = 0;
		strcpy(result2.name[i],result1.name[t]);
		for (k = 0; k < DataNum; ++k) {
			data[k][i] = Data[k][t];
		}
		i++;
	}
	p++;
	for (i = 0; i < DataNum; ++i) {
		data[i][0] = 1;
		data[i][p] = Data[i][FeatureNum + 1];
	}
}
void LineReg() {
    							//根据输入的维度个数求解线性回归方程
	int i, j, k;
	for (i = 0; i < p; ++i) {
		constant[i] = 0;
		for (j = 0; j < DataNum; ++j) {
			constant[i] += data[j][i] * data[j][p];
		}
	}
	for (i = 0; i < p; ++i) {
		for (j = 0; j < p; ++j) {
			radio[i][j] = 0;
			for (k = 0; k < DataNum; ++k) {
				radio[i][j] += data[k][i] * data[k][j];
			}
		}
	}
	for (i = 0; i < p; ++i)radio[i][p] = constant[i];
	for (i = 0; i < p; ++i) {
		double m = radio[0][0];
		int x = 0;
		int y = 0;
		for (j = 0; j < p; ++j) {
			for (k = 0; k < p; ++k) {
				if (radio[j][k] > m) {
					m = radio[j][k];
					x = j;
					y = k;
				}
			}
		}
		if (x != y) {
			double temp;
			for (j = 0; j < p + 1; ++j) {
    
				temp = radio[x][j];
				radio[x][j] = radio[y][j];
				radio[y][j] = temp;
			}
		}
		for (j = 0; j < p + 1; ++j) {
    
			radio[y][j] /= m;
		}
		for (j = 0; j < p; ++j) {
    
			if (j == y)continue;
			double t = radio[j][y];
			for (k = 0; k < p + 1; ++k) {
    
				radio[j][k] -= radio[y][k] * t;
			}
		}
	}
	printf("\n线性回归方程系数:\n");
	for (i = 0; i <p; ++i) {
		result2.coefficient[i] = radio[i][p];
		printf("%s\t%lf\n", result2.name[i], result2.coefficient[i]);
	}
	printf("\n线性回归方程:\n");
	printf("MEDV = %lf",result2.coefficient[0]);
	for (i = 1; i < p; ++i) {
    
		printf(" + (%lf) * %s ", result2.coefficient[i], result2.name[i]);
	}
	printf("\n");
}
int main() {
    						//主函数
	if (Init() == false) {
    
		return 0;
	}
	sortCC();
	LineReg();
	return 0;
}