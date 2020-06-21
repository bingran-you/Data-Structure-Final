/*------------------------------------------------
    作者: ZZY
    日期: 2020.6.8
    文件名: head_file.h
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: 头文件
    
    v1.1: 完成路线搜索、排序功能
    v1.2: 完成终端Interface 20200616
    v1.3: 文件输入完成 20200617
------------------------------------------------*/

#ifndef head_file_h
#define head_file_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAXNUM 101      // 图中城市的最大个数
#define MAXLEN 20       // 字符串的最大长度
#define MAXQUEUE 100    // 使用的队列的最大长度
#define OK 1            // 函数状态正常
#define ERROR 0         // 函数状态异常
#define print_line(); printf("---------------------------------------\n");
#define print_long_line(); printf("---------------------------------------------------------------------------------------------------------------\n");
#define print_double_long_line(); printf("===============================================================================================================\n");


typedef unsigned Status;

typedef enum {AIR, RAIL} CARRIER;   // 交通方式
typedef enum {INVALID, JANUARY, FEBURARY, MARCH, APRIL, MAY, JUNE, 
                JULY, AUGUST, SEPTEMBER, OCTOBER, NOVEMBER, DECEMBER} MONTH;
typedef enum {CLEAN, VERBOSE} MODE;
typedef enum {MON, TUE, WED, THU, FRI, SAT, SUN} WEEK_DAY;
typedef enum {ADD, DEL} ACT;
typedef enum {ECON, SPEED, DIRECT} PRIORITY;      // 决策优先级，ECON表示低价优先，SPEED表示速度优先（耗时越短越好）


typedef struct {
    int year, month, day, hour, minute;      // 以年、月、日、小时(24)、分钟记录时间
} TIME;


typedef struct TICKET_INFO {
    char *from, *to;                // from指向出发地的名称字符串，to指向目的地名称字符串
    char *id;                       // 航班号/火车车次
    CARRIER carrier;                // by air or by rail, = AIR or RAIL respectively
    TIME departure_time;            // 出发时间
    TIME arrival_time;              // 到达时间
    TIME duration;                  // 时常
    bool in_schedule[7];            // 以周为周期的班次信息（1表示存在）
//    float price;                    // 票价
    unsigned price;                    // 票价
    struct TICKET_INFO *next;       // 链表指针
} TICKET_INFO;


typedef struct CITY_LINK_BOX {
    char *from, *to;                // from指向出发地的名称字符串，to指向目的地名称字符串
    TICKET_INFO *first_air_ticket;  // 航空票价，以链表形式记录所有的票价信息
    TICKET_INFO *first_rail_ticket; // 铁路票价，以链表形式记录所有的票价信息
    struct CITY_LINK_BOX *next;
} CITY_LINK_BOX;        // 这里隐含一个约束，即first_air_ticket与first_rail_ticket指向的TICKET_INFO链表中，其from域必须指向同一个城市的城市名


typedef struct {
    bool exist;                     // 该城市是否存在，即是否有从其出发或到达这座城市的交通线路
    bool exist_as_dest;             // 是否存在到达这座城市的交通线路
    char *name;                     // 城市名，字符串，全小写
    CITY_LINK_BOX *first_link;      // 指向第一条边，即与第一个可以到达的城市之间的交通信息
} CITY_BOX;             // 这里同样隐含一个约束，即first_link指向的CITY_LINK_BOX链表中，其from域必须指向同一个城市的城市名


typedef struct {
    CITY_BOX city[MAXNUM];          // 城市交通信息数组，最多100个城市
    unsigned int city_num;          // 已录入信息的城市个数
} TRAFFIC_GRAPH;


typedef struct {
    char *from, *to;                     // 出发地和目的地名称
    PRIORITY priority;                   // 排序优先级
    CARRIER carrier;                     // 交通方式
    TIME departure;                      // 用户给定的出发时间
    WEEK_DAY travelling_week_day;        // 用户最早出行日对应的星期几
} USER_QUERY;


typedef struct {
    TICKET_INFO *first_ticket_info;      // 指向该路径的第一段旅程的票价信息
    CARRIER carrier;                     // 交通方式
    TIME departure_time;                 // 出发时间
    TIME arrival_time;                   // 到达时间
    TIME duration;                       // 整个行程的时长
    TIME on_route_duration;              // 在路上的时长
    TIME transfer_duration;              // 中转耗时
    unsigned int transfer_num;           // 中转的次数
    unsigned int price;                  // 全程总票价
} ROUTE;


typedef struct {
    TICKET_INFO ticket[MAXQUEUE];
    unsigned front;
    unsigned rear;
} TICKET_INFO_QUEUE;


// graph.c
void init_city_box(CITY_BOX *p);
void init_traffic_graph(TRAFFIC_GRAPH *pG);
void delete_traffic_graph(TRAFFIC_GRAPH *pG);
void init_ticket_info_queue(TICKET_INFO_QUEUE *pQ);
void init_ticket_info(TICKET_INFO *pt);
void fill_schedule(TICKET_INFO *p, const bool *s);
void calculate_city_num(TRAFFIC_GRAPH *pG);
void calculate_duration(TIME departure, TIME arrival, TIME *p);
void update_exist_as_dest(TRAFFIC_GRAPH *pG);
void en_queue(TICKET_INFO_QUEUE *pQ, TICKET_INFO t);
void sort_route(ROUTE *pR, int n, PRIORITY priority);
void fill_date_in_ticket_info(TICKET_INFO *pti, TICKET_INFO t);
bool ticket_info_queue_full(TICKET_INFO_QUEUE Q);
bool ticket_info_queue_empty(TICKET_INFO_QUEUE Q);
bool find_route_resursor(const TRAFFIC_GRAPH G, USER_QUERY u, TICKET_INFO *t_current, ROUTE *pR, unsigned *n, TICKET_INFO_QUEUE *pQ, bool *visited);
unsigned find_route(const TRAFFIC_GRAPH G, USER_QUERY u, ROUTE *pR);
unsigned city_to_index(const char *s);
Status insert_new_city(TRAFFIC_GRAPH *pG, const CITY_BOX city);
Status delete_city(TRAFFIC_GRAPH *pG, const char *name);
Status insert_new_ticket_info(TRAFFIC_GRAPH *pG, TICKET_INFO t_info);
Status delete_ticket_info(TRAFFIC_GRAPH *pG, const TICKET_INFO t_info);
TICKET_INFO *get_ticket_info(const char *id, const char *from, const char *to, const CARRIER carrier, const TIME departure_time, const TIME arrival_time, const float price);
TICKET_INFO *get_next_ticket_info(const TRAFFIC_GRAPH G, const char *from, TICKET_INFO t_current);
TICKET_INFO *get_first_ticket_info(const TRAFFIC_GRAPH G, const char *from, const CARRIER carrier);
TICKET_INFO de_queue_from_rear(TICKET_INFO_QUEUE *pQ);
TICKET_INFO de_queue_from_front(TICKET_INFO_QUEUE *pQ);
ROUTE *get_route_from_ticket_info_queue(TICKET_INFO_QUEUE Q, USER_QUERY u);
CITY_LINK_BOX *get_city_link_box(void);
CITY_BOX *get_city_box(const char *name, const bool exist);


// interface.c
void print_interface_header(void);
void print_user_query(USER_QUERY u);
void print_usage(void);
void interface(void);
void interface_end(void);
bool interface_add_ticket_info(TRAFFIC_GRAPH *pG);
bool interface_del_ticket_info(TRAFFIC_GRAPH *pG);
bool interface_add_ticket_info_from_txt(TRAFFIC_GRAPH *pG);
int get_time_from_keyboard(TIME *t);
USER_QUERY get_user_query_from_keyboard(void);


// py_interface.c
unsigned get_city_link_box_num(TRAFFIC_GRAPH *pG, unsigned i);
unsigned get_ticket_info_num(TICKET_INFO *pti);
unsigned get_ticket_info_num_from_one_city(TRAFFIC_GRAPH G, unsigned i);
TICKET_INFO *get_all_ticket_info_from_one_city(TRAFFIC_GRAPH G, unsigned i);


// utils.c
void raise_error(const char *func_name, const char *hint);
void copy_time(const TIME *from, TIME *to);
void copy_schedule(const bool *from, bool *to);
void copy_queue(TICKET_INFO_QUEUE *from, TICKET_INFO_QUEUE *to);
void copy_ticket_info(const TICKET_INFO *from, TICKET_INFO *to);
void copy_city_box(const CITY_BOX *from, CITY_BOX *to);
void string_to_lower_case(char *s);
void print_city_link(const CITY_BOX cb, MODE mode);
void print_ticket_info(TICKET_INFO t, MODE mode);
void print_time(const TIME t, MODE mode, bool newline);
void print_hour_and_minute(TIME t, bool newline);
void print_graph(const TRAFFIC_GRAPH G);
void print_route(ROUTE R);
bool assert_ticket_info_same(const TICKET_INFO t1, const TICKET_INFO t2);
bool assert_time_equal(const TIME t1, const TIME t2);
bool assert_city_name_same(const char *c1, const char *c2);
bool time_A_before_time_B(TIME A, TIME B);
bool is_leap_year(unsigned year);
void init_time(TIME *p);
void add_one_day(TIME *pt);
unsigned time_subtraction(TIME ta, TIME tb, TIME *ptc);
unsigned time_addition(TIME ta, TIME tb, TIME *ptc);
WEEK_DAY time_to_week_day(TIME t);


// test.c
void test_time(void);
void test_user_input_from_keyboard(void);
void test_city_to_index(void);
void test_print_ticket_info(void);
void test_city_link(void);
void test_insert_new_ticket_info(void);
void test_delete_ticket_info(void);
void test_get_next_ticket_info(void);
void test_time_to_week_day(void);
void test_find_route(void);
void test_add_ticket_info_from_txt(void);
void test_add_one_day(void);
void test_get_city_link_num(void);
void test_get_ticket_info_num(void);


// io.c
bool add_ticket_info_from_txt(TRAFFIC_GRAPH *pG, const char *fname);


#endif /* head_file_h */
