/*------------------------------------------------
    作者: ZZY
    日期: 2020.6.13
    文件名: io.c
    版本: v1.3
    项目: 数据结构大作业--交通咨询
    说明: 文件输入输出相关
 
    v1.3: 文件输入完成 20200617
------------------------------------------------*/

#include "head_file.h"


bool add_ticket_info_from_txt(TRAFFIC_GRAPH *pG, const char *fname)
{
    /**
     * 函数名：add_ticket_info_from_txt
     * 参数：图指针pG，文件名（txt文件的绝对路径）fname
     * 作用：从txt文件中读取所有的票价信息，插入到pG所指向的交通图中
     */
    
    FILE *fp = fopen(fname, "r");
    
    char c;
    if (!fp)
    {
        printf("%s\n", fname);
        raise_error("add_ticket_info_from_txt", "Fail to open file.");
        return false;
    }
    
    TICKET_INFO t_info;
    
    while (fscanf(fp, "%c", &c) != EOF)
    {
        init_ticket_info(&t_info);
        
        if (c == 'p') t_info.carrier = AIR;
        else if (c == 't') t_info.carrier = RAIL;
        else {
            raise_error("add_ticket_info_from_txt", "Wrong CARRIER. Should be p (for PLANE) or t (for TRAIN).");
            return false;
        }
        if (fscanf(fp, "%c", &c) == EOF) return false;
        
        int i = 0;
        
        while (fscanf(fp, "%c", &c) != EOF && c != ' ')
            t_info.id[i++] = c;
        t_info.id[i] = '\0';
        if (c == EOF) return false;
        
        i = 0;
        while (fscanf(fp, "%c", &c) != EOF && c != ' ')
            t_info.from[i++] = c;
        t_info.from[i] = '\0';
        if (c == EOF) return false;
        
        i = 0;
        while (fscanf(fp, "%c", &c) != EOF && c != ' ')
            t_info.to[i++] = c;
        t_info.to[i] = '\0';
        if (c == EOF) return false;
        
        while (fscanf(fp, "%c", &c) != EOF && c != ':')
            t_info.departure_time.hour = t_info.departure_time.hour * 10 + c - '0';
        if (c == EOF) return false;
        
        while (fscanf(fp, "%c", &c) != EOF && c != ' ')
            t_info.departure_time.minute = t_info.departure_time.minute * 10 + c - '0';
        if (c == EOF) return false;
        
        while (fscanf(fp, "%c", &c) != EOF && c != ':')
            t_info.arrival_time.hour = t_info.arrival_time.hour * 10 + c - '0';
        if (c == EOF) return false;
        
        while (fscanf(fp, "%c", &c) != EOF && c != ' ')
            t_info.arrival_time.minute = t_info.arrival_time.minute * 10 + c - '0';
        if (c == EOF) return false;
        
        calculate_duration(t_info.departure_time, t_info.arrival_time, &t_info.duration);
        
        while (fscanf(fp, "%c", &c) != EOF && c != ' ')
            t_info.price = t_info.price * 10 + c - '0';
        if (c == EOF) return false;
        
        while (fscanf(fp, "%c", &c) != EOF && c != '\n' && c != EOF)
            t_info.in_schedule[c - '0' - 1] = true;
        if (c == EOF) break;
        
        insert_new_ticket_info(pG, t_info);
    }
    
    fclose(fp);
    
    return true;
}
