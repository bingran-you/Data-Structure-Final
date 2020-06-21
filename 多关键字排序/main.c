/*------------------------------------------------
  作者: ZZY YBR WZR
  日期: 2020.6.12
  文件名: main.c
  版本: v1.8
  项目: 数据结构大作业--多关键字排序
------------------------------------------------*/

#include "head_file.h"

// main函数只用于测试，最终的结果见GUI
int main(int argc, char *argv[])
{
    LIST *p = create_list(101);
    rand_list(p);
    KEY_IDX sort_seq[MAXNUM] = {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5};
    int endian[5] = {1, 1, 1, 1, 1};
    MSD_sort_framework(p, insert_sort, sort_seq, endian);
    print_list(p, SIMPLE);
    
    int i,j;
    clock_t start,finish;
    for(i = 0;i < 5;i++){
        p = create_list(200);
        rand_list(p);
        for(j = 0;j < 7;j++){
            start = clock();
            get_sorted_result(200, sort_seq, j, 1, endian);
            finish = clock();
            printf("MSD：%d: %d\n",j,(int)(finish - start));
        }
        for(j = 0;j < 7;j++){
            start = clock();
            get_sorted_result(200, sort_seq, j, 0, endian);
            finish = clock();
            
            printf("LSD：%d: %d\n",j,(int)(finish - start));
        }
        printf("\n\n\n");
    }
    
    printf("Done\n");
    return 0;
}
