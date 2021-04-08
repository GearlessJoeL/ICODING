#include "tsmatrix.h"
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100          //假设非零元个数的最大值为100
typedef struct {
    int i,j;									//非零元的行下标和列下标，i 和 j 从 1 开始计数，与数学中矩阵元素的编号一致
    ElemType e;						//非零元的值
}Triple;

typedef struct {
    Triple data[MAXSIZE];			// 非零元三元组表
    int    m, n, len;							// 矩阵的行数、列数和非零元个数
}TSMatrix;

//**********************************************************************************************//
//**********************************************************************************************//
//********************不会吧不会吧，不会真的有人不全部遍历存到新数组里面吧？********************//
//**********************************************************************************************//
//**********************************************************************************************//

bool add_matrix(const TSMatrix* pM, const TSMatrix* pN, TSMatrix* pQ)
{
    if (pM->m != pN->m || pM->n != pN->n)
        return 0;

    int m[MAXSIZE][MAXSIZE], n[MAXSIZE][MAXSIZE], q[MAXSIZE][MAXSIZE];
    for (int i = 0; i < MAXSIZE; i++) {
        for (int j = 0; j < MAXSIZE; j++) {
            m[i][j] = 0;
            n[i][j] = 0;
            q[i][j] = 0;
        }
    }

    for (int i = 0; i < pM->len; i++) {
        m[pM->data[i].i][pM->data[i].j] = pM->data[i].e;
    }
    for (int i = 0; i < pN->len; i++) {
        n[pN->data[i].i][pN->data[i].j] = pN->data[i].e;
    }
    int cnt = 0;
    for (int i = 1; i <= pM->m; i++) {
        for (int j = 1; j <= pN->n; j++) {
            q[i][j] = m[i][j] + n[i][j];
            if (q[i][j] != 0) {
                pQ->data[cnt].e = q[i][j];
                pQ->data[cnt].i = i;
                pQ->data[cnt].j = j;
                cnt++;
            }
        }
    }
    pQ->len = cnt;
    return 1;
}