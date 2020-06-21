/*------------------------------------------------
  作者: ZZY YBR WZR
  日期: 2020.6.12
  文件名: list.c
  版本: v1.8
  项目: 数据结构大作业--多关键字排序
  说明: 数据表操作相关
------------------------------------------------*/

#include "head_file.h"

void rand_list(LIST *pL)
{
    /**
     * 函数名：rand_list
     * 参数：指向LIST的指针pL
     * 功能：随机生成pL->entry[i].data[j]
     */
    
    int temp = 1;
    for (int i = 0; i < pL->len; i++)
    {
        for (int j = 0; j < MAXNUM; j++)
        {
            for (int k = 0; k < 11; k++) temp = (temp * 37 + 11 * i + j) % 101;
            pL->entry[i].data[j] = temp % 101;
        }
    }
    return;
}


void discard_list(LIST *pL)
{
    /**
     * 函数名：discard_list
     * 参数：指向LIST的指针pL
     * 功能：释放pL指向的内存空间
     */
    
    if (!pL) {printf("ERROR discard_list: LIST doesn't exist.\n"); return;}
    free(pL);
    return;
}


void clear_list(LIST *pL)
{
    /**
     * 函数名：clear_list
     * 参数：指向LIST的指针pL
     * 功能：清除所有ENTRY的信息，顺序恢复ENTRY ID
     */
    
    if (!pL) {printf("ERROR clear_list: LIST doesn't exist.\n"); return;}
    for (int i = 0; i < pL->len; i++)
    {
        pL->entry[i].info.id = i;
        clear_entry(&pL->entry[i]);
        pL->sorted[i] = 0;
    }
    pL->len = 0;
    
    return;
}


void clear_entry(ENTRY *pE)
{
    /**
     * 函数名：clear_entry
     * 参数：指向ENTRY的指针pE
     * 功能：清除ENTRY的信息
     */
    
    if (!pE) {printf("ERROR clear_entry: ENTRY doesn't exist.\n"); return;}
    
    for (int i = 0; i < MAXNUM; i++) pE->data[i] = 0;
    pE->info.name = NULL;
    pE->info.gender = 'n';
    pE->info.id = 0;

    return;
}


LIST *create_list(unsigned int len)
{
    /**
     * 函数名：create_list
     * 参数：len（需要生成的列表的长度）
     * 返回值：指向LIST的指针
     * 功能：生成并初始化一个有len个元素的列表
     */
    
    ENTRY *pE = (ENTRY *)malloc(sizeof(ENTRY) * len);
    if (!pE) return NULL;
    for (int i = 0; i < len; i++)
    {
        pE[i].info.name = NULL;
        pE[i].info.gender = 'n';        // 初始性别设置为NA
        pE[i].info.id = i;
        for (int j = 0; j < MAXNUM; j++) pE[i].data[j] = 0;
    }
    
    LIST *pL = (LIST *)malloc(sizeof(LIST));
    if (!pL) exit(0);
    
    pL->entry = pE;
    pL->len = len;
    for (int j = 0; j < MAXNUM; j++) pL->sorted[j] = 0;
    
    return pL;
}



