﻿// smMatrix.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#define MAX 100
/*
  用典型的多重链表（十字链表）存储稀疏矩阵
  设计要点：
		1   用数组存储head，数组中的第一个元素
			col:矩阵的列数，row：矩阵的行数，value:非0元素个数
		2   行和列都是循环链表
		3   实现了三个方法：初始化，插入，打印

*/

/*稀疏矩阵
   18  0   0
A= 0   27  0
   0   0   0
   23  -1  0
*/

//定义结构
typedef struct _SparseMatrix {
	struct _SparseMatrix* Down;
	struct _SparseMatrix* Right;
	union {
		struct {
			int row;
			int col;
			int value;
		};
		struct _SparseMatrix* Next;
	}URegion;
}SparseMatrix;

//初始化一个稀疏矩阵 
void smInitialize(SparseMatrix* smArray[], int row, int col);
//插入一个非0的元素 ，已有则替换  
void smInsertTerm(SparseMatrix* mySM[], int row, int col, int value);
//给矩阵,循环打印非0元素 
void smPrint(SparseMatrix* mySM);
//查找某一位置是否是非零元素，是返回1，否返回0 
int smFindTerm(SparseMatrix* mySM[], int row, int col);
//删除某一位置的非零元素，删除返回1，否则返回0
int smDeleteTerm(SparseMatrix* mySM[], int row, int col);

int main(int argc, char* argv[])
{
	SparseMatrix* term00[MAX] = { NULL };
	smInitialize(term00, 4, 3);
	smInsertTerm(term00, 1, 1, 18);
	smInsertTerm(term00, 2, 2, 27);
	smInsertTerm(term00, 4, 3, 24);
	smInsertTerm(term00, 4, 1, 23);
	smInsertTerm(term00, 4, 2, -1);
	smPrint(term00[0]);
	return 0;
}
void smInitialize(SparseMatrix* smArray[], int row, int col)
{
	SparseMatrix* term00 = (SparseMatrix*)malloc(sizeof(SparseMatrix));
	term00->URegion.row = row;
	term00->URegion.col = col;
	term00->URegion.value = 0;
	term00->Right = term00;
	term00->Right = NULL;
	smArray[0] = term00;
	//初始化head结构 
	int headNum = row > col ? row : col;
	//	if(headNum>MAX)
	//	   throw;
	for (int i = 1; i <= headNum; i++) {
		smArray[i] = (SparseMatrix*)malloc(sizeof(SparseMatrix));;
		if (i == 1) {
			term00->Right = smArray[i];
		}
		else {
			smArray[i - 1]->URegion.Next = smArray[i];
		}
		smArray[i]->Down = smArray[i];//每列是循环列表 
		smArray[i]->Right = smArray[i];//每行是循环列表 
	}

	smArray[headNum]->URegion.Next = smArray[0];//head与term00形成循环链表 
}
void smInsertTerm(SparseMatrix* mySM[], int row, int col, int value)
{
	//	if(mySM[0]->URegion.row<row || mySM[0]->URegion.col<col)
	//	    throw ;
		//非零节点行，列，值 
	int repeatFlag = 0;
	SparseMatrix* term = (SparseMatrix*)malloc(sizeof(SparseMatrix));
	term->URegion.col = col;
	term->URegion.row = row;
	term->URegion.value = value;
	//非零节点链接到链表中 
	SparseMatrix* rowP = mySM[row]->Right;
	SparseMatrix* rowLastP = mySM[row];
	SparseMatrix* colP = mySM[col]->Down;
	SparseMatrix* colLastP = mySM[col];
	while (rowP != mySM[row] && rowP->URegion.col <= col) {
		rowLastP = rowP;
		if (rowP->URegion.col != col) {
			rowP = rowP->Right;
		}
		else {
			repeatFlag = 1;
		}
	}

	//如果节点已有， 指向已有的下一个
	if (repeatFlag) {
		term->Right = rowP->Right;
	}
	else {
		term->Right = rowP;
	}
	rowLastP->Right = term;


	while (colP != mySM[col] && colP->URegion.row < row) {
		colLastP = colP;
		colP = colP->Down;
	}
	//如果节点已有， 指向已有的下一个 
	if (repeatFlag) {
		term->Down = colP->Down;
	}
	else {
		term->Down = colP;
	}
	colLastP->Down = term;
	//删除重复的 
	if (repeatFlag)
	{
		free(colP);
	}

	mySM[0]->URegion.value += 1;
}

void smPrint(SparseMatrix* mySM) {
	SparseMatrix* head;
	if (mySM) {
		head = mySM->Right;
	}
	else {
		return;
	}
	SparseMatrix* colP = head->Right;
	SparseMatrix* headP = head;

	while (headP != mySM) {
		while (colP != headP) {
			printf("%d,%d,%d||%d\n", colP->URegion.value, colP->URegion.row, colP->URegion.col, mySM->URegion.value);
			colP = colP->Right;
		}
		headP = headP->URegion.Next;
		colP = headP->Right;
	}
}


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
