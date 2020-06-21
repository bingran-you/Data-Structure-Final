/*------------------------------------------------
  作者: ZZY YBR WZR
  日期: 2020.6.12
  文件名: sort.c
  版本: v1.8
  项目: 数据结构大作业--多关键字排序
  说明: 所有排序子函数
------------------------------------------------*/

#include "head_file.h"


unsigned LSD_sort_framework(LIST *pL, FUNC sort_func, KEY_IDX *sort_seq)
{
    /**
     * 函数名：LSD_sort_framework
     * 参数：指向LIST的指pL，排序函数sort_func, 排序的顺序sort_seq
     * 功能：LSD排序策略框架；按照sort_seq指定的顺序，用sort_func给pL指向的LIST排序，在该LSD排序框架中可以调用不同的子函数，比如归并排序、冒泡排序等稳定的排序算法对子序列的某一关键字进行排序，也可以使用分配与收集策略
     */
    
    unsigned count = 0;
    
    int endian[5] = {1, 1, 1, 1, 1};
    
    for (int p = MAXNUM - 1; p >= 0; p--)
        count += sort_func(pL, sort_seq[p], 0, pL->len - 1, endian[sort_seq[p]]);

    return count;
}


unsigned MSD_sort_framework(LIST *pL, FUNC sort_func, KEY_IDX *sort_seq, int *endian)
{
    /**
     * 函数名：MSD_sort_framework
     * 参数：指向LIST的指pL，排序函数sort_func, 排序的顺序sort_seq
     * 功能：MSD排序策略框架；按照sort_seq指定的顺序，用sort_func给pL指向的LIST排序L，每次对一个关键字排序完成后，下一次排序将在前一个关键字相同的子序列中进行；在该MSD排序框架中可以调用不同的子函数，比如归并排序、冒泡排序等稳定的排序算法对子序列的某一关键字进行排序
     */
    
    unsigned count = 0;
    
    for (int p = 0; p < MAXNUM; p++)
    {
        KEY_IDX current_key_idx = sort_seq[p];
        KEY_IDX last_key_idx = (p == 0) ? ALL : sort_seq[p-1];
        if (last_key_idx != ALL)
        {
            int i = 0, j = 0;
            int temp = pL->entry[0].data[last_key_idx];
            while (j < pL->len)
            {
                int k = 0;
                while (j < pL->len)
                {
                    k = p - 1;
                    if (pL->entry[j].data[sort_seq[k]] != pL->entry[i].data[sort_seq[k]]) break;
                    while (pL->entry[j].data[sort_seq[k]] == pL->entry[i].data[sort_seq[k]])
                    {
                        k--;
                        if (k == -1) {j++; break;}
                    }
                    if (k != -1) break;
                }
                sort_func(pL, current_key_idx, i, j - 1, endian[current_key_idx]);
                if (j == pL->len) break;
                i = j++;
                temp = pL->entry[i].data[last_key_idx];
            }
        } else {
            count += sort_func(pL, sort_seq[0], 0, pL->len - 1, endian[current_key_idx]);
        }
        pL->sorted[current_key_idx] = 1;
    }
    
    return count;
}


unsigned merge_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：merge_sort
     * 参数：指向LIST的指pL，当前正在排序的key的索引current_key_idx，当前正在排序的片段在pL->entry数组中的起止索引；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 返回值：排序过程中移动ENTRY的次数
     * 功能：sort_list的子函数，递归调用自己完成给指定的key排序（sort_list()保证已经排过序的key不再排序）
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR merge_sort: invalid key_idx.\n");
        return 0;
    }
    
    int middle = (begin + end) / 2;
    count += merge_sort(pL, current_key_idx, begin, middle, endian);
    count += merge_sort(pL, current_key_idx, middle+1, end, endian);
    
    ENTRY entry_temp[pL->len];
    
    int i, j, k;
    
    for (i = begin, j = begin, k = middle+1; j <= middle && k <= end;)
    {
        if (endian * pL->entry[j].data[current_key_idx] < endian * pL->entry[k].data[current_key_idx])
            count += copy_entry(&pL->entry[j++], &entry_temp[i++]);
        else
            count += copy_entry(&pL->entry[k++], &entry_temp[i++]);
    }
    
    while (j <= middle) count += copy_entry(&pL->entry[j++], &entry_temp[i++]);
    while (k <= end) count += copy_entry(&pL->entry[k++], &entry_temp[i++]);
    
    for (int i = begin; i <= end; i++)
        count += copy_entry(&entry_temp[i], &pL->entry[i]);
    
    return count;
}


unsigned radix_10_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：radix_10_sort
     * 参数：指向LIST的指pL，当前正在排序的key的索引current_key_idx，当前正在排序的片段在pL->entry数组中的起止索引；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：对某一排序子片段采用基数为10的基数排序，即将该子片段的某个关键字（3位整数）的每一位再看做一个关键字，用分配与收集策略进行基数为10的基数排序
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR radix_10_sort: invalid key_idx.\n");
        return 0;
    }
    
    int bitnum = 1, i, j;
    int biten = 1;                      // 写使能信号
    
    SNode sL[BITNUM];                   // 用于存放分配至各位的数据
    ETNode *p, *q;
    ENTRY entry_temp[end - begin + 1];
    
    for(i = 0; i < 10; i++)             // 分配初始化
        sL[i].data = i;
    
    while (biten)
    {
        for(i = 0; i < 10; i++)         // 初始化
            sL[i].firstarc = NULL;
        
        biten = 0;
        
        for (i = begin; i <= end; i++)  // 分配
        {
            p = (ETNode *)malloc(sizeof(ETNode));
            p->data = i;
            p->next = NULL;
            
            j = pL->entry[i].data[current_key_idx] / bitnum;
            
            if (j / 10 != 0) biten = 1;         // 判断是否需要为下一位排序
            j = j % 10;                         // 获得当前位的数字
            if (!sL[j].firstarc)                // 分配进组
            {
                sL[j].firstarc = p;
            } else {
                for (q = sL[j].firstarc; q && q->next; q = q->next)
                    ;
                q->next = p;
            }
        }
        
        for (i = 9, j = 0; i >= 0; i--)     // 收集
        {
            for (q = sL[i].firstarc; q; q = q->next)        // 对于每个组的数字
            {
                p = q;
                count += copy_entry(&pL->entry[q->data], &entry_temp[j++]);
                free(p);
            }
        }
        
        for(i = begin, j = 0; i <= end; i++)        //拷贝排列后的list
            count += copy_entry(&entry_temp[j++], &pL->entry[i]);
    
        bitnum *= 10;                   //研究下一位数字
    }

    return count;
}


unsigned radix_101_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：radix_101_sort
     * 参数：指向LIST的指针pL，关键字下标key_idx，起始项和末尾项下标begin和end；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：实现对给定数据片段的给定关键字使用基数排序，由于排序中的数值范围为0到100（含），故可以采用基数为101的分配与收集策略
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR radix_101_sort: invalid key_idx.\n");
        return 0;
    }
    
    int len = (end - begin + 1);  // 得到数组长度
    
    ENTRY distribute[101][len];
    
    int i = 0, j = 0;
    
    int where_now[101] = {0}; // 定义数组where_now，用来记录对应的记录链当前可用的下一个位置的标号
    
    // 分配
    for (i = 0; i < len; i++)
    {
        int temp = pL->entry[begin+i].data[current_key_idx];
//        distribute[temp][where_now[temp]] = pL->entry[begin+i];
        count += copy_entry(&pL->entry[begin+i], &distribute[temp][where_now[temp]]);
        where_now[temp]++;
    }

    // 收集
    int number = 0;
    for (i = 100; i >= 0; i--)
    {
        for (j = 0; j < where_now[i]; j++)
        {
//            pL->entry[begin+number] = distribute[i][j];
            count += copy_entry(&distribute[i][j], &pL->entry[begin+number]);
            number++;
        }
    }
    
    return count;
}


unsigned quick_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：quick_sort
     * 参数：指向LIST的指pL，当前正在排序的key的索引current_key_idx，当前正在排序的片段在pL->entry数组中的起止索引；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：递归调用自己完成给指定的key排序（sort_list()保证已经排过序的key不再排序）
     * 备注：不稳定的排序，仅作为额外实现
     */
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR quick_sort: invalid key_idx.\n");
        return 0;
    }

    int i = begin;
    int j = end;
    int key = pL->entry[i].data[current_key_idx];
    
    ENTRY temp;
    count += copy_entry(&pL->entry[i], &temp);
    
    while (i < j)
    {
        while (i < j && endian * pL->entry[j].data[current_key_idx] >= endian * key)
            --j;
        if (i < j)
            count += copy_entry(&pL->entry[j], &pL->entry[i]);
        
        while (i < j && endian * pL->entry[i].data[current_key_idx] <= endian * key)
            ++i;
        if (i < j)
            count += copy_entry(&pL->entry[i], &pL->entry[j]);
    }
    
    count += copy_entry(&temp, &pL->entry[i]);
    
    count += quick_sort(pL, current_key_idx, begin, i - 1, endian);
    count += quick_sort(pL, current_key_idx, i + 1, end, endian);
    
    return count;
}



unsigned bubble_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：bubble_sort
     * 参数：指向LIST的指pL，当前正在排序的key的索引current_key_idx，当前正在排序的片段在pL->entry数组中的起止索引；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：完成给指定的key排序（sort_list()保证已经排过序的key不再排序）
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR bubble_sort: invalid key_idx.\n");
        return 0;
    }
    
    int i,j;
    for (i = begin; i <= end; i++)
        for (j = end; j > i; j--)
            if (endian * pL->entry[j].data[current_key_idx] < endian * pL->entry[j - 1].data[current_key_idx])
                count += swap_entry(&pL->entry[j], &pL->entry[j - 1]);
    
    return count;
}


unsigned insert_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：insert_sort
     * 参数：指向LIST的指pL，当前正在排序的key的索引current_key_idx，当前正在排序的片段在pL->entry数组中的起止索引；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：完成给指定的key排序（sort_list()保证已经排过序的key不再排序）
     * 备注：不稳定的排序，仅作为额外实现
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR insert_sort: invalid key_idx.\n");
        return 0;
    }
    
    int i, j;
    ENTRY temp;

    for(i = begin + 1; i <= end; i++)
    {
        count += copy_entry(&pL->entry[i], &temp);
        j = i - 1;
        while(j >= begin && endian * temp.data[current_key_idx] < endian * pL->entry[j].data[current_key_idx])
        {
            count += copy_entry(&pL->entry[j], &pL->entry[j + 1]);
            j--;
        }
        count += copy_entry(&temp, &pL->entry[j + 1]);
    }
    
    return count;
}



unsigned shell_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：shell_sort
     * 参数：指向LIST的指针pL，关键字下标key_idx，起始项和末尾项下标begin和end；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：以key_idx标记的数据项为参照，用shell_sort给pL指向的LIST排序
     * 备注：其中begin和end分别对应数组pL中的项pL[begin]和pL[end]（第一项和最后一项）
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR shell_sort: invalid key_idx.\n");
        return 0;
    }
    
    int len = (end - begin + 1);
    int i = 0, j = 0, gap = 1;
    ENTRY temp;
    
    for (gap = len/2; gap > 0; gap /= 2)
    {
        for (i = gap; i < len; i++)
        {
            for (j = (i - gap);
                j >= 0 && endian * pL->entry[begin + j].data[current_key_idx] > endian * pL->entry[begin + j + gap].data[current_key_idx];
                j -= gap)
            {
                count += copy_entry(&pL->entry[begin + j + gap], &temp);
                count += copy_entry(&pL->entry[begin + j], &pL->entry[begin + j + gap]);
                count += copy_entry(&temp, &pL->entry[begin + j]);
            }
        }
    }
    
    //表示下标为key_idx的数据项已经有序
    pL->sorted[current_key_idx] = 1;
    
    return count;
}



unsigned max_heapify(LIST *pL, KEY_IDX current_key_idx, int start, int end, int endian)
{
    /**
     * 函数名：heap_sort
     * 参数：指向LIST的指针pL，关键字下标key_idx，起始项和末尾项下标start和end；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：建立父节点指标和子节点指标
     */
    
    unsigned count = 0;
    
    int dad = start;
    ENTRY temp;
    int son = dad * 2 + 1;
    while (son <= end)                                                 // 若子节点指标在范围内才做比较
    {
            if (son + 1 <= end &&
                endian * pL->entry[son].data[current_key_idx] <
                endian * pL->entry[son + 1].data[current_key_idx])              // 先比较两个子节点大小，选择最大的
                son++;
        if (endian * pL->entry[dad].data[current_key_idx] >
            endian * pL->entry[son].data[current_key_idx])                      // 如果父节点大 代表调整完毕，直接跳出函数
                return count;
        else {                                                         // 否则交换父子内容再继续子节点和孙节点比较
            count += copy_entry(&pL->entry[son], &temp);
            count += copy_entry(&pL->entry[dad], &pL->entry[son]);
            count += copy_entry(&temp, &pL->entry[dad]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
    
    return count;
}



unsigned heap_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian)
{
    /**
     * 函数名：heap_sort
     * 参数：指向LIST的指针pL，关键字下标key_idx，起始项和末尾项下标begin和end；endian指示大小端序，endian=1表示从小到大排序，endian=-1表示从大到小排序
     * 功能：以key_idx标记的数据项为参照，用heap_sort给pL指向的LIST排序
     * 备注：不稳定的排序，仅作为额外实现
     */
    
    unsigned count = 0;
    
    if (begin >= end) return 0;
    if (current_key_idx < KEY_1 || current_key_idx > KEY_5)
    {
        printf("ERROR heap_sort: invalid key_idx.\n");
        return 0;
    }
    
    ENTRY temp;
    int len = end - begin + 1;
    int i;
    
    //初始化
    for (i = len / 2 - 1; i >= 0; i--)
        count += max_heapify(pL, current_key_idx, i+begin, len - 1 + begin, endian);
    
    //先将第一个元素和已排好元素前一位做交换，再重新调整，直到排序完毕
    for (i = len - 1; i > 0; i--)
    {
        count += copy_entry(&pL->entry[0], &temp);
        count += copy_entry(&pL->entry[i], &pL->entry[0]);
        count += copy_entry(&temp, &pL->entry[i]);
        count += max_heapify(pL, current_key_idx, 0 + begin, i - 1 + begin, endian);
    }
    
    return count;
}



