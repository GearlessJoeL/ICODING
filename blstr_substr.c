#include "dsstring.h" // 请不要删除，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 4    // 可由用户定义的块大小
#define BLS_BLANK '#'   // 用于空白处的补齐字符

typedef struct _block {
    char ch[BLOCK_SIZE];    //块的数据域
    struct _block *next;    //块的指针域
} Block;

typedef struct {
    Block *head;        // 串的头指针
    Block *tail;        // 串的尾指针
    int len;            // 串的当前长度
} BLString;

//字符串初始化函数：
void blstr_init(BLString *T) {
    T->len = 0;
    T->head = NULL;
    T->tail = NULL;
}


bool blstr_substr(BLString src, int pos, int len, BLString* sub)
{
    int i = 0, j = 0, times;
    Block* p = src.head;
    Block* cur = (Block*)malloc(sizeof(Block));
    blstr_init(sub);
    
    if (pos >= src.len || len <= 0 || pos < 0)
        return 0;
        
    sub->head = cur;

    if (pos + len > src.len) {
        times = src.len - pos;
    } else {
        times = len;
    }
    
    while (i < pos / BLOCK_SIZE) {
        p = p->next;
        i++;
    }
    i = pos % BLOCK_SIZE;
    for (int k = 0; k < times; k++, sub->len++) {
        cur->ch[j] = p->ch[i];
        i++;
        j++;
        if (i >= BLOCK_SIZE) {
            i = 0;
            p = p->next;
        }
        if (j >= BLOCK_SIZE && k != times - 1) {
            j = 0;
            cur->next = (Block*)malloc(sizeof(Block));
            cur = cur->next;
        }
    }
    
    while (j < BLOCK_SIZE && j) {
        cur->ch[j] = '#';
        j++;
    }

    sub->tail = cur;
	
    return 1;
}