/*------------------------------------------------
    作者: ZZY YBR
    日期: 2020.6.10
    文件名: test.c
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: 测试函数，实际应用的时候不会用到
 
    v1.1: 完成路线搜索、排序功能
    v1.2: 完成终端Interface 20200616
    v1.3: 文件输入完成 20200617
------------------------------------------------*/

#include "head_file.h"

extern const char *WEEK_DAY_NAME[7];

void test_print_ticket_info()
{
    /**
     * 函数名：test_print_ticket_info
     * 作用：测试用
     */
    
    TIME t1 = {2020, 10, 10, 10, 10};
    TIME t2 = {2020, 10, 10, 10, 10};
    
    TICKET_INFO *t = get_ticket_info("MU2871", "nanjing", "beijing", AIR, t1, t2, 1000);
    t->in_schedule[SUN] = true;
    printf("  FROM\t\tTO\tCARRIER\tPRICE\tDEPARTURE\t\tARRIVAL\t\t\tSCHEDULE\n");
    print_long_line();
    print_ticket_info(*t, CLEAN);
    
    return;
}


void test_user_input_from_keyboard()
{
    /**
     * 函数名：test_user_input_from_keyboard
     * 作用：测试用
     */
    
    // test examples
    // 2020.10.10 11:11
    // 2020.6.10 01:01
    
    USER_QUERY u = get_user_query_from_keyboard();
    print_user_query(u);
    return;
}


void test_time()
{
    /**
     * 函数名：test_time
     * 作用：测试用
     */
    
    TIME ta, tb, tc;
    
    ta.year = 2020;
    ta.month = MAY;
    ta.day = 31;
    ta.hour = 12;
    ta.minute = 56;
    tb.year = 2020;
    tb.month = APRIL;
    tb.day = 30;
    tb.hour = 13;
    tb.minute = 45;
    
    time_subtraction(ta, tb, &tc);
    print_time(tc, VERBOSE, true);
    
    return;
}


void test_city_link()
{
    /**
     * 函数名：test_city_link
     * 作用：测试用
     */
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    CITY_BOX *c = get_city_box("nanjing", true);
    
    if (!insert_new_city(&G, *c))
    {
        raise_error("test_city_link", "Fail to insert a new city.");
        return;
    }
    
    print_city_link(G.city[city_to_index("nanjing")], CLEAN);
    
    return;
}


void test_insert_new_ticket_info()
{
    /**
     * 函数名：test_insert_new_ticket_info
     * 作用：测试用
     */
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    CITY_BOX *c = get_city_box("nanjing", true);
    
    if (!insert_new_city(&G, *c))
    {
        raise_error("test_city_link", "Fail to insert a new city.");
        return;
    }
    
    TIME t1 = {2020, 10, 10, 10, 10};
    TIME t2 = {2020, 10, 10, 10, 10};
    
    TICKET_INFO *t_info_1 = get_ticket_info("test", "nanjing", "beijing", AIR, t1, t2, 1000);
    t_info_1->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_2 = get_ticket_info("test", "nanjing", "shanghai", RAIL, t1, t2, 1000);
    t_info_2->in_schedule[MON] = t_info_2->in_schedule[WED] = true;
    
    TICKET_INFO *t_info_3 = get_ticket_info("test", "nanjing", "shanghai", AIR, t1, t2, 1000);
    t_info_3->in_schedule[MON] = t_info_3->in_schedule[WED] = true;

    TICKET_INFO *t_info_4 = get_ticket_info("test", "beijing", "shanghai", AIR, t1, t2, 800);
    t_info_4->in_schedule[TUE] = t_info_4->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_5 = get_ticket_info("test", "beijing", "shanghai", AIR, t1, t2, 800);
    t_info_5->in_schedule[TUE] = t_info_5->in_schedule[SUN] = true;
    
    insert_new_ticket_info(&G, *t_info_1);
    insert_new_ticket_info(&G, *t_info_2);
    insert_new_ticket_info(&G, *t_info_3);
    insert_new_ticket_info(&G, *t_info_4);
    insert_new_ticket_info(&G, *t_info_5);
    //print_city_link(G.city[city_to_index("beijing")], CLEAN);
    print_graph(G);
    printf("city_num: %d\n", G.city_num);
    
    return;
}


void test_delete_ticket_info()
{
    /**
     * 函数名：test_delete_new_ticket_info
     * 作用：测试用
     */
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    
    TIME t1 = {2020, 10, 10, 10, 10};
    TIME t2 = {2020, 10, 11, 12, 30};
    TIME t3 = {2020, 10, 12, 13, 10};
    
    TICKET_INFO *t_info_1 = get_ticket_info("test", "nanjing", "beijing", AIR, t1, t2, 1000);
    t_info_1->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_2 = get_ticket_info("test", "nanjing", "shanghai", RAIL, t1, t2, 1000);
    t_info_2->in_schedule[MON] = t_info_2->in_schedule[WED] = true;
    
    TICKET_INFO *t_info_3 = get_ticket_info("test", "nanjing", "shanghai", AIR, t1, t2, 1000);
    t_info_3->in_schedule[MON] = t_info_3->in_schedule[WED] = true;

    TICKET_INFO *t_info_4 = get_ticket_info("test", "beijing", "shanghai", AIR, t2, t3, 800);
    t_info_4->in_schedule[TUE] = t_info_4->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_5 = get_ticket_info("test", "beijing", "shanghai", AIR, t1, t2, 800);
    t_info_5->in_schedule[TUE] = t_info_5->in_schedule[SUN] = true;
    
    insert_new_ticket_info(&G, *t_info_1);
    insert_new_ticket_info(&G, *t_info_2);
    insert_new_ticket_info(&G, *t_info_3);
    insert_new_ticket_info(&G, *t_info_4);
    insert_new_ticket_info(&G, *t_info_5);
    delete_ticket_info(&G, *t_info_1);
    delete_ticket_info(&G, *t_info_2);
    //delete_ticket_info(&G, *t_info_3);
    print_graph(G);
    calculate_city_num(&G);
    printf("city_num: %d\n", G.city_num);
    
    return;
}

void test_get_next_ticket_info()
{
    /**
     * 函数名：test_get_next_ticket_info
     * 作用：测试用
     */
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    
    TIME t1 = {0, 0, 0, 10, 10};
    TIME t2 = {0, 0, 0, 12, 30};
    TIME t3 = {0, 0, 0, 13, 10};
    
    TICKET_INFO *t_info_1 = get_ticket_info("test", "nanjing", "beijing", AIR, t1, t2, 1000);
    t_info_1->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_2 = get_ticket_info("test", "nanjing", "shanghai", RAIL, t1, t2, 1000);
    t_info_2->in_schedule[MON] = t_info_2->in_schedule[WED] = true;
    
    TICKET_INFO *t_info_3 = get_ticket_info("test", "nanjing", "shanghai", AIR, t1, t2, 1000);
    t_info_3->in_schedule[MON] = t_info_3->in_schedule[WED] = true;

    TICKET_INFO *t_info_4 = get_ticket_info("test", "beijing", "shanghai", AIR, t2, t3, 800);
    t_info_4->in_schedule[TUE] = t_info_4->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_5 = get_ticket_info("test", "beijing", "shanghai", AIR, t1, t2, 800);
    t_info_5->in_schedule[TUE] = t_info_5->in_schedule[SUN] = true;
    
    insert_new_ticket_info(&G, *t_info_1);
    insert_new_ticket_info(&G, *t_info_2);
    insert_new_ticket_info(&G, *t_info_3);
    insert_new_ticket_info(&G, *t_info_4);
    insert_new_ticket_info(&G, *t_info_5);
    
    print_graph(G);
    
    print_long_line();
    printf("NEXT TICKET_INFO:\n");
    TICKET_INFO *p = get_next_ticket_info(G, "nanjing", *t_info_1);
    //print_ticket_info(*t_info_5, CLEAN);
    if (p) print_ticket_info(*p, CLEAN);
    
    return;
}


void test_time_to_week_day()
{
    /**
     * 函数名：test_time_to_week_day
     * 作用：测试用
     */
    
    TIME t = {2020, 6, 14, 0, 0};
    printf("%s\n", WEEK_DAY_NAME[time_to_week_day(t)]);
    return;
}


void test_find_route()
{
    /**
     * 函数名：test_find_route
     * 作用：测试用
     */
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    
//    TIME t1 = {2020, 6, 14, 10, 10};
//    TIME t2 = {2020, 6, 14, 12, 30};
//    TIME t3 = {2020, 6, 14, 13, 10};
//    TIME t4 = {2020, 6, 14, 15, 30};
//    TIME t5 = {2020, 6, 14, 20, 30};
//    TIME t6 = {2020, 6, 14, 21, 50};
//    TIME t7 = {2020, 6, 14, 22, 50};
    TIME t1 = {0, 0, 0, 10, 10};
    TIME t2 = {0, 0, 0, 12, 30};
    TIME t3 = {0, 0, 0, 13, 10};
    TIME t4 = {0, 0, 0, 15, 30};
    TIME t5 = {0, 0, 0, 20, 30};
    TIME t6 = {0, 0, 0, 21, 50};
    TIME t7 = {0, 0, 0, 22, 50};
    TIME t8 = {0, 0, 0, 23, 10};
    TIME t9 = {0, 0, 0, 0, 10};
    
//    TICKET_INFO *t_info_1 = get_ticket_info("CA1811", "nanjing", "beijing", AIR, t1, t2, 1000);
//    t_info_1->in_schedule[SUN] = true;
    TICKET_INFO *t_info_1 = get_ticket_info("CA1811", "nanjing", "beijing", AIR, t1, t2, 1000);
    t_info_1->in_schedule[MON] = true;
    
    TICKET_INFO *t_info_2 = get_ticket_info("MU2882", "nanjing", "shanghai", RAIL, t1, t2, 1000);
    t_info_2->in_schedule[MON] = t_info_2->in_schedule[WED] = t_info_2->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_3 = get_ticket_info("MU2884", "nanjing", "shanghai", AIR, t1, t2, 1000);
    t_info_3->in_schedule[MON] = t_info_3->in_schedule[WED] = t_info_3->in_schedule[SUN] = true;

//    TICKET_INFO *t_info_4 = get_ticket_info("MU5100", "beijing", "shanghai", AIR, t2, t3, 800);
//    t_info_4->in_schedule[TUE] = t_info_4->in_schedule[SUN] = true;
    TICKET_INFO *t_info_4 = get_ticket_info("MU5100", "beijing", "shanghai", AIR, t8, t9, 800);
    t_info_4->in_schedule[MON] = t_info_4->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_5 = get_ticket_info("MU5101", "shanghai", "beijing", AIR, t5, t6, 800);
    t_info_5->in_schedule[TUE] = t_info_5->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_6 = get_ticket_info("MU7878", "shanghai", "tianjin", AIR, t3, t4, 800);
    t_info_6->in_schedule[TUE] = t_info_6->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_7 = get_ticket_info("CZ1561", "tianjin", "beijing", AIR, t5, t6, 800);
    t_info_7->in_schedule[TUE] = t_info_7->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_8 = get_ticket_info("HU7878", "beijing", "nanjing", AIR, t4, t5, 800);
    t_info_8->in_schedule[TUE] = t_info_8->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_9 = get_ticket_info("HU9898", "nanjing", "shenzhen", AIR, t4, t5, 800);
    t_info_9->in_schedule[WED] = t_info_9->in_schedule[SUN] = true;

    TICKET_INFO *t_info_10 = get_ticket_info("T1627", "baoji", "taian", RAIL, t1, t2, 1000);
    t_info_10->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_11 = get_ticket_info("K8192", "baoji", "hefei", RAIL, t1, t2, 500);
    t_info_11->in_schedule[MON] = t_info_11->in_schedule[WED] = true;
    
    TICKET_INFO *t_info_12 = get_ticket_info("K1829", "hefei", "xvzhou", RAIL, t2, t3, 700);
    t_info_12->in_schedule[MON] = t_info_12->in_schedule[WED] = true;

    TICKET_INFO *t_info_13 = get_ticket_info("T1572", "xvzhou", "taian", RAIL, t3, t4, 600);
    t_info_13->in_schedule[TUE] = t_info_13->in_schedule[SUN] = true;
    //==========================================================================

    TICKET_INFO *t_info_14 = get_ticket_info("MU5697", "jinan", "linyi", AIR, t1, t2, 1000);
    t_info_14->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_15 = get_ticket_info("D6128", "weihai", "qingdao", RAIL, t1, t2, 1000);
    t_info_15->in_schedule[MON] = t_info_15->in_schedule[WED] = true;
    
    TICKET_INFO *t_info_16 = get_ticket_info("HU7182", "jinan", "rizhao", AIR, t1, t2, 1000);
    t_info_16->in_schedule[MON] = t_info_16->in_schedule[WED] = true;

    TICKET_INFO *t_info_17 = get_ticket_info("CZ8179", "rizhao", "linyi", AIR, t2, t3, 800);
    t_info_17->in_schedule[TUE] = t_info_17->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_18 = get_ticket_info("CA1728", "linyi", "rizhao", AIR, t1, t2, 800);
    t_info_18->in_schedule[TUE] = t_info_18->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_19 = get_ticket_info("MU5141", "jinan", "weihai", AIR, t3, t4, 800);
    t_info_19->in_schedule[TUE] = t_info_19->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_20 = get_ticket_info("CA1672", "weihai", "weifang", AIR, t4, t5, 800);
    t_info_20->in_schedule[TUE] = t_info_20->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_21 = get_ticket_info("HU1728", "weifang", "linyi", AIR, t6, t7, 800);
    t_info_21->in_schedule[TUE] = t_info_21->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_22 = get_ticket_info("MU7812", "liaocheng", "linyi", AIR, t4, t5, 800);
    t_info_22->in_schedule[WED] = t_info_22->in_schedule[SUN] = true;
    
    TICKET_INFO *t_info_23 = get_ticket_info("CA1813", "nanjing", "beijing", AIR, t1, t3, 2000);
    t_info_23->in_schedule[SUN] = true;
    
    insert_new_ticket_info(&G, *t_info_1);
    insert_new_ticket_info(&G, *t_info_2);
    insert_new_ticket_info(&G, *t_info_3);
    insert_new_ticket_info(&G, *t_info_4);
    insert_new_ticket_info(&G, *t_info_5);
    insert_new_ticket_info(&G, *t_info_6);
    insert_new_ticket_info(&G, *t_info_7);
    insert_new_ticket_info(&G, *t_info_8);
    insert_new_ticket_info(&G, *t_info_9);
    insert_new_ticket_info(&G, *t_info_10);
    insert_new_ticket_info(&G, *t_info_11);
    insert_new_ticket_info(&G, *t_info_12);
    insert_new_ticket_info(&G, *t_info_13);
    insert_new_ticket_info(&G, *t_info_14);
    insert_new_ticket_info(&G, *t_info_15);
    insert_new_ticket_info(&G, *t_info_16);
    insert_new_ticket_info(&G, *t_info_17);
    insert_new_ticket_info(&G, *t_info_18);
    insert_new_ticket_info(&G, *t_info_19);
    insert_new_ticket_info(&G, *t_info_20);
    insert_new_ticket_info(&G, *t_info_21);
    insert_new_ticket_info(&G, *t_info_22);
    insert_new_ticket_info(&G, *t_info_23);
    
    print_graph(G);
    
    print_double_long_line();
    
    USER_QUERY u_1 = {"nanjing", "beijing", SPEED, AIR, {2020, 6, 15, 0, 0}, SUN};
//    USER_QUERY u_1 = {"nanjing", "shanghai", SPEED, AIR, {2020, 6, 15, 0, 0}, MON};
    
    USER_QUERY u_9 = {"nanjing", "shanghai", ECON, AIR, {2020, 6, 14, 0, 0}, MON};
    
    /*
    ---------------------------------------------------------------------------------------------------------------
    nanjing    beijing          PLANE    1000       10:10        12:30        0d 2h 20m
    --------------------------------------------------------------------------------------------------------------
    nanjing    shanghai         PLANE    1000       10:10        12:30        0d 2h 20m
    shanghai    beijing         PLANE    800        10:10        12:30        0d 2h 20m
    ---------------------------------------------------------------------------------------------------------------
    nanjing     shanghai            PLANE    1000       10:10        12:30        0d 2h 20m
    shanghai    tianjin             PLANE    800        13:10        15:30        0d 2h 20m
    tianjin     beijing             PLANE    800        15:30        20:30        0d 5h 0m
     */
    
    USER_QUERY u_2 = {"shanghai", "shenzhen", ECON, AIR, {0, 0, 0, 0, 0}};
    /*
    shanghai    beijing         PLANE    800    10:10        12:30        0d 2h 20m
    beijing     nanjing         PLANE    800    15:30        20:30        0d 5h 0m
    nanjing     shenzhen        PLANE    800    15:30        20:30        0d 5h 0m
     */
    
    
    USER_QUERY u_3 = {"shanghai", "shenzhen", ECON, RAIL, {0, 0, 0, 0, 0}};

    USER_QUERY u_4 = {"baoji", "taian", ECON, RAIL, {0, 0, 0, 0, 0}};
    /* pass
    baoji   taian   TRAIN   1000    10:10   12:30   0d 2h 20m
    ---------------------------------------------------------------------------------------------------------------
    baoji   hefei   TRAIN   500     10:10   12:30   0d 2h 20m
    hefei   xvzhou  TRAIN   700     12:30   13:10   0d 2h 20m
    xvzhou  taian   TRAIN   600     13:10   15:30   0d 2h 20m
     */
    
    USER_QUERY u_5 = {"baoji", "hefei", ECON, RAIL, {0, 0, 0, 0, 0}};
    /* pass
    baoji   hefei   TRAIN   500     10:10   12:30   0d 2h 20m
     */
    
    USER_QUERY u_6 = {"hefei", "xvzhou", ECON, RAIL, {0, 0, 0, 0, 0}};
    /* pass
    hefei   xvzhou  TRAIN   700     12:30   13:10   0d 2h 20m
     */

    USER_QUERY u_7 = {"xvzhou", "taian", ECON, RAIL, {0, 0, 0, 0, 0}};
    /* pass
    xvzhou  taian   TRAIN   600     13:10   15:30   0d 2h 20m
     */

    USER_QUERY u_8 = {"jinan", "linyi", ECON, AIR, {0, 0, 0, 0, 0}};
    /* pass
    jinan   linyi   PLANE   1000    10:10   12:30   0d 2h 20m
    ---------------------------------------------------------------------------
    jinan   rizhao  PLANE   1000    10:10   12:30   0d 2h 20m
    rizhao  linyi   PLANE   1000    12:30   13:10   0d 2h 20m
    ---------------------------------------------------------------------------
    jinan   weihai  PLANE   800     13:10   15:30   0d 2h 20m
    weihai  weifang PLANE   800     15:30   20:30   0d 5h 0m
    weifang linyi   PLANE   800     20:30   22:50   0d 2h 20m
     */
    
    print_user_query(u_1);
    
    ROUTE *pR = (ROUTE *)malloc(10 * sizeof(ROUTE));
    
    unsigned num_found = find_route(G, u_1, pR);
    
    printf("FIND %d ROUTES:\n", num_found);
    
    
    for (int i = 0; i < num_found; i++)
        print_route(*(pR + i));
    return;
}


void test_city_to_index()
{
    /**
     * 函数名：test_city_to_index
     * 作用：测试用
     */
    
    char *nanjing = "nanjing";
    printf("%d\n", city_to_index(nanjing));
    char *beijing = "beijing";
    printf("%d\n", city_to_index(beijing));
    char *hefei = "hefei";
    printf("%d\n", city_to_index(hefei));
    char *shanghai = "shanghai";
    printf("%d\n", city_to_index(shanghai));
    char *shenzhen = "shenzhen";
    printf("%d\n", city_to_index(shenzhen));
    char *guangzhou = "guangzhou";
    printf("%d\n", city_to_index(guangzhou));
    char *taian = "taian";
    printf("%d\n", city_to_index(taian));
    char *tianjin = "tianjin";
    printf("%d\n", city_to_index(tianjin));
    char *taibei = "taibei";
    printf("%d\n", city_to_index(taibei));
    char *chengdu = "chengdu";
    printf("%d\n", city_to_index(chengdu));
    char *baoji = "baoji";
    printf("%d\n", city_to_index(baoji));
    char *taiyuan = "taiyuan";
    printf("%d\n", city_to_index(taiyuan));
    char *shijiazhuang = "shijiazhuang";
    printf("%d\n", city_to_index(shijiazhuang));
    
    return;
}


void test_add_ticket_info_from_txt()
{
    /**
     * 函数名：test_add_ticket_info_from_txt
     * 作用：测试用
     */
    
    char *s = "/Users/zhangzy/Desktop/学习资源/2019-2020 大二下/2019-2020 数据结构/Data-Structure-Homework/2019-2020 数据结构大作业/Data-Structure-Final/交通咨询/input_test.txt";      // 输入文件的绝对路径
    
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    add_ticket_info_from_txt(&G, s);
    print_graph(G);
    
    return;
}


void test_add_one_day()
{
    /**
     * 函数名：test_add_one_day
     * 作用：测试用
     */
    
    TIME t = {2020, 2, 28, 0, 0};
    printf("Original time:\n  ");
    print_time(t, CLEAN, true);
    add_one_day(&t);
    printf("Add one day:\n  ");
    print_time(t, CLEAN, true);
    add_one_day(&t);
    printf("Add one day again:\n  ");
    print_time(t, CLEAN, true);
    return;
}


void test_get_city_link_num()
{
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    
    TIME t1 = {0, 0, 0, 10, 10};
    TIME t2 = {0, 0, 0, 12, 30};

    TICKET_INFO *t_info_1 = get_ticket_info("CA1811", "nanjing", "beijing", AIR, t1, t2, 1000);
    t_info_1->in_schedule[MON] = true;
        
    TICKET_INFO *t_info_2 = get_ticket_info("MU2882", "nanjing", "shanghai", RAIL, t1, t2, 1000);
    t_info_2->in_schedule[MON] = t_info_2->in_schedule[WED] = t_info_2->in_schedule[SUN] = true;
    
    insert_new_ticket_info(&G, *t_info_1);
    insert_new_ticket_info(&G, *t_info_2);
    
//    get_city_link_num(&G, "nanjing");
    return;
}


void test_get_ticket_info_num()
{
    TRAFFIC_GRAPH G;
    init_traffic_graph(&G);
    
    add_ticket_info_from_txt(&G, "/Users/zhangzy/Desktop/学习资源/2019-2020 大二下/2019-2020 数据结构/Data-Structure-Homework/2019-2020 数据结构大作业/Data-Structure-Final/交通咨询/input_test.txt");
    get_ticket_info_num(G.city[city_to_index("guangzhou")].first_link->first_air_ticket);
    TICKET_INFO *pti = G.city[city_to_index("guangzhou")].first_link->first_air_ticket;
    while (pti)
    {
        printf("%s\n", pti->to);
        pti = pti->next;
    }
}
