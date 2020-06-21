/*------------------------------------------------
    作者: ZZY
    日期: 2020.6.8
    文件名: graph.c
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: 交通图操作相关
    
    v1.1: 完成路线搜索、排序功能
    v1.2: 完成终端Interface 20200616
    v1.3: 文件输入完成   
------------------------------------------------*/

#include "head_file.h"

extern const char *WEEK_DAY_NAME[7];

void init_city_box(CITY_BOX *p)
{
    /**
     * 函数名：init_city_box
     * 参数：指向CITY_BOX的指针p
     * 返回值：无
     * 作用：初始化CITY_BOX结构体变量
     */
    
    p->exist = false;
    p->name = NULL;
    p->first_link = NULL;
    return;
}


void init_ticket_info(TICKET_INFO *pt)
{
    /**
     * 函数名：init_ticket_info
     * 参数：指向TICKET_INFO结构的指针p
     * 作用：初始化指针pt指向的TICKET_INFO结构体
     */
    
    pt->from = (char *)malloc(MAXLEN);
    pt->to = (char *)malloc(MAXLEN);
    pt->id = (char *)malloc(MAXLEN);
    pt->carrier = AIR;
    for (int i = 0; i < 7; i++)
        pt->in_schedule[i] = false;
    pt->price = 0;
    pt->departure_time.year = pt->departure_time.month = pt->departure_time.day = pt->departure_time.hour = pt->departure_time.minute = 0;
    pt->arrival_time.year = pt->arrival_time.month = pt->arrival_time.day = pt->arrival_time.hour = pt->arrival_time.minute = 0;
    pt->duration.year = pt->duration.month = pt->duration.day = pt->duration.hour = pt->duration.minute = 0;
    pt->next = NULL;
    
    return;
}


void init_traffic_graph(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：init_traffic_graph
     * 参数：指向TRAFFIC_GRAPH的指针pG
     * 返回值：无
     * 作用：初始化pG指向的TRAFFIC_GRAPH结构体
     */
    
    for (int i = 0; i < MAXNUM; i++)
        init_city_box(&pG->city[i]);
    pG->city_num = 0;
    return;
}


void delete_traffic_graph(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：delete_traffic_graph
     * 参数：指向的指针pG
     * 作用：彻底删除一个已经存在的图，释放内存空间
     */
    
    if (!pG) return;
    free(pG);
    return;
}


void calculate_city_num(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：calculate_city_num
     * 作用：更新图中现存的城市数量
     */
    
    pG->city_num = 0;
    
    for (int i = 0; i < MAXNUM; i++)
        if (pG->city[i].exist)
            pG->city_num++;
    
    return;
}


void fill_schedule(TICKET_INFO *p, const bool *s)
{
    /**
     * 函数名：fill_schedule
     * 作用：在TICKET_INFO中填入班次信息
     */
    
    for (int i = 0; i < 7; i++)
        p->in_schedule[i] = s[i];
    return;
}


CITY_LINK_BOX *get_city_link_box()
{
    /**
     * 函数名：get_city_link_box
     * 参数：无
     * 返回值：CITY_LINK_BOX地址
     * 作用：生成一个初始化的CITY_LINK_BOX变量
     */
    
    CITY_LINK_BOX *p = (CITY_LINK_BOX *)malloc(sizeof(CITY_LINK_BOX));
    if (!p) {raise_error("get_city_link_box", "Overflow"); return NULL;}
    
    p->first_air_ticket = p->first_rail_ticket = NULL;
    
    p->from = (char *)malloc(MAXLEN);
    p->to = (char *)malloc(MAXLEN);
    
    p->next = NULL;
    
    return p;
}


void calculate_duration(TIME departure, TIME arrival, TIME *p)
{
    /**
     * 函数名：calculate_duration
     * 作用：计算从departure到arrival所经历的时间，需要考虑跨过24点的情况
     */
    
    print_long_line();
    if (time_A_before_time_B(arrival, departure))
        arrival.day += 1;
//    print_time(*p, CLEAN, true);
    time_subtraction(arrival, departure, p);
    
    return;
}


TICKET_INFO *get_ticket_info(const char *id, const char *from, const char *to, const CARRIER carrier, const TIME departure_time, const TIME arrival_time, const float price)
{
    /**
     * 函数名：get_ticket_info
     * 参数：const char *from: 出发地名称字符串
            const char *to: 目的地名称字符串
            CARRIER carrier: 交通方式
            TIME departure_time: 出发时间
            TIME arrival_time: 到达时间
            unsigned int price: 票价
     * 返回值：初始化的TICKET_INFO结构变量地址
     * 作用：按照指定信息生成一个TICKET_INFO结构体并返回其地址
     */
    
    TICKET_INFO *p = (TICKET_INFO *)malloc(sizeof(TICKET_INFO));
    if (!p) {raise_error("get_city_box", "Overflow"); return NULL;}
    
    p->id = (char *)malloc(MAXLEN);
    p->from = (char *)malloc(MAXLEN);
    p->to = (char *)malloc(MAXLEN);
    
    strcpy(p->id, id);
    strcpy(p->from, from);
    strcpy(p->to, to);
    
    p->carrier = carrier;
    copy_time(&departure_time, &p->departure_time);
    copy_time(&arrival_time, &p->arrival_time);
    init_time(&p->duration);
    
    if (time_A_before_time_B(p->arrival_time, p->departure_time))   // 跨过24点的duration需要特别处理
    {
        TIME time_temp;
        init_time(&time_temp);
        copy_time(&p->arrival_time, &time_temp);
        time_temp.day += 1;
        time_subtraction(time_temp, departure_time, &p->duration);
    } else {
        time_subtraction(arrival_time, departure_time, &p->duration);
    }
    
    p->price = price;
    p->next = NULL;
    for (int i = 0; i < 7; i++) p->in_schedule[i] = false;
    
    return p;
}


CITY_BOX *get_city_box(const char *name, const bool exist)
{
    /**
     * 函数名：get_city_box
     * 返回值：指向一个初始化后的CITY_BOX结构体变量的指针
     * 作用：分配CITY_BOX的空间并初始化，返回该结构体
     */
    
    CITY_BOX *p = (CITY_BOX *)malloc(sizeof(CITY_BOX));
    if (!p) {raise_error("get_city_box", "Overflow"); return NULL;}
    
    p->name = (char *)malloc(MAXLEN);
    strcpy(p->name, name);
    p->exist = exist;
    p->exist_as_dest = false;
    p->first_link = NULL;
    
    return p;
}


unsigned city_to_index(const char *s)
{
    /**
     * 函数名：city_to_index
     * 参数：城市名字符串s
     * 作用：一个简单的字符串哈希函数，将城市名字符串hash到其在邻接表中的索引，采用线性探测解决哈希冲突
     */

    static char *hash_record[MAXNUM];
    static bool existed[MAXNUM] = {false};
    static bool initialization_finished = false;

    if (!initialization_finished)
    {
        for (int i = 0; i < MAXNUM; i++)
            hash_record[i] = (char *)malloc(MAXLEN);
        initialization_finished = true;
    }

    unsigned idx = 0, i = 0;

    while (s[i])
        idx = (idx * 43 + s[i++]) % 101;

    while (existed[idx] && strcmp(hash_record[idx], s))
        idx = (idx + 1) % 101;

    if (!strcmp(hash_record[idx], s)) return idx;
    else {
        existed[idx] = true;
        strcpy(hash_record[idx], s);
        return idx;
    }
}


Status insert_new_city(TRAFFIC_GRAPH *pG, const CITY_BOX city)
{
    /**
     * 函数名：insert_new_city
     * 参数：指向TRAFFIC_GRAPH的指针pG，需要插入的城市信息CITY_BOX结构变量city
     * 返回值：状态，OK表示成功插入，ERROR表示插入失败
     * 作用：在图的邻接表中插入一个新的城市信息；如果该城市已经存在，则报错
     */
    
    unsigned idx = city_to_index(city.name);
    
    if (pG->city[idx].exist)
    {
        raise_error("insert_new_city", "This city exists already. Cannot insert again.");
        return ERROR;
    }
    
    pG->city[idx].name = (char *)malloc(MAXLEN);
    
    copy_city_box(&city, &pG->city[idx]);
    pG->city[idx].exist = true;
    pG->city_num++;
    
    return OK;
}


Status delete_city(TRAFFIC_GRAPH *pG, const char *name)
{
    /**
     * 函数名：delete_city
     * 参数：指向TRAFFIC_GRAPH的指针pG，需要删除的城市信息CITY_BOX结构变量city
     * 返回值：状态，OK表示删除成功，ERROR表示删除失败
     * 作用：在图的邻接表中删除一个城市的所有信息；如果城市不存在，则报错
     */
    
    unsigned idx = city_to_index(name);
    
    if (!pG->city[idx].exist)
    {
        raise_error("delete_city", "This city does not exist. Cannot delete.");
        return ERROR;
    }
    
    pG->city[idx].exist = false;
    free(pG->city[idx].first_link);
    
    return OK;
}


Status insert_new_ticket_info(TRAFFIC_GRAPH *pG, TICKET_INFO t_info)
{
    /**
     * 函数名：insert_new_ticket_info
     * 参数：指向图的指针pG，待插入的票信息t_info
     * 返回值：状态，插入成功返回OK，否则返回ERROR并报错
     * 作用：在图的邻接表中插入新的票价信息；如果涉及新的城市，则相应添加
     * 备注：重复票价是否需要避免？
     */
    
    if (!pG) {raise_error("insert_new_ticket_info", "Graph not exists."); return ERROR;}
    
    time_subtraction(t_info.arrival_time, t_info.departure_time, &t_info.duration);
    
    if (!pG->city[city_to_index(t_info.to)].exist)
    {
        pG->city[city_to_index(t_info.to)].exist_as_dest = true;
        pG->city[city_to_index(t_info.to)].exist = true;
        pG->city[city_to_index(t_info.to)].name = (char *)malloc(MAXLEN);
        strcpy(pG->city[city_to_index(t_info.to)].name, t_info.to);
    }
    
    unsigned idx = city_to_index(t_info.from);
    
    CITY_LINK_BOX *pclb = NULL;
    
    if (!pG->city[idx].exist || !pG->city[idx].first_link)       // 图中不存在票上的出发城市的CITY_BOX或者没有从该城市出发的交通方式
    {
        // 初始化CITY_BOX
        if (!pG->city[idx].exist) pG->city_num++;
        pG->city[idx].exist = true;
        pG->city[idx].name = (char *)malloc(MAXLEN);
        strcpy(pG->city[idx].name, t_info.from);
        
        // 插入一个新的CITY_LINK_BOX并同步基本信息，TICKET_INFO的插入在后续过程中完成
        pclb = pG->city[idx].first_link = get_city_link_box();
        strcpy(pclb->from, t_info.from);
        strcpy(pclb->to, t_info.to);
    } else {                        // 图中存在票上的出发城市的CITY_BOX且有从该城市出发的交通线路
        pclb = pG->city[idx].first_link;
        
        // 造一个头结点，使得可以使用pre指针
        CITY_LINK_BOX *pre = get_city_link_box();
        pre->next = pclb;
        
        // pre和pclb同步顺着链表后移
        while (pclb && strcmp(pclb->to, t_info.to))
        {
            pclb = pclb->next;
            pre = pre->next;
        }
        
        if (!pclb)      // 未找到从出发地到目的地的CITY_LINK_BOX
        {
            pre->next = get_city_link_box();
            strcpy(pre->next->from, t_info.from);
            strcpy(pre->next->to, t_info.to);
            pclb = pre->next;
        } else {        // 找到了从出发地到目的地的CITY_LINK_BOX
            // assert equal
            if (strcmp(pclb->from, t_info.from) && strcmp(pclb->to, t_info.to))
            {
                raise_error("insert_new_ticket_info", "Unknown ERROR.");
            }
        }
    }
    
    if (!pclb)
    {
        raise_error("insert_new_ticket_info", "pclb NULL.");
        return ERROR;
    }
    
    TICKET_INFO *pti;
    switch (t_info.carrier)
    {
        case AIR: pti = pclb->first_air_ticket; break;
        case RAIL: pti = pclb->first_rail_ticket; break;
        default:
            raise_error("insert_new_ticket_info", "Wrong CARRIER.");
            return ERROR;
    }
    
    TICKET_INFO *pre = (TICKET_INFO *)malloc(sizeof(TICKET_INFO));
    pre->next = pti;
    
    TICKET_INFO *t = get_ticket_info(t_info.id, t_info.from, t_info.to, t_info.carrier, t_info.departure_time, t_info.arrival_time, t_info.price);
    fill_schedule(t, t_info.in_schedule);
    if (!pti)
    {
        if (t_info.carrier == AIR) pclb->first_air_ticket = t;
        else if (t_info.carrier == RAIL) pclb->first_rail_ticket = t;
        printf("# Ticket info inserted:\n");
        print_ticket_info(t_info, CLEAN);
        return OK;
    }
    
    while (pti && time_A_before_time_B(t->departure_time, pti->departure_time))
    {
        if (assert_ticket_info_same(*pti, t_info))
        {
            printf("# Ticket info already exists:\n");
            print_ticket_info(*pti, CLEAN);
            return OK;
        }
        pre = pre->next;
        pti = pti->next;
    }
    
    switch (t_info.carrier)
    {
        case AIR:
            if (pti == pclb->first_air_ticket)
            {
                t->next = pti;
                pclb->first_air_ticket = t;
            }
            break;
        case RAIL:
            if (pti == pclb->first_rail_ticket)
            {
                t->next = pti;
                pclb->first_rail_ticket = t;
            }
            break;
        default:
            raise_error("insert_new_ticket_info", "Wrong CARRIER.");
            return ERROR;
    }
    
    pre->next = t;
    strcpy(t->id, t_info.id);
    
    printf("# Ticket info inserted:\n");
    print_ticket_info(*t, CLEAN);
    
    return OK;
}


Status delete_ticket_info(TRAFFIC_GRAPH *pG, const TICKET_INFO t_info)
{
    /**
     * 函数名：delete_ticket_info
     * 参数：图指针pG，删除的TICKET_INFO信息t_info
     * 返回值：若图中存在该条信息，则删除后返回OK；若图中不存在这个票价信息，则返回ERROR
     * 作用：删除某一个票价信息
     */
    
    unsigned idx = city_to_index(t_info.from);
    CITY_BOX *pcb = &pG->city[idx];
    CITY_LINK_BOX *pclb = pcb->first_link;
    CITY_LINK_BOX *pre_cb = get_city_link_box();
    pre_cb->next = pclb;
    
    while (pclb)
    {
        if (strcmp(t_info.to, pclb->to) == 0) break;
        pclb = pclb->next;
        pre_cb = pre_cb->next;
    }
    
    if (!pclb)
    {
        raise_error("delete_ticket_info", "Ticket info below does not exist. Cannot delete.");
        print_ticket_info(t_info, CLEAN);
        return ERROR;
    }
    
    TICKET_INFO *pti = NULL;
    
    switch (t_info.carrier)
    {
        case AIR: pti = pclb->first_air_ticket; break;
        case RAIL: pti = pclb->first_rail_ticket; break;
        default:
            raise_error("delete_ticket_info", "Wrong CARRIER. Should be AIR or RAIL.");
            return ERROR;
    }
    
    TICKET_INFO *pre_ti = (TICKET_INFO *)malloc(sizeof(TICKET_INFO));
    pre_ti->next = pti;
    
    while (pti)
    {
        //if (assert_ticket_info_same(*pti, t_info))
        if (!strcmp(pti->id, t_info.id))
        {
            // 当前两个城市之间，这种交通方式只有一条线路
            if (pti == pclb->first_rail_ticket)
            {
                pclb->first_rail_ticket = pti->next;
                break;
            }
            if (pti == pclb->first_air_ticket)
            {
                pclb->first_air_ticket = pti->next;
                break;
            }
            pre_ti->next = pti->next;
            free(pti);
            break;
        }
        pti = pti->next;
        pre_ti = pre_ti->next;
    }
    
    if (!pti)
    {
        raise_error("delete_ticket_info", "Ticket info below does not exist. Cannot delete.");
        print_ticket_info(t_info, CLEAN);
        return ERROR;
    }
    
    if (!pclb->first_air_ticket && !pclb->first_rail_ticket)
    {
        if (pclb == pG->city[idx].first_link)
        {
            pG->city[idx].first_link = pclb->next;
        } else {
            pre_cb->next = pclb->next;
            free(pclb);
        }
    }
    
    update_exist_as_dest(pG);
    
    if (!pG->city[idx].first_link && !pG->city[idx].exist_as_dest)
        pG->city[idx].exist = false;
    
    printf("# Ticket info deleted:\n");
    print_ticket_info(*pti, CLEAN);
    
    return OK;
}


void init_ticket_info_queue(TICKET_INFO_QUEUE *pQ)
{
    /**
     * 函数名：init_ticket_info_queue
     * 作用：初始化TICKET_INFO栈
     */
    
    if (!pQ) {raise_error("init_route_queue", "Overflow."); return;}
    pQ->front = 0;
    pQ->rear = 0;
    for (int i = 0; i < MAXQUEUE; i++)
    {
        pQ->ticket[i].next = NULL;
        pQ->ticket[i].id = (char *)malloc(MAXLEN);
        pQ->ticket[i].from = (char *)malloc(MAXLEN);
        pQ->ticket[i].to = (char *)malloc(MAXLEN);
        for (int j = 0; j < 7; j++)
            pQ->ticket[i].in_schedule[j] = false;
        pQ->ticket[i].price = 0;
    }
    return;
}


TICKET_INFO de_queue_from_rear(TICKET_INFO_QUEUE *pQ)
{
    /**
     * 函数名：de_queue_from_front
     * 作用：将TICKET_INFO结构体变量出队列（从队列头）
     */
    
//    printf("de_queue_r: ");
//    print_ticket_info(pQ->ticket[pQ->rear-1], CLEAN);
    
    if (pQ->rear == pQ->front) {raise_error("de_queue_from_rear", "Queue empty. Cannot pop_queue.");}
    return pQ->ticket[--pQ->rear];
}

void en_queue(TICKET_INFO_QUEUE *pQ, TICKET_INFO t)
{
    /**
     * 函数名：en_queue
     * 作用：将TICKET_INFO结构体变量入队列
     */
    
//    printf("en_queue: ");
//    print_ticket_info(t, CLEAN);
    
    if (pQ->rear >= MAXQUEUE) {raise_error("en_queue", "Queue full. Cannot en_queue."); return;}
    copy_ticket_info(&t, &pQ->ticket[pQ->rear++]);
    return;
}


TICKET_INFO de_queue_from_front(TICKET_INFO_QUEUE *pQ)
{
    /**
     * 函数名：de_queue_from_front
     * 作用：将TICKET_INFO结构体变量出队列（从队列头）
     */
    
//    printf("de_queue: ");
//    print_ticket_info(pQ->ticket[pQ->front], CLEAN);

    if (pQ->front == pQ->rear) {raise_error("de_queue_from_front", "Queue empty. Cannot de_queue.");}
    return pQ->ticket[pQ->front++];
}


bool ticket_info_queue_full(TICKET_INFO_QUEUE Q)
{
    /**
     * 函数名：ticket_info_queue_full
     * 作用：判断队列满（超出最大范围）
     */
    
    return (Q.rear >= MAXQUEUE);
}


bool ticket_info_queue_empty(TICKET_INFO_QUEUE Q)
{
    /**
     * 函数名：ticket_info_queue_empty
     * 作用：判断队列空
     */
    
    return (Q.rear == Q.front);
}


ROUTE *get_route(CARRIER carrier)
{
    /**
     * 函数名：get_route
     * 作用：得到初始化的路径信息
     */
    
    ROUTE *p = (ROUTE *)malloc(sizeof(ROUTE));
    if (!p) {raise_error("get_route", "Overflow"); return NULL;}
    
    p->first_ticket_info = NULL;
    p->carrier = carrier;
    p->transfer_num = 0;
    p->price = 0;
    init_time(&p->departure_time);
    init_time(&p->arrival_time);
    init_time(&p->duration);
    init_time(&p->on_route_duration);
    init_time(&p->transfer_duration);
    
    return p;
}


TICKET_INFO *get_next_ticket_info(const TRAFFIC_GRAPH G, const char *from, TICKET_INFO t_current)
{
    /**
     * 函数名：get_next_ticket_info
     * 参数：图G，当前出发城市from，当前票价信息t_current
     * 返回值：指向下一张票的指针，若不存在，则为NULL
     * 作用：按照邻接表，顺序找到从该城市出发的下一个票价信息
     */
    
    if (assert_city_name_same(from, t_current.from) == false)
    {
        raise_error("get_next_ticket_info", "Conflict departure city name.");
        return NULL;
    }
    
    CITY_LINK_BOX *pclb = G.city[city_to_index(from)].first_link;
    while (pclb && strcmp(t_current.to, pclb->to) != 0) pclb = pclb->next;
    
    if (!pclb)
    {
        raise_error("get_next_ticket_info", "Cannot find a city link between your starting point and destination.");
        return NULL;
    }
    
    TICKET_INFO *pti = NULL;
    switch (t_current.carrier)
    {
        case AIR:
            pti = pclb->first_air_ticket;
            break;
        case RAIL:
            pti = pclb->first_rail_ticket;
            break;
        default:
            raise_error("get_next_ticket_info", "Wrong CARRIER. Should be AIR or RAIL.");
            break;
    }
    
    while (pti)
    {
        if (assert_ticket_info_same(*pti, t_current)) break;
        pti = pti->next;
    }
    
    if (pti->next) return pti->next;
    
    pclb = pclb->next;
    
    switch (t_current.carrier)
    {
        case AIR:
            while (pclb && !pclb->first_air_ticket) pclb = pclb->next;
            if (pclb) return pclb->first_air_ticket;
            break;
        case RAIL:
            while (pclb && !pclb->first_rail_ticket) pclb = pclb->next;
            if (pclb) return pclb->first_rail_ticket;
            break;
        default:
            raise_error("get_next_ticket_info", "Wrong CARRIER. Should be AIR or RAIL.");
            break;
    }
    
    return NULL;
}


void update_exist_as_dest(TRAFFIC_GRAPH *pG)
{
    /**
     * 函数名：update_exist_as_dest
     * 作用：更新所有终到城市信息
     */
    
    if (!pG) {raise_error("update_exist_as_dest", "Graph does not exist."); return;}
    
    for (int i = 0; i < MAXNUM; i++)
    {
        pG->city[i].exist_as_dest = false;
        if (pG->city[i].first_link)
        {
            CITY_LINK_BOX *p = pG->city[i].first_link;
            while (p)
            {
                pG->city[city_to_index(p->to)].exist_as_dest = true;
                p = p->next;
            }
        }
    }
    
    return;
}


ROUTE *get_route_from_ticket_info_queue(TICKET_INFO_QUEUE Q, USER_QUERY u)
{
    /**
     * 函数名：get_route_from_ticket_info_queue
     * 参数：一个由TICKET_INFO组成的队列Q
     * 返回值：一个指向由该队列中所有TICKET_INFO构成的全程交通信息的指针
     * 作用：从中间过程的队列中构建一个ROUTE，并完成额外信息的填充
     */
    
    if (ticket_info_queue_empty(Q)) return NULL;
    ROUTE *r = get_route(Q.ticket[Q.front].carrier);
    
    if (!r)
    {
        raise_error("get_route_from_ticket_info_stack", "Overflow.");
        return NULL;
    }
    
    TICKET_INFO ti = de_queue_from_front(&Q);
    r->first_ticket_info = get_ticket_info(ti.id, ti.from, ti.to, ti.carrier, ti.departure_time, ti.arrival_time, ti.price);
    TICKET_INFO *pti = r->first_ticket_info;
    
    while (!ticket_info_queue_empty(Q))
    {
        r->transfer_num++;
        r->price += ti.price;
        time_addition(ti.duration, r->on_route_duration, &r->on_route_duration);
        
        ti = de_queue_from_front(&Q);
        
        pti = pti->next = get_ticket_info(ti.id, ti.from, ti.to, ti.carrier, ti.departure_time, ti.arrival_time, ti.price);
    }
    
    r->price += ti.price;
    time_addition(ti.duration, r->on_route_duration, &r->on_route_duration);
    
    pti = r->first_ticket_info;
    TIME time_base = {u.departure.year, u.departure.month, u.departure.day, 0, 0};
    while (pti)
    {
        if (time_A_before_time_B(pti->arrival_time, pti->departure_time))
            add_one_day(&time_base);
        time_addition(time_base, pti->departure_time, &pti->departure_time);
        time_addition(time_base, pti->arrival_time, &pti->arrival_time);
        pti = pti->next;

    }
    
    for (pti = r->first_ticket_info; pti->next; pti = pti->next);

    copy_time(&r->first_ticket_info->departure_time, &r->departure_time);
    copy_time(&pti->arrival_time, &r->arrival_time);
    
    if (time_A_before_time_B(r->arrival_time, r->departure_time))   // 跨过24点的duration需要特别处理
    {
        TIME time_temp;
        init_time(&time_temp);
        copy_time(&r->arrival_time, &time_temp);
        time_temp.day += 1;
        time_subtraction(time_temp, r->departure_time, &r->duration);
    } else {
        time_subtraction(r->arrival_time, r->departure_time, &r->duration);
    }
    time_subtraction(r->duration, r->on_route_duration, &r->transfer_duration);
    
    
    return r;
}


TICKET_INFO *get_first_ticket_info(const TRAFFIC_GRAPH G, const char *from, const CARRIER carrier)
{
    /**
     * 函数名：get_first_ticket_info
     * 作用：找到从from城市出发的第一张票价信息（特定交通方式）
     */
    
    CITY_LINK_BOX *pclb = G.city[city_to_index(from)].first_link;
    TICKET_INFO *pti = NULL;
    
    switch (carrier)
    {
        case AIR:
            while (pclb && !pclb->first_air_ticket) pclb = pclb->next;
            if (pclb) pti = pclb->first_air_ticket;
            break;
        case RAIL:
            while (pclb && !pclb->first_rail_ticket) pclb = pclb->next;
            if (pclb) pti = pclb->first_rail_ticket;
            break;
        default:
            raise_error("get_first_ticket_info", "Wrong CARRIER. Should be AIR or RAIL.");
            break;
    }
    
    return pti;
}


void fill_date_in_ticket_info(TICKET_INFO *pti, TICKET_INFO t)
{
    /**
     * 函数名：fill_date_in_ticket_info
     * 作用：由于TICKET_INFO中是不包含具体的日期信息的，只有排班表和出发到达时间 的小时、分钟，所以在实际搜索用户的票的时候需要填上用户出发的日期
     */
    
    pti->arrival_time.year = t.departure_time.year;
    pti->arrival_time.month = t.departure_time.month;
    pti->arrival_time.day = t.departure_time.day;
    
    // 跨天
    if (time_A_before_time_B(pti->arrival_time, pti->departure_time))
        add_one_day(&pti->arrival_time);
    
    pti->departure_time.year = t.departure_time.year;
    pti->departure_time.month = t.departure_time.month;
    pti->departure_time.day = t.departure_time.day;
    
    return;
}


bool find_route_resursor(const TRAFFIC_GRAPH G, USER_QUERY u, TICKET_INFO *t_current, ROUTE *pR, unsigned *n, TICKET_INFO_QUEUE *pQ, bool *visited)
{
    /**
     * 函数名：find_route_resursor
     * 参数：const TRAFFIC_GRAPH G：交通图
            USER_QUERY u：用户输入的信息
            TICKET_INFO *t_current：指向当前票价信息的指针
            ROUTE *pR：用于存储所有找到的路径的数组头指针
            unsigned *n：用于记录找到的所有路径信息
            TICKET_INFO_QUEUE *pQ：当前用于记录路径票价信息的队列指针
            bool *visited：记录当前哪些城市已经被访问了
     * 作用：find_route的子函数，用于递归进行深度优先遍历
     */
    
    while (t_current && visited[city_to_index(t_current->to)])
        t_current = get_next_ticket_info(G, t_current->from, *t_current);
    
    if (!t_current) return false;
    
    visited[city_to_index(t_current->to)] = true;
    
    TIME current_arrival_time = t_current->arrival_time;
    TIME last_arrival_time;
    TIME departure = {0, 0, 0, u.departure.hour, u.departure. minute};
    
    while (t_current)
    {
        // 不在班期内或处罚时间早于用户指定的票直接跳过
        if (!t_current->in_schedule[u.travelling_week_day] || time_A_before_time_B(t_current->departure_time, departure))
        {
            t_current = get_next_ticket_info(G, t_current->from, *t_current);
            continue;
        }
        
        if (pQ && !ticket_info_queue_empty(*pQ))
        {
            last_arrival_time = pQ->ticket[pQ->rear-1].arrival_time;
            if (time_A_before_time_B(t_current->departure_time, last_arrival_time))
            {
                t_current = get_next_ticket_info(G, t_current->from, *t_current);
                continue;
            }
        }
        
        current_arrival_time = t_current->arrival_time;
        en_queue(pQ, *t_current);
        
        if (assert_city_name_same(t_current->to, u.to))
        {
            TICKET_INFO_QUEUE Qt;
            init_ticket_info_queue(&Qt);
            copy_queue(pQ, &Qt);
            *(pR + (*n)++) = *get_route_from_ticket_info_queue(Qt, u);
            
            de_queue_from_rear(pQ);
            visited[city_to_index(t_current->to)] = false;
            t_current = get_next_ticket_info(G, t_current->from, *t_current);
        } else {
            TICKET_INFO *t_next = get_first_ticket_info(G, t_current->to, u.carrier);
            
            // 出发时间早于上一程的到达时间，则跳过
            // 出发日期没有排班，则跳过
            while (t_next && (time_A_before_time_B(t_next->departure_time, current_arrival_time) || !t_next->in_schedule[u.travelling_week_day]))
                t_next = get_next_ticket_info(G, t_next->from, *t_next);
            
            if (t_next) find_route_resursor(G, u, t_next, pR, n, pQ, visited);
            de_queue_from_rear(pQ);
            t_current = get_next_ticket_info(G, t_current->from, *t_current);
        }
    }
    
    return false;
}


unsigned find_route(const TRAFFIC_GRAPH G, USER_QUERY u, ROUTE *pR)
{
    /**
     * 函数名：find_route
     * 参数：const TRAFFIC_GRAPH G：交通图的邻接表
     *      USER_QUERY u：用户的输入信息
     *      ROUTE *pR：ROUTE数组，需要实时分配空间，用于返回所有符合条件的路径信息
     * 返回值：查询到的满足条件的路径
     * 功能：在给定的交通图G（邻接表）中，按照决策原则，找到所有符合条件的交通路径
     */
    
    unsigned num_found = 0;
    
    TICKET_INFO_QUEUE Q;
    init_ticket_info_queue(&Q);
    
    bool visited[MAXNUM] = {false};
    visited[city_to_index(u.from)] = true;
    
    TICKET_INFO *pti = get_first_ticket_info(G, u.from, u.carrier);
    
    find_route_resursor(G, u, pti, pR, &num_found, &Q, visited);
    
    sort_route(pR, num_found, u.priority);
    
    return num_found;
}


void sort_route(ROUTE *pR, int n, PRIORITY priority)
{
    /**
     * 函数名：sort_route
     * 参数：ROUTE结构体数组头指针pR，pR指向的数组的大小，priority为用户指定的优先级
     * 作用：按照用户给定的优先级，将所有搜索到的路径排序，由于路径数目较少，故直接采用插入排序
     */
    
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (priority == SPEED)
            {
                if (time_A_before_time_B(pR[i].duration, pR[j].duration))
                {
                    ROUTE temp = pR[i];
                    for (int k = i; k > j; k--)
                        pR[k] = pR[k-1];
                    pR[j] = temp;
                }
            } else if (priority == ECON) {
                if (pR[i].price < pR[j].price)
                {
                    ROUTE temp = pR[i];
                    for (int k = i; k > j; k--)
                         pR[k] = pR[k-1];
                    pR[j] = temp;
                }
            } else if (priority == DIRECT) {
                if (pR[i].transfer_num < pR[j].transfer_num)
                {
                    ROUTE temp = pR[i];
                    for (int k = i; k > j; k--)
                         pR[k] = pR[k-1];
                    pR[j] = temp;
                }
            } else {
                raise_error("sort_route", "Invalid PRIORITY. Should be ECON, SPEED or DIRECT,");
                return;
            }
        }
    }
    
    return;
}
