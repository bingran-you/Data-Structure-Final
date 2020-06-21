/*------------------------------------------------
    作者: ZZY
    日期: 2020.6.8
    文件名: utils.c
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: 工具函数，用于中间过程计算、调试等
 
    v1.1: 完成路线搜索、排序功能
    v1.2: 完成终端Interface 20200616
    v1.3: 文件输入完成 20200617
------------------------------------------------*/

#include "head_file.h"


unsigned int month_day[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

const char *WEEK_DAY_NAME[7] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};

void raise_error(const char *func_name, const char *hint)
{
    /**
     * 函数名：raise_error
     * 参数：const char *func_name：出错的函数的名称，字符串
     *      const char *hint：出错后的提示，字符串
     * 返回值：无
     * 作用：打印错误提示信息
     */
    
    printf("! ERROR %s: %s\n", func_name, hint);
    return;
}


void copy_time(const TIME *from, TIME *to)
{
    /**
     * 函数名：copy_time
     * 参数：两个指向TIME的指针from和to
     * 返回值：无
     * 作用：将from的值拷贝到to中
     */
    
    to->year = from->year;
    to->month = from->month;
    to->day = from->day;
    to->hour = from->hour;
    to->minute = from->minute;
    return;
}


void copy_schedule(const bool *from, bool *to)
{
    /**
     * 函数名：copy_schedule
     * 作用：拷贝班表
     */
    
    for (int i = 0; i < 7; i++)
        to[i] = from[i];
    return;
}


void copy_queue(TICKET_INFO_QUEUE *from, TICKET_INFO_QUEUE *to)
{
    /**
     * 函数名：copy_queue
     * 作用：拷贝队列
     */
    
    if (!from || !to)
    {
        raise_error("copy_queue", "Invalid TICKET_INFO_QUEUE pointer.");
        return;
    }
    
    for (int i = 0; i < MAXQUEUE; i++)
        to->ticket[i] = from->ticket[i];
    to->rear = from->rear;
    to->front = from->front;
    
    return;
}


void copy_ticket_info(const TICKET_INFO *from, TICKET_INFO *to)
{
    /**
     * 函数名：copy_ticket_info
     * 作用：拷贝TICKET_INFO结构体变量，//将to的next域设置为NULL
     */
    
    strcpy(to->id, from->id);
    strcpy(to->from, from->from);
    strcpy(to->to, from->to);
    copy_time(&from->departure_time, &to->departure_time);
    copy_time(&from->arrival_time, &to->arrival_time);
    copy_time(&from->duration, &to->duration);
    copy_schedule(from->in_schedule, to->in_schedule);
    to->carrier = from->carrier;
    to->price = from->price;
    to->next = from->next;
    
    return;
}


void copy_city_box(const CITY_BOX *from, CITY_BOX *to)
{
    /**
     * 函数名：copy_city_box
     * 参数：两个CITY_BOX指针from和to
     * 作用：将from的内容拷贝到to中
     */
    
    to->exist = from->exist;
    strcpy(to->name, from->name);
    to->first_link = from->first_link;
    
    return;
}


void string_to_lower_case(char *s)
{
    /**
     * 函数名：string_to_lower_case
     * 作用：将字符串转换为小写字母
     */
    
    size_t len = strlen(s);
    for (int i = 0; i < len; i++)
        s[i] = tolower(s[i]);
    return;
}


void print_city_link(const CITY_BOX cb, MODE mode)
{
    /**
     * 函数名：print_city_link
     * 参数：CITY_BOX变量，打印模式mode（VERBOSE或CLEAN）
     * 作用：打印所有从该城市出发的交通方式信息
     */
    
    print_long_line();
    printf("CITY LINK INFO from %s:\n", cb.name);
    CITY_LINK_BOX *pcb = cb.first_link;
    if (!pcb) {printf("! No city link info from %s\n", cb.name); return;}
    
    printf("* AIR TICKETS:\n");
    printf("  ID        FROM        TO        CARRIER        PRICE\tDEPARTURE\tARRIVAL\t\tDURATION\tSCHEDULE\n");
    while (pcb)
    {
        TICKET_INFO *pa = pcb->first_air_ticket;
        
        while (pa)
        {
            print_ticket_info(*pa, CLEAN);
            pa = pa->next;
        }
        pcb = pcb->next;
    }
    
    pcb =cb.first_link;
    printf("* TRAIN TICKETS:\n");
    printf("  ID        FROM        TO        CARRIER        PRICE\tDEPARTURE\tARRIVAL\t\tDURATION\tSCHEDULE\n");
    while (pcb)
    {
        TICKET_INFO *pr = pcb->first_rail_ticket;
        
        while (pr)
        {
            print_ticket_info(*pr, CLEAN);
            pr = pr->next;
        }
        pcb = pcb->next;
    }
    
    return;
}


void print_ticket_info(TICKET_INFO t, MODE mode)
{
    /**
     * 函数名：print_ticket_info
     * 参数：TICKET_INFO结构体变量，打印模式mode
     * 作用：打印单个交通票的信息
     */
    
    if (mode == VERBOSE)
    {
        printf("  FLIGHT/TRAIN ID: %s\n", t.id);
        printf("  FROM: %s\n", t.from);
        printf("  TO: %s\n", t.to);
        printf("  CARRIER: %s\n", (t.carrier == AIR) ? "PLANE" : "RAIL");
        printf("  DEPARTURE: ");
        print_hour_and_minute(t.departure_time, false);
        printf("  ARRIVAL: ");
        print_hour_and_minute(t.arrival_time, false);
        printf("  DURATION: %dd %dh %dm\n", t.duration.day, t.duration.hour, t.duration.minute);
        printf("  PRICE: %u\n", t.price);
        printf("  DAILY SCHEDULE: ");
        for (int i = 0; i < 7; i++)
            if (t.in_schedule[i])
                printf("%s ", WEEK_DAY_NAME[i]);
        putchar('\n');
    } else if (mode == CLEAN) {
        printf("  %s   %s   %s%s     %s%s         %u\t", t.id, t.from, ((strlen(t.from) > 8) ? "" : "   "), t.to, ((strlen(t.to) > 8) ? "" : "  "), (t.carrier == AIR) ? "PLANE" : "RAIL", t.price);
        print_hour_and_minute(t.departure_time, false);
        putchar('\t');
        putchar('\t');
        print_hour_and_minute(t.arrival_time, false);
        putchar('\t');
        putchar('\t');
        printf("%dd %dh %dm", t.duration.day, t.duration.hour, t.duration.minute);
        //putchar('\t');
        putchar('\t');
        for (int i = 0; i < 7; i++)
            if (t.in_schedule[i])
                printf("%s ", WEEK_DAY_NAME[i]);
        putchar('\n');
    } else {
        raise_error("print_ticket_info", "Wrong printing mode.");
    }
    
    return;
}


void print_time(const TIME t, MODE mode, bool newline)
{
    /**
     * 函数名：print_time
     * 参数：TIME结构体变量t，打印模式mode，bool变量newline表征是否换行
     * 返回值：无
     * 作用：格式化打印时间信息
     */
    
    if (mode == VERBOSE)
        printf("# TIME: Y %d, M %d, D %d, H %d, M %d", t.year, t.month, t.day, t.hour, t.minute);
    else if (mode == CLEAN)
        printf("%d.%2d.%2d %2d:%2d", t.year, t.month, t.day, t.hour, t.minute);
    else
        raise_error("print_time", "Wrong print mode.");
    if (newline) putchar('\n');
    
    return;
}


void print_hour_and_minute(TIME t, bool newline)
{
    /**
     * 函数名：print_hour_and_minute
     * 参数：TIME结构体变量t，bool变量newline表征是否换行
     * 返回值：无
     * 作用：格式化打印时间信息（只打印小时和分钟）
     */
    
    printf("%2d:%2d", t.hour, t.minute);
    if (newline) putchar('\n');
    return;
}


void print_graph(const TRAFFIC_GRAPH G)
{
    /**
     * 函数名：print_graph
     * 作用：打印整张图上所有的票价信息
     */
    
    for (int i = 0; i < MAXNUM; i++)
        if (G.city[i].exist && G.city[i].first_link)
            print_city_link(G.city[i], CLEAN);
    
    return;
}


void print_route(ROUTE R)
{
    /**
     * 函数名：print_route
     * 作用：打印单个路径的全部信息
     */
    
    TICKET_INFO *pti = R.first_ticket_info;
    print_long_line();
    while (pti)
    {
        print_ticket_info(*pti, CLEAN);
        pti = pti->next;
    }
    putchar('\n');
    printf("  DPARTURE: ");
    print_time(R.departure_time, CLEAN, true);
    printf("  ARRIVAL: ");
    print_time(R.arrival_time, CLEAN, true);
    printf("  TOTAL DURATION: ");
    print_time(R.duration, CLEAN, true);
    printf("  ON-ROUTE DURATION: ");
    print_time(R.on_route_duration, CLEAN, true);
    printf("  TRANSFER DURATION: ");
    print_time(R.transfer_duration, CLEAN, true);
    printf("  TRANSFER TIMES: %d\n", R.transfer_num);
    printf("  PRICE: %d\n", R.price);
    
    return;
}


bool assert_time_equal(const TIME t1, const TIME t2)
{
    /**
     * 函数名：assert_time_equal
     * 参数：两个TIME结构体变量
     * 返回值：相等返回true，不等返回false
     * 作用：比较两个TIME是否相等
     */
    
    if (t1.year == t2.year &&
        t1.month == t2.month &&
        t1.day == t2.day &&
        t1.hour == t2.hour &&
        t1.minute == t2.minute)
        return true;
    
    return false;
}


bool assert_ticket_info_same(const TICKET_INFO t1, const TICKET_INFO t2)
{
    /**
     * 函数名：assert_ticket_info_same
     * 参数：两个TICKET_INFO结构体变量
     * 返回值：相等返回true，不等返回false
     * 作用：比较两个TICKET_INFO是否相等
     * 备注：不比较next域
     */
    
    if (strcmp(t1.from, t2.from) || strcmp(t1.to, t2.to)) return false;
    if (t1.carrier != t2.carrier) return false;
    if (!assert_time_equal(t1.departure_time, t2.departure_time)) return false;
    if (!assert_time_equal(t1.arrival_time, t2.arrival_time)) return false;
    if (!assert_time_equal(t1.duration, t2.duration)) return false;
    for (int i = 0; i < 7; i++)
        if (t1.in_schedule[i] != t2.in_schedule[i])
            return false;
    if (t1.price != t2.price) return false;
    
    return true;
}


bool assert_city_name_same(const char *c1, const char *c2)
{
    /**
     * 函数名：assert_city_name_same
     * 作用：判断两个城市的名称是否相同
     */
    
    return (!strcmp(c1, c2));
}


bool time_A_before_time_B(TIME A, TIME B)
{
    /**
     * 函数名：time_A_before_time_B
     * 作用：若时间A在B之前，则返回true，否则返回false
     */
    
    bool year = (A.year == B.year);
    bool month = (A.month == B.month);
    bool day = (A.day == B.day);
    bool hour = (A.hour == B.hour);
    
    if (A.year < B.year) return true;
    if (year && A.month < B.month) return true;
    if (year && month && A.day < B.day) return true;
    if (year && month && day && A.hour < B.hour) return true;
    if (year && month && day && hour && A.minute < B.minute) return true;
    
    return false;
}


bool is_leap_year(unsigned year)
{
    /**
     * 函数名：is_leap_year
     * 作用：判断闰年
     */
    
    if (year % 400 == 0) return true;
    if (year % 100 == 0) return false;
    if (year % 4 == 0) return true;
    return false;
}


void init_time(TIME *p)
{
    p->year = p->month = p->day = p->hour = p->minute = 0;
    return;
}


void add_one_day(TIME *pt)
{
    /**
     * 函数名：add_one_day
     * 作用：在原先的日期上加上一天，考虑闰年2月29天的情况
     */
    
    pt->day++;
    if (pt->day > month_day[pt->month])
    {
        if (is_leap_year(pt->year) && pt->month == FEBURARY && pt->day == 29) return;
        if (is_leap_year(pt->year) && pt->month == FEBURARY && pt->day == 30)
            pt->day--;
        pt->day -= month_day[pt->month];
        pt->month++;
        if (pt->month > 12)
        {
            pt->month -= 12;
            pt->year++;
        }
    }
    
    return;
}


unsigned time_subtraction(TIME ta, TIME tb, TIME *ptc)
{
    /**
     * 函数名：time_subtraction
     * 参数：两个TIME类型结构体变量ta, tb和一个指向TIME结构体的指针ptc
     * 返回值：int状态值，1为出错，0为正常
     * 作用：时间减法，ta - tb = *ptc
     * 备注：由于本项目中不会出现两个时间相差一个月以上的情况，故若出现时间差大于1个月，则报错
     */
    
    ptc->minute = ta.minute - tb.minute;
    if (ptc->minute < 0) {ptc->minute += 60; ta.hour--;}
    ptc->hour = ta.hour - tb.hour;
    if (ptc->hour < 0) {ptc->hour += 24; ta.day--;}
    ptc->day = ta.day - tb.day;
    if (ptc->day < 0) {ptc->day += month_day[ta.month]; ta.month--;}
    ptc->month = ta.month - tb.month;
    if (ptc->month < 0) {ptc->month += 12; ta.year--;}
    ptc->year = ta.year - tb.year;
    if (ptc->year < 0)
    {
        //raise_error("time_subtraction", "Time ta comes before time tb. Failure in subtraction.");
        return 1;
    }
    if (ptc->month)
    {
        raise_error("time_subtraction", "This function only computes time difference less \
                    than 1 month, since no train/air traffic will cost more than 1 month within China.");
        return 1;
    }
    return 0;
}


unsigned time_addition(TIME ta, TIME tb, TIME *ptc)
{
    /**
     * 函数名：time_addition
     * 参数：两个TIME类型结构体变量ta, tb和一个指向TIME结构体的指针ptc
     * 返回值：int状态值，1为出错，0为正常
     * 作用：时间加法，ta + tb = *ptc
     */

    ptc->year = ptc->month = ptc->day = ptc->hour = ptc->minute = 0;
    
    ptc->minute = ta.minute + tb.minute;
    if (ptc->minute >= 60)
    {
        ptc->minute -= 60;
        ptc->hour++;
    }
    
    ptc->hour += ta.hour + tb.hour;
    if (ptc->hour >= 24)
    {
        ptc->hour -= 24;
        ptc->day++;
    }
    
    ptc->day += ta.day + tb.day;
    ptc->month += ta.month + tb.month;
    if (ptc->day > month_day[ptc->month])
    {
        ptc->day -= month_day[ptc->month];
        if (is_leap_year(ptc->year) && ptc->month == FEBURARY) ptc->day--;
        ptc->month++;
    }
    
    
    if (ptc->month > 12)
    {
        ptc->month -= 12;
        ptc->year++;
    }
    
    ptc->year += ta.year + tb.year;
    
    return 0;
}


WEEK_DAY time_to_week_day(TIME t)
{
    /**
     * 函数名：time_to_week_day
     * 参数：TIME结构体变量t
     * 作用：由时间求得星期几
     */
    
    TIME anchor_2020 = {2020, 3, 2, 0, 0};
    
    unsigned delta_day = 0;
    
    if (t.year > anchor_2020.year || t.month > anchor_2020.month)
    {
        delta_day += month_day[anchor_2020.month] - 2;
        delta_day += t.day;
    } else {
        delta_day += t.day - anchor_2020.day;
    }
    
    delta_day += (t.year - anchor_2020.year) * 365;
    
    for (unsigned year = anchor_2020.year + 1; year <= t.year - 1; year++)
        if (is_leap_year(year)) delta_day++;
    if (is_leap_year(t.year) && t.year > anchor_2020.year && (t.month > FEBURARY || (t.month == FEBURARY && t.day == 29)))
        delta_day++;
    
    for (unsigned month = anchor_2020.month + 1; month < t.month; month++)
        delta_day += month_day[month];
    
    return (WEEK_DAY)(delta_day % 7 + MON);
}
