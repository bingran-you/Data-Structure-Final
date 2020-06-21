/*------------------------------------------------
  作者: ZZY YBR WZR
  日期: 2020.6.12
  文件名: head_file.h
  版本: v1.8
  项目: 数据结构大作业--多关键字排序
  说明: 头文件
------------------------------------------------*/

#ifndef head_file_h
#define head_file_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <stdbool.h>

#define MAXNUM 5
#define MINDATA 0
#define MAXDATA 100
#define BITNUM 10
#define SORTNUM 8
#define LINE "-------------------------------------------------------------\n"
#define print_line(); printf("%s", LINE);
#define VERBOSE 1
#define SIMPLE 0

typedef int Status, MODE;

typedef struct {
    unsigned int id;
    char *name;
    char gender;
    // TODO
    // 可以添加其他信息
} INFO;

typedef struct {
    int data[MAXNUM];         // 0 ~ 100
    INFO info;
} ENTRY;

typedef struct {
    ENTRY *entry;
    unsigned int len;
    int sorted[MAXNUM];
    // TODO
    // 可以添加其他信息
} LIST;

typedef struct ETNode{
    int data;
    struct ETNode *next;
    // TODO
    // 可以添加其他信息
} ETNode;

typedef struct SNode{
    int data;
    ETNode *firstarc;
} SNode;

typedef struct {
    int sumtime;
    int name;
    int extimes;
} TIME_LIST;

typedef enum KEY_IDX {KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, ALL} KEY_IDX;
typedef unsigned (*FUNC)(LIST *pL, KEY_IDX key_idx, int begin, int end, int endian);


// utils.c
void print_entry_verbose(ENTRY *pE);
void print_entry_simple(ENTRY *pE);
void print_list(LIST *pL, MODE mode);
void print_time_list(TIME_LIST *pL);
void copy_list(LIST *from, LIST *to);
unsigned copy_entry(ENTRY *from, ENTRY *to);
unsigned swap_entry(ENTRY *from, ENTRY *to);
unsigned get_list_length(LIST *pL);
TIME_LIST *time_judge(unsigned int len, int num, int seq);
TIME_LIST *time_cal(LIST *pL, FUNC sort_func, KEY_IDX *sort_seq, int kind, int *endian);
LIST *get_sorted_result(int len, KEY_IDX *sort_seq, int sort_type, bool is_msd, int *endian);


// sort.c
unsigned MSD_sort_framework(LIST *pL, FUNC sort_func, KEY_IDX *sort_seq, int *endian);
unsigned LSD_sort_framework(LIST *pL, FUNC sort_func, KEY_IDX *sort_seq);
unsigned merge_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned radix_10_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned radix_101_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned quick_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned bubble_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned insert_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned shell_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);
unsigned max_heapify(LIST *pL, KEY_IDX current_key_idx, int start, int end, int endian);
unsigned heap_sort(LIST *pL, KEY_IDX current_key_idx, int begin, int end, int endian);


// list.c
void rand_list(LIST *pL);
void discard_list(LIST *pL);
void clear_list(LIST *pL);
void clear_entry(ENTRY *pE);
LIST *create_list(unsigned int len);


#endif /* head_file_h */
