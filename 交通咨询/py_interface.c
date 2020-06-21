/*------------------------------------------------
    作者: ZZY
    日期: 2020.6.21
    文件名: graph.c
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: pyqt5 GUI相关
    
    v1.1: 完成路线搜索、排序功能
    v1.2: 完成终端Interface 20200616
    v1.3: 文件输入完成
------------------------------------------------*/

#include "head_file.h"

unsigned get_city_link_box_num(TRAFFIC_GRAPH *pG, unsigned i)
{
    /**
     * 函数名：get_city_link_box_num
     * 作用：得到从索引为i的城市出发能够到达的城市数目，方便构建pyqt
     */
    
    unsigned count = 0;
    CITY_LINK_BOX *pclb = pG->city[i].first_link;
    
    while (pclb)
    {
        count++;
        pclb = pclb->next;
    }
    
    return count;
}


unsigned get_ticket_info_num(TICKET_INFO *pti)
{
    /**
     * 函数名：get_ticket_info_num
     * 作用：得到从pti开始还剩多少张票的信息，用于构建GUI
     */
    
    unsigned count = 0;
    while (pti)
    {
        printf("%s\n", pti->to);
        count++;
        pti = pti->next;
    }
    printf("count = %d\n", count);
    return count;
}



unsigned get_ticket_info_num_from_one_city(TRAFFIC_GRAPH G, unsigned i)
{
    /**
     * 函数名：get_ticket_info_num_from_one_city
     * 作用：得到从索引为i的城市出发的所有交通线路的数量，用于构建pyqt的GUI
     */
    
    CITY_LINK_BOX *pclb = G.city[i].first_link;
    unsigned count = 0;
    
    while (pclb)
    {
        TICKET_INFO *pti = NULL;
        
        pti = pclb->first_air_ticket;
        while (pti)
        {
            count++;
            pti = pti->next;
        }
        
        pti = pclb->first_rail_ticket;
        while (pti)
        {
            count++;
            pti = pti->next;
        }
        pclb = pclb->next;
    }
    
    return count;
}


TICKET_INFO *get_all_ticket_info_from_one_city(TRAFFIC_GRAPH G, unsigned i)
{
    /**
     * 函数名：get_all_ticket_info_from_one_city
     * 参数：交通图G，城市索引i
     * 作用：在使用pyqt显示所有交通线的时候，将从一个城市出发的所有交通线存储在一个数组中，方便索引
     */
    
    CITY_LINK_BOX *pclb = G.city[i].first_link;
    unsigned t_info_num = get_ticket_info_num_from_one_city(G, i);
    TICKET_INFO *p = (TICKET_INFO *)malloc(t_info_num * sizeof(TICKET_INFO));
    
    unsigned j = 0;
    
    while (pclb)
    {
        TICKET_INFO *pti = NULL;
        
        pti = pclb->first_air_ticket;
        while (pti)
        {
            p[j++] = *pti;
            pti = pti->next;
        }
        
        pti = pclb->first_rail_ticket;
        while (pti)
        {
            p[j++] = *pti;
            pti = pti->next;
        }
        
        pclb = pclb->next;
    }
    
    return p;
}


ROUTE *get_found_route_array(const TRAFFIC_GRAPH G, USER_QUERY u)
{
    ROUTE *pR = (ROUTE *)malloc(10 * sizeof(ROUTE));
    
    find_route(G, u, pR);
    
    return pR;
}



TICKET_INFO *get_ticket_info_array(TICKET_INFO *pti)
{
    TICKET_INFO *p = (TICKET_INFO *)malloc(10 * sizeof(TICKET_INFO));
    unsigned i = 0;
    
    while (pti)
    {
        p[i++] = *pti;
        pti = pti->next;
    }
    
    return p;
}
