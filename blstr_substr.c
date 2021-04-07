#include "dsstring.h" // 请不要删除，否则检查不通过
#include <stdio.h>
#include <stdlib.h>

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