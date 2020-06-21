/*------------------------------------------------
  作者: ZZY YBR WZR
  日期: 2020.6.12
  函数名: utils.c
  版本: v1.8
  项目: 数据结构大作业--多关键字排序
  说明: 工具函数集合
------------------------------------------------*/

#include "head_file.h"

void print_entry_verbose(ENTRY *pE)
{
    /**
     * 函数名：print_entry_verbose
     * 参数：指向ENTRY的指针pE
     * 功能：打印ENTRY的内容，按条目详细打印
     */
    
    if (!pE) {printf("ERROR print_entry_verbose: ENTRY doesn't exist.\n"); return;}
    
    print_line();
    printf("ENTRY ID: %d\n", pE->info.id);
    printf("DATA:\n\tidx\t");
    for (int i = 0; i < MAXNUM; i++)
        printf("%d\t", i);
    printf("\n\tdata\t");
    for (int i = 0; i < MAXNUM; i++)
        printf("%u\t", pE->data[i]);
    printf("\nINFO:\n\t");
    if (pE->info.name) printf("name: %s\n\t", pE->info.name);
    else printf("name: NO NAME\n\t");
    printf("gender: %c\n", pE->info.gender);
    
    return;
}


void print_entry_simple(ENTRY *pE)
{
    /**
     * 函数名：print_entry_simple
     * 参数：指向ENTRY的指针pE
     * 功能：打印ENTRY的内容，简化版
     */
    
    if (!pE) {printf("ERROR print_entry_simple: ENTRY doesn't exist.\n"); return;}
    
    printf("%d\t", pE->info.id);
    if (pE->info.name) printf("%s\t", pE->info.name);
    else printf("N/A\t");
    printf("%c\t", pE->info.gender);
    for (int i = 0; i < MAXNUM; i++)
        printf("%u\t", pE->data[i]);
    putchar('\n');
    
    return;
}


void print_list(LIST *pL, MODE mode)
{
    /**
     * 函数名：print_list
     * 参数：指向列表的指针pL，模式选择（VERBOSE为详细内容，SIMPLE为简化版内容）
     * 功能：打印列表内容，两种打印模式可选
     */
    
    if (!pL) {printf("ERROR print_list: LIST doesn't exist.\n"); return;}
    
    if (mode == VERBOSE)
    {
        print_line();
        printf("NUM of elements: %d\n", pL->len);
        printf("SORTED keys:\n\tkeys\t");
        for (int i = 0; i < MAXNUM; i++)
            printf("%d\t", i);
        printf("\n\t\t");
        for (int i = 0; i < MAXNUM; i++)
            printf("%s\t", pL->sorted[i] ? "YES" : "NO");
        putchar('\n');
    } else if (mode == SIMPLE) {
        print_line();
        printf("ID\tNAME\tGENDER\tDATA0\tDATA1\tDATA2\tDATA3\tDATA4\n");
        print_line();
    } else {
        printf("ERROR print_list: invalid mode\n");
    }
    
    for (int i = 0; i < pL->len; i++)
        if (mode == VERBOSE)
        {
            print_entry_verbose(&pL->entry[i]);
        } else if (mode == SIMPLE) {
            print_entry_simple(&pL->entry[i]);
        } else {
            printf("ERROR print_list: invalid mode\n");
        }
    
    return;
}


unsigned get_list_length(LIST *pL)
{
    /**
     * 函数名：get_list_length
     * 参数：指向LIST的指针pL
     * 返回值：LIST的长度
     * 功能：返回列表长度（数据库元素个数）
     */
    
    if (!pL) {printf("ERROR get_list_length: LIST doesn't exist.\n"); return 0;}
    return pL->len;
}


unsigned copy_entry(ENTRY *from, ENTRY *to)
{
    /**
     * 函数名：copy_entry
     * 参数：两个指向ENTRY的指针from和to
     * 功能：将from指向的ENTRY值拷贝至to指向的ENTRY
     */
    
    for (int i = 0; i < MAXNUM; i++)
        to->data[i] = from->data[i];
    
    to->info.name = from->info.name;
    to->info.gender = from->info.gender;
    to->info.id = from->info.id;
    
    return 1;
}


unsigned swap_entry(ENTRY *from, ENTRY *to)
{
    /**
     * 函数名：swap_entry
     * 参数：两个指向ENTRY的指针from和to
     * 功能：交换from指向的ENTRY值和to指向的ENTRY
     */
    
    ENTRY temp;
    
    copy_entry(from, &temp);
    copy_entry(to, from);
    copy_entry(&temp, to);
    
    return 3;
}


TIME_LIST *time_judge(unsigned int len, int num, int seq)
{
    /**
     * 函数名：time_judge
     * 参数：len表示每组数据的个数，num表示数据的组数,seq表示时间和交换次数的优先级，1表示时间优先
     * 功能：按照len生成数据获得完成每个排序所花的时间，对num个数据取平均值获得
     * 备注：其中begin和end分别对应数组pL中的项pL[begin]和pL[end]（第一项和最后一项）
     */
    
    int time_record[SORTNUM][2];
    KEY_IDX sort_seq[MAXNUM] = {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5};
    int i, j, k;
    
    //初始化
    for (int i = 0; i < SORTNUM; i++)
    {
        time_record[i][0] = 0;
        time_record[i][1] = 0;
    }
    
    int endian[5] = {1, 1, 1, 1, 1};
    
    TIME_LIST *q;
    for (int i = 0; i < num; i++)
    {
        LIST *s = create_list(len);
        rand_list(s);
        q = time_cal(s, radix_10_sort, sort_seq, 0, endian);
        time_record[0][0] += q->sumtime;
        time_record[0][1] += q->extimes;
        q = time_cal(s, radix_101_sort, sort_seq, 1, endian);
        time_record[1][0] += q->sumtime;
        time_record[1][1] += q->extimes;
        q = time_cal(s, merge_sort, sort_seq, 2, endian);
        time_record[2][0] += q->sumtime;
        time_record[2][1] += q->extimes;
        q = time_cal(s, quick_sort, sort_seq, 3, endian);
        time_record[3][0] += q->sumtime;
        time_record[4][1] += q->extimes;
        q = time_cal(s, bubble_sort, sort_seq, 4, endian);
        time_record[4][0] += q->sumtime;
        time_record[4][1] += q->extimes;
        q = time_cal(s, insert_sort, sort_seq, 5, endian);
        time_record[5][0] += q->sumtime;
        time_record[5][1] += q->extimes;
        q = time_cal(s, shell_sort, sort_seq, 6, endian);
        time_record[6][0] += q->sumtime;
        time_record[6][1] += q->extimes;
        q = time_cal(s, heap_sort, sort_seq, 7, endian);
        time_record[7][0] += q->sumtime;
        time_record[7][1] += q->extimes;
    }
    
    TIME_LIST *p;
    p = (TIME_LIST *)malloc(SORTNUM * sizeof(TIME_LIST));
    
    int sum_time,sum_extimes;
    for (j = 0; j < SORTNUM; j++)     //进行时间比较
    {
        sum_time = time_record[j][0];
        sum_extimes = time_record[j][1];
        
        if(seq == 0) for (i = 0; i < j && p[i].sumtime <= sum_time; i++);
        else for (i = 0; i < j && p[i].extimes <= sum_extimes; i++);
        
        if (i != j)
        {
            k = j;
            while (k > i)
            {
                p[k].name = p[k - 1].name;
                p[k].sumtime = p[k - 1].sumtime;
                p[k].extimes = p[k - 1].extimes;
                k--;
            }
        }
        p[i].name = j;
        p[i].sumtime = sum_time;
        p[i].extimes = sum_extimes;
    }
    return p;
}

TIME_LIST *time_cal(LIST *pL, FUNC sort_func, KEY_IDX *sort_seq, int kind, int *endian)
{
    /**
     * 函数名：time_cal
     * 参数：指向LIST的指针pL, 排序函数类型sort_func，关键字下标sort_seq
     * 功能：计算排序从开始到结束的时间
     */
    
    LIST *q = (LIST *)malloc(sizeof(LIST));
    q->entry = (ENTRY *)malloc(sizeof(ENTRY) * pL->len);
    copy_list(pL, q);
    
    clock_t start,finish;
    start = clock();
    int count = MSD_sort_framework(q, sort_func, sort_seq, endian);
    finish = clock();
    
    TIME_LIST *p = (TIME_LIST *)malloc(sizeof(TIME_LIST));
    p->name = kind;
    p->sumtime = (int)(finish - start);
    p->extimes = count;
    
    return p;
}


void print_time_list(TIME_LIST *pL)
{
    /**
     * 函数名：print_time_list
     * 参数：指向列表的指针pL，模式选择（VERBOSE为详细内容，SIMPLE为简化版内容）
     * 功能：打印列表内容，两种打印模式可选
     */
    
    if (!pL) {printf("ERROR print_list: LIST doesn't exist.\n"); return;}
    
    print_line();
    printf("MODE\t\t\t\tSUMTIME\n");
    print_line();
    
    TIME_LIST *p = pL;
    int i = 0;
    while (i < SORTNUM)
    {
        if(p[i].name == 0) printf("radix_10_sort\t\t\t");
        else if(p[i].name == 1) printf("radix_101_sort\t\t\t");
        else if(p[i].name == 2) printf("merge_sort\t\t\t");
        else if(p[i].name == 3) printf("quick_sort\t\t\t");
        else if(p[i].name == 4) printf("bubble_sort\t\t\t");
        else if(p[i].name == 5) printf("insert_sort\t\t\t");
        else if(p[i].name == 6) printf("shell_sort\t\t\t");
        else if(p[i].name == 7) printf("heap_sort\t\t\t");
        printf("%d\t",p[i].sumtime);
        printf("%d\n",p[i].extimes);
        i++;
    }
    print_line();
    return;
}


void copy_list(LIST *from, LIST *to)
{
    /**
     * 函数名：copy_list
     * 参数：两个指向LIST的指针from和to
     * 功能：将from指向的LIST值拷贝至to指向的LIST
     */
    
    int i = 0;
    
    to->len = from->len;
    
    for(i = 0;i < MAXNUM;i++)
        to->sorted[i] = from->sorted[i];
    
    for(i = 0; i < from->len; i++)
    {
        copy_entry(&from->entry[i], &to->entry[i]);
    }
        
    
    return;
}


LIST *get_sorted_result(int len, KEY_IDX *sort_seq, int sort_type, bool is_msd, int *endian)
{
    /**
     * 函数名：get_sorted_result
     * 参数：len表示每组数据的个数，sort_seq表示关键字的顺序，sort_type表示排序函数种类，seq为1表示MSD，为0表示LSD
     * 功能：按照len生成数据， 根据sort_seq进行排序
     * 备注：由于采用各种稳定的排序算法得到的最终结果相同
     */
    
    LIST *p = create_list(len);
    rand_list(p);
    
    typedef enum {SHELL_SORT, RADIX_10_SORT, MERGE_SORT, QUICK_SORT, BUBBLE_SORT, INSERT_SORT, HEAP_SORT, RADIX_101_SORT} SORT_TYPE;
    
    if (is_msd)
    {
        switch (sort_type)
        {
            case SHELL_SORT: MSD_sort_framework(p, shell_sort, sort_seq, endian); break;
            case RADIX_10_SORT: MSD_sort_framework(p, radix_10_sort, sort_seq, endian); break;
            case MERGE_SORT: MSD_sort_framework(p, merge_sort, sort_seq, endian); break;
            case QUICK_SORT: MSD_sort_framework(p, quick_sort, sort_seq, endian); break;
            case BUBBLE_SORT: MSD_sort_framework(p, bubble_sort, sort_seq, endian); break;
            case INSERT_SORT: MSD_sort_framework(p, insert_sort, sort_seq, endian); break;
            case HEAP_SORT: MSD_sort_framework(p, heap_sort, sort_seq, endian); break;
            case RADIX_101_SORT: MSD_sort_framework(p, radix_101_sort, sort_seq, endian); break;
            default: printf("ERROR get_sorted_result: Unknown sort function kind.\n");
                return NULL;
        }
    } else {
        switch (sort_type)
        {
            case SHELL_SORT: LSD_sort_framework(p, shell_sort, sort_seq); break;
            case RADIX_10_SORT: LSD_sort_framework(p, radix_10_sort, sort_seq); break;
            case MERGE_SORT: LSD_sort_framework(p, merge_sort, sort_seq); break;
            case QUICK_SORT: LSD_sort_framework(p, quick_sort, sort_seq); break;
            case BUBBLE_SORT: LSD_sort_framework(p, bubble_sort, sort_seq); break;
            case INSERT_SORT: LSD_sort_framework(p, insert_sort, sort_seq); break;
            case HEAP_SORT: LSD_sort_framework(p, heap_sort, sort_seq); break;
            case RADIX_101_SORT: LSD_sort_framework(p, radix_101_sort, sort_seq); break;
            default: printf("ERROR get_sorted_result: Unknown sort function kind.\n");
                return NULL;
        }
    }
    
    return p;
}
