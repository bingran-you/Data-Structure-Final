/*------------------------------------------------
    作者: ZZY
    日期: 2020.6.8
    文件名: interface.c
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: 交互界面相关
 
    v1.1: 完成路线搜索、排序功能
    v1.2: 完成终端Interface 20200616
    v1.3: 文件输入完成 20200617
------------------------------------------------*/

#include "head_file.h"

extern unsigned int month_day[13];
extern const char *WEEK_DAY_NAME[7];

USER_QUERY get_user_query_from_keyboard()
{
    /**
     * 函数名：get_user_input_from_keyboard
     * 参数：无
     * 返回值：USER_INPUT结构体变量，包含用户输入的信息
     * 作用：从键盘输入中提取信息
     */
    
    char s[MAXLEN];
    USER_QUERY u;
    u.from = (char *)malloc(MAXLEN);
    u.to = (char *)malloc(MAXLEN);
    
    printf("* FROM:\n  ");
    scanf("%s", u.from);
    string_to_lower_case(u.from);
    
    printf("* TO:\n  ");
    scanf("%s", u.to);
    string_to_lower_case(u.to);
    
    printf("* PRIORITY:\n");
ENTER_PRIORITY:
    printf("  enter 's' for speed priority -- the faster the better\n");
    printf("  enter 'c' for cost priority -- the cheaper the better\n");
    printf("  enter 'd' for direct route first\n");
    printf("  ");
    scanf("%s", s);
    string_to_lower_case(s);
    if (strcmp(s, "c") == 0) u.priority = ECON;
    else if (strcmp(s, "s") == 0) u.priority = SPEED;
    else if (strcmp(s, "d") == 0) u.priority = DIRECT;
    else {
        raise_error("get_user_input_from_keyboard", "Sorry, invalid PRIORITY mode. \nPlease enter again:\n");
        goto ENTER_PRIORITY;
    }

    printf("* CARRIER:\n");
ENTER_CARRIER:
    printf("  enter 'p' for plane tickets\n");
    printf("  enter 't' for train tickets\n");
    printf("  ");
    scanf("%s", s);
    if (strcmp(s, "p") == 0) u.carrier = AIR;
    else if (strcmp(s, "t") == 0) u.carrier = RAIL;
    else {
        raise_error("get_user_input_from_keyboard", "Sorry, invalid CARRIER mode. \nPlease enter again:\n");
        goto ENTER_CARRIER;
    }
    
ENTER_TIME:
    printf("* DEPARTURE TIME:\n");
    printf("  time format: YYYY.MM.DD hh:mm\n  ");
    fflush(stdin);
    while (get_time_from_keyboard(&u.departure)) {fflush(stdin); printf("  ");}
    
    u.travelling_week_day = time_to_week_day(u.departure);
    
    return u;
}


int get_time_from_keyboard(TIME *t)
{
    /**
     * 函数名：get_time_from_keyboard
     * 参数：TIME *t，将从输入中得到的时间信息保存在t指向的TIME结构体变量中
     * 返回值：状态，1表示格式错误，需要重新输入；0表示一切正常
     * 作用：从输入中得到格式化的时间
     */
    
    char c;
    t->year = t->month = t->day = t->hour = t->minute = 0;
    
    c = getchar();
    
    // year
    while (isdigit(c)) {t->year = t->year * 10 + c - '0'; c = getchar();}
    if (t->year < 2020)
    {
        raise_error("get_time_from_keyboard", "You cannot go back to time before 2020.");
        return 1;
    }
    if (c == '.') c = getchar();
    else {raise_error("get_time_from_keyboard", "Wrong time format"); return 1;}
    
    // month
    while (isdigit(c)) {t->month = t->month * 10 + c - '0'; c = getchar();}
    if (t->month > 12 || t->month < 1)
    {
        raise_error("get_time_from_keyboard", "Wrong month input.");
        return 1;
    }
    if (c == '.') c = getchar();
    else {raise_error("get_time_from_keyboard", "Wrong time format"); return 1;}
    
    // day
    while (isdigit(c)) {t->day = t->day * 10 + c - '0'; c = getchar();}
    if (t->day < 1 || t->day > month_day[t->month])
    {
        raise_error("get_time_from_keyboard", "Wrong day input.");
        return 1;
    }
    if (c == ' ') c = getchar();
    else {raise_error("get_time_from_keyboard", "Wrong time format"); return 1;}
    
    // hour
    while (isdigit(c)) {t->hour = t->hour * 10 + c - '0'; c = getchar();}
    if (t->hour < 0 || t->hour >= 24)
    {
        raise_error("get_time_from_keyboard", "Wrong hour input");
        return 1;
    }
    if (c == ':') c = getchar();
    else {raise_error("get_time_from_keyboard", "Wrong time format"); return 1;}
    
    // minute
    while (isdigit(c)) {t->minute = t->minute * 10 + c - '0'; c = getchar();}
    if (t->minute < 0 || t->minute >= 60)
    {
        raise_error("get_time_from_keyboard", "Wrong minute input");
        return 1;
    }
    
    return 0;
}


int get_schedule_time_from_keyboard(TIME *t)
{
    /**
     * 函数名：get_schedule_time_from_keyboard
     * 参数：TIME *t，将从输入中得到的时间信息保存在t指向的TIME结构体变量中，排班信息中的时间只精确到小时
     * 返回值：状态，1表示格式错误，需要重新输入；0表示一切正常
     * 作用：从输入中得到格式化的时间
     */
    
    char c;
    t->year = t->month = t->day = t->hour = t->minute = 0;
    
    c = getchar();
    
    // hour
    while (isdigit(c)) {t->hour = t->hour * 10 + c - '0'; c = getchar();}
    if (t->hour < 0 || t->hour >= 24)
    {
        raise_error("get_time_from_keyboard", "Wrong hour input");
        return 1;
    }
    if (c == ':') c = getchar();
    else {raise_error("get_time_from_keyboard", "Wrong time format"); return 1;}
    
    // minute
    while (isdigit(c)) {t->minute = t->minute * 10 + c - '0'; c = getchar();}
    if (t->minute < 0 || t->minute >= 60)
    {
        raise_error("get_time_from_keyboard", "Wrong minute input");
        return 1;
    }
    
    return 0;
}


void fill_schedule_from_input(TICKET_INFO *p)
{
    /**
     * 函数名： fill_schedule_from_input
     * 参数：TICKET_INFO *p，将从输入中得到的班次信息存入p所指向的TICKET_INFO结构体的in_schedule域中
     * 作用：从输入中得到班次信息
     */
    
    char c;
    while ((c = getchar()) != EOF && c != '\n')
        if (isdigit(c)) p->in_schedule[c - '0' - 1] = true;
    return;
}


void print_interface_header()
{
    /**
     * 函数名：print_interface_header
     * 参数：无
     * 返回值：无
     * 作用：打印程序头，包含合作者信息等
     */
    
    system("clear");
    print_line();
    printf("TRANSPORTATION QUERY SYSTEM\n");
    print_line();
}


void print_user_query(USER_QUERY u)
{
    /**
     * 函数名：print_user_input
     * 参数：USER_INPUT u，包含用户输入信息的结构体变量
     * 返回值：无
     * 作用：打印用户输入的信息
     */
    
    if (!u.from || !u.to) {raise_error("print_user_input", "Invalid city name."); return;}
    
    print_line();
    printf("USER TRAVELLING INFO\n");
    print_line();
    printf("FROM:\t\t%s\n", u.from);
    printf("TO:\t\t%s\n", u.to);
    if (u.priority != ECON && u.priority != SPEED && u.priority != DIRECT)
    {
        raise_error("print_user_input", "Invalid PRIORITY mode.");
        return;
    }
    printf("PRIORITY:\t%s\n", (u.priority == ECON) ? "ECON" :
                              (u.priority == SPEED) ? "SPEED" : "DIRECT");
    printf("CARRIER:\t%s\n", (u.carrier == AIR) ? "AIR" : "RAIL");
    printf("DEPARTURE AFTER: ");
    print_time(u.departure, CLEAN, true);
    printf("TRAVELLING WEEK DAY: %s\n", WEEK_DAY_NAME[u.travelling_week_day]);

    print_line();
    
    return;
}


void print_usage()
{
    /**
     * 函数名：print_usage
     * 作用：提示系统使用方法
     */
    
    printf("# ENTER\n");
    printf("  'a' to add a new ticket info in the graph.\n");
    printf("  'd' to delete an existed ticket info from the graph.\n");
    printf("  's' to search a traffic route arrangement.\n");
    printf("  'p' to print the whole traffic graph.\n");
    printf("  'f' to add traffic information from txt file.\n");
    printf("  'q' to quit the system.\n");
    
    return;
}


void interface_end()
{
    /**
     * 函数名：interface_end
     * 作用：退出系统的提示
     */
    
    printf("# YOU HAVE QUITED THE PROGRAMM.\n");
    return;
}


bool interface_del_ticket_info(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：interface_del_ticket_info
     * 作用：交互界面中当用户要求删除已有的票价信息时，进入该函数进行处理
     */
    
    if (!pG) {raise_error("interface_del_ticket_info", "Graph not exists."); return ERROR;}
    printf("# ENTER TICKET INFO:\n");
    
    char *t = (char *)malloc(MAXLEN);
    TICKET_INFO t_info;
    init_ticket_info(&t_info);
    
    printf("* FROM:\n  ");
    if (!scanf("%s", t)) return false;
    strcpy(t_info.from, t);
    
    printf("* TO:\n  ");
    if (!scanf("%s", t)) return false;
    strcpy(t_info.to, t);
    
ENTER_CARRIER:
    printf("* PLANE OR TRAIN: \n");
    printf("  enter 'p' for plane tickets\n");
    printf("  enter 't' for train tickets\n");
    printf("  ");
    scanf("%s", t);
    if (strcmp(t, "p") == 0) t_info.carrier = AIR;
    else if (strcmp(t, "t") == 0) t_info.carrier = RAIL;
    else {
        raise_error("get_user_input_from_keyboard", "Sorry, invalid CARRIER mode. \nPlease enter again:\n");
        goto ENTER_CARRIER;
    }
    
    printf("* FLIGHT/TRAIN NUMBER:\n  ");
    if (!scanf("%s", t)) return false;
    strcpy(t_info.id, t);
    
    TIME time = {0, 0, 0, 0, 0};
    TICKET_INFO *pt = get_ticket_info(t_info.id, t_info.from, t_info.to, t_info.carrier, time, time, 0);
    
    delete_ticket_info(pG, *pt);
    
    return true;
}


bool interface_add_ticket_info(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：interface_add_ticket_info
     * 作用：交互界面中当用户要求添加新的票价信息时，进入该函数进行处理
     */
    
    if (!pG) {raise_error("interface_add_ticket_info", "Graph not exists."); return ERROR;}
    
    printf("# ENTER NEW TICKET INFO:\n");
    
    char *t = (char *)malloc(MAXLEN);
    TICKET_INFO t_info;
    init_ticket_info(&t_info);
    
    printf("* FROM:\n  ");
    if (!scanf("%s", t)) return false;
    strcpy(t_info.from, t);
    
    printf("* TO:\n  ");
    if (!scanf("%s", t)) return false;
    strcpy(t_info.to, t);

ENTER_CARRIER:
    printf("* PLANE OR TRAIN: \n");
    printf("  enter 'p' for plane tickets\n");
    printf("  enter 't' for train tickets\n");
    printf("  ");
    scanf("%s", t);
    if (strcmp(t, "p") == 0) t_info.carrier = AIR;
    else if (strcmp(t, "t") == 0) t_info.carrier = RAIL;
    else {
        raise_error("get_user_input_from_keyboard", "Sorry, invalid CARRIER mode. \nPlease enter again:\n");
        goto ENTER_CARRIER;
    }
    
    printf("* FLIGHT/TRAIN NUMBER:\n  ");
    if (!scanf("%s", t)) return false;
    strcpy(t_info.id, t);
    
ENTER_DEPARTURE_TIME:
    printf("* DEPARTURE TIME:\n");
    printf("  time format: hh:mm\n  ");
    fflush(stdin);
    while (get_schedule_time_from_keyboard(&t_info.departure_time)) {fflush(stdin); printf("  ");}

ENTER_ARRIVAL_TIME:
    printf("* ARRIVAL TIME:\n");
    printf("  time format: hh:mm\n  ");
    fflush(stdin);
    while (get_schedule_time_from_keyboard(&t_info.arrival_time)) {fflush(stdin); printf("  ");}
    
    printf("* WEEKLY SCHEDULE:\n  e.g. enter 12 for MON and TUE\n  ");
    char c;
    
    time_subtraction(t_info.arrival_time, t_info.departure_time, &t_info.duration);
    
ENTER_SCHEDULE:
    while ((c = getchar()) != EOF && c != '\n')
    {
        if (!isdigit(c))
        {
            printf("! You should enter digits between 1 and 7.\n# ENTER AGAIN: ");
            goto ENTER_SCHEDULE;
        }
        t_info.in_schedule[c - '0' - 1] = true;
    }

    printf("* PRICE:\n  ");
ENTER_PRICE:
    t_info.price = 0;
    while ((c = getchar()) != EOF && c != '\n')
    {
        if (!isdigit(c))
        {
            printf("! You should enter digits.\n# ENTER AGAIN: ");
            goto ENTER_SCHEDULE;
        }
        t_info.price = t_info.price * 10 + c - '0';
    }
    
    insert_new_ticket_info(pG, t_info);
    
    return true;
}


bool interface_add_ticket_info_from_txt(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：interface_add_ticket_info_from_txt
     * 作用：显示用户从文件中添加交通信息的交互界面
     */
    
    if (!pG) {raise_error("interface_add_ticket_info_from_txt", "Graph not exists."); return ERROR;}
    
    printf("# ENTER TXT FILE NAME (with .txt):\n  ");
    
    char *s = (char *)malloc(MAXLEN);
    char c;
    int i = 0;
    
    fflush(stdin);
    for (i = 0; (c = getchar()) != '\n'; i++)
        s[i] = c;
    s[i] = '\0';
    printf("# READING %s.\n  ", s);
    
    if (!add_ticket_info_from_txt(pG, s)) return false;
    
    return true;
}


void interface()
{
    /**
     * 函数名：interface
     * 作用：终端交互界面接口，启动查询系统
     */
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    
    print_interface_header();
    print_usage();
    printf("# YOUR CHOICE:\n  ");
    
    char *s = (char *)malloc(MAXLEN);
    
    while (scanf("%s", s))
    {
        if (!strcmp(s, "q")) break;
        else if (!strcmp(s, "a")) {
            if (!interface_add_ticket_info(&G))
                printf("! Insert new ticket info failed.\n");
            printf("  ");
            getchar();
            system("clear");
            print_interface_header();
            goto PRINT_USAGE;
        } else if (!strcmp(s, "d")) {
            if (!interface_del_ticket_info(&G))
                printf("! Delete ticket info failed.\n");
            printf("  ");
            getchar();
            system("clear");
            print_interface_header();
            goto PRINT_USAGE;
        } else if (!strcmp(s, "s")) {
            USER_QUERY u = get_user_query_from_keyboard();
            ROUTE *pR = (ROUTE *)malloc(10 * sizeof(ROUTE));
            
            unsigned num_found = find_route(G, u, pR);
            
            printf("FIND %d ROUTES:\n", num_found);
            
            for (int i = 0; i < num_found; i++)
                print_route(*(pR + i));
        } else if (!strcmp(s, "p")) {
            print_graph(G);
        } else if (!strcmp(s, "f")) {
            interface_add_ticket_info_from_txt(&G);
        }
    PRINT_USAGE:
        print_usage();
        printf("# YOUR CHOICE:\n  ");
    }
    
    interface_end();
    
    return;
}
