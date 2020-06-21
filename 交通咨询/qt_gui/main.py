#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR ZZY
File    : main.py
Time    : 2020-06-21
Software: PyCharm
'''

import sys, os
from PyQt5.Qt import *
from Welcome_panel import WelcomePanel
from System_panel import SystemPanel
from Record_panel import RecordPanel
from Query_panel import QueryPanel
from ctypes import *


traffic = CDLL('../lib/libtraffic.so')

class TIME(Structure):
    _fields_ = [("year", c_int),
                ("month", c_int),
                ("day", c_int),
                ("hour", c_int),
                ("minute", c_int)]


class TICKET_INFO(Structure):
    pass

TICKET_INFO._fields_ = [("_from", c_char_p),
                ("to", c_char_p),
                ("id", c_char_p),
                ("carrier", c_int),
                ("departure_time", TIME),
                ("arrival_time", TIME),
                ("duration", TIME),
                ("in_schedule", c_bool * 7),
                ("price", c_int),
                ("next", POINTER(TICKET_INFO))]


class CITY_LINK_BOX(Structure):
    pass

CITY_LINK_BOX._fields_ = [("_from", c_char_p),
                ("to", c_char_p),
                ("first_air_ticket", POINTER(TICKET_INFO)),
                ("first_rail_ticket", POINTER(TICKET_INFO)),
                ("minute", c_int),
                ("next", POINTER(CITY_LINK_BOX))]


class CITY_BOX(Structure):
    _fields_ = [("exist", c_bool),
                ("exist_as_dest", c_bool),
                ("name", c_char_p),
                ("first_link", POINTER(CITY_LINK_BOX))]


class TRAFFIC_GRAPH(Structure):
    _fields_ = [("city", 101 * CITY_BOX),
                ("city_num", c_int)]


class USER_QUERY(Structure):
    _fields_ = [("from", c_char_p),
                ("to", c_char_p),
                ("priority", c_int),
                ("carrier", c_int),
                ("departure", TIME),
                ("travelling_week_day", c_int)]


class ROUTE(Structure):
    _fields_ = [("first_ticket_info", POINTER(TICKET_INFO)),
                ("carrier", c_int),
                ("departure_time", TIME),
                ("arrival_time", TIME),
                ("duration", TIME),
                ("on_route_duration", TIME),
                ("transfer_duration", TIME),
                ("transfer_num", c_int),
                ("price", c_int)] # TODO 价格为float


class TICKET_INFO_QUEUE(Structure):
    _fields_ = [("ticket", 100 * TICKET_INFO),
                ("front", c_int),
                ("rear", c_int)]


def wel_to_sys():
    welcome.hide()
    system.show()


def sys_to_que():
    system.clear()
    system.hide()
    query.show() 


def sys_to_rec():
    system.clear()
    system.hide()
    record.show()


def que_to_rec():
    query.clear()
    query.hide()
    record.show()

    
def que_to_sys():
    query.clear()
    query.hide()
    system.show()


def rec_to_que():
    record.hide()
    query.show()


def rec_to_sys():
    record.hide()
    system.show()


def init_graph():
    init_traffic_graph = traffic.init_traffic_graph
    init_traffic_graph.argtypes = (POINTER(TRAFFIC_GRAPH), )
    init_traffic_graph(byref(G))


def get_schedule_from_int(a):
    j = [0, 0, 0, 0, 0, 0, 0]
    while a > 0:
        b = a % 10
        j[int(b)-1] = 1
        a = int(a / 10)
    return j


def insert_new_ticket_info(j):
    dep_time = TIME(0, 0, 0, j[4], j[5])
    arr_time = TIME(0, 0, 0, j[6], j[7])
    duration = TIME(0, 0, 0, 0, 0)
    SevenBool = c_bool * 7
    in_schedule = get_schedule_from_int(j[8])
    in_schedule = SevenBool(in_schedule[0], in_schedule[1], in_schedule[2], in_schedule[3], in_schedule[4], in_schedule[5], in_schedule[6])
    t_info = TICKET_INFO(j[1].encode('ascii'), j[2].encode('ascii'), j[0].encode('ascii'), \
                            j[3], dep_time, arr_time, duration, in_schedule, j[9])
    
    insert_ticket = traffic.insert_new_ticket_info
    insert_ticket.restype = c_int
    insert_ticket.argtypes = (POINTER(TRAFFIC_GRAPH), TICKET_INFO)
    insert_ticket(byref(G), t_info)
    record.addTable(1, j[1], j[2], j[0])


def delete_ticket_info(j):
    duration = TIME(0, 0, 0, 0, 0)
    SevenBool = 7 * c_bool
    in_schedule = SevenBool(0, 0, 0, 0, 0, 0, 0)
    t_info = TICKET_INFO(j[1].encode('ascii'), j[2].encode('ascii'), j[0].encode('ascii'), j[3], duration, duration, duration, in_schedule, 0)
    delete_ticket = traffic.delete_ticket_info
    delete_ticket.restype = c_int
    delete_ticket.argtypes = (POINTER(TRAFFIC_GRAPH), TICKET_INFO)
    delete_ticket(byref(G), t_info)
    record.addTable(0, j[1], j[2], j[0])


def add_ticket_info_from_txt(j):
    insert_file = traffic.add_ticket_info_from_txt
    insert_file.restype = c_bool
    insert_file.argtypes = (POINTER(TRAFFIC_GRAPH), c_char_p)
    txt_dir = bytes(j[0], encoding='utf-8')
    success = insert_file(byref(G), txt_dir)
    if not success:
        print("add_ticket_info_from_txt unsuccessfull")
        return
    record.addTable(1, "**", "**", "来自文件")
    print("successfully add ticket info form txt")


def get_city_link_box_num(i):
    get = traffic.get_city_link_box_num
    get.restype = c_int
    get.argtypes = [POINTER(TRAFFIC_GRAPH), c_int]
    return get(byref(G), i)


def get_ticket_info_num(pti):
    get = traffic.get_ticket_info_num
    get.restype = c_uint
    get.argtypes = [POINTER(TICKET_INFO), ]
    return get(pti)


def print_graph_all():
    pg = traffic.print_graph
    pg.argtypes = [TRAFFIC_GRAPH]
    pg(G)


def get_all_ticket_info_from_one_city(i):
    global G
    get = traffic.get_all_ticket_info_from_one_city
    get.argtypes = [TRAFFIC_GRAPH, c_uint]
    get.restype = POINTER(TICKET_INFO)
    return get(G, i)
    

def get_ticket_info_num_from_one_city(i):
    global G
    get = traffic.get_ticket_info_num_from_one_city
    get.argtypes = [TRAFFIC_GRAPH, c_uint]
    get.restype = c_uint
    return get(G, i)


def get_found_route_array(u):
    global G
    get = traffic.get_found_route_array
    get.argtypes = [TRAFFIC_GRAPH, USER_QUERY]
    get.restype = POINTER(ROUTE)
    return get(G, u)


def get_ticket_info_array(pti):
    get = traffic.get_ticket_info_array
    get.argtypes = [POINTER(TICKET_INFO)]
    get.restype = POINTER(TICKET_INFO)
    return get(pti)


def show_all():
    
    """
    将图中所有票价信息输出在窗口中
    """
    
    global G
    week_day = ['MON ', 'TUE ', 'WED ', 'THU ', 'FRI ', 'SAT ', 'SUN ']
    
    system.tableWidget.setRowCount(0)
    
    for i in range(101):
        if G.city[i].exist and G.city[i].first_link:
            t_num = get_ticket_info_num_from_one_city(i)
            t_info_array = get_all_ticket_info_from_one_city(i)
            for j in range(t_num):
                t_info = t_info_array[j]
                _from = str(t_info._from.decode('utf-8'))
                _to = str(t_info.to.decode('utf-8'))
                _id = str(t_info.id.decode('utf-8'))
                _carrier = "AIR" if t_info.carrier == 0 else "RAIL"
                _departure_time = str(t_info.departure_time.hour) + ':' + str(t_info.departure_time.minute)
                _arrival_time = str(t_info.arrival_time.hour) + ':'+ str(t_info.arrival_time.minute)
                _duration = str(t_info.duration.hour) + "小时" + str(t_info.duration.minute) + '分钟'
                _price = t_info.price
                _in_schedule = ''
                for k in range(7):
                    if t_info.in_schedule[k]:
                        _in_schedule += week_day[k]
                
                system.addTable(_id, _from, _to, _carrier, _departure_time, _arrival_time, _duration, f"{_in_schedule}", f"{_price}")


def queryRoute(j):
    global G
    departure = TIME(j[4], j[5], j[6], j[7], j[8])
    u = USER_QUERY(j[0].encode('ascii'), j[1].encode('ascii'), j[2], j[3], departure, j[9])
    find_route = traffic.find_route
    find_route.argtypes = (TRAFFIC_GRAPH, USER_QUERY, POINTER(ROUTE))
    find_route.restype = c_int
    route = get_found_route_array(u)
    idle = ROUTE()
    r_num = find_route(G, u, byref(idle))
    if j[3] == 0:
        carrier = "AIR"
    else:
        carrier = "RAIL"
    if r_num == 0:
        root_info = ["NONE", '', '', '', '', '', '', '', '', '', '']
        query.addTreeRoot(root_info)
    for i in range(r_num):
        # 离开时间
        dtime = route[i].departure_time
        if dtime.hour < 10:
            dtime_hour_str = f"0{dtime.hour}"
        else:
            dtime_hour_str = f"{dtime.hour}"
        if dtime.minute < 10:
            dtime_min_str = f"0{dtime.minute}"
        else:
            dtime_min_str = f"{dtime.minute}"
        dTime = f"{dtime.year}/{dtime.month}/{dtime.day} {dtime_hour_str}:{dtime_min_str}"
        # 到达时间
        atime = route[i].arrival_time
        if atime.hour < 10:
            atime_hour_str = f"0{atime.hour}"
        else:
            atime_hour_str = f"{atime.hour}"
        if atime.minute < 10:
            atime_min_str = f"0{atime.minute}"
        else:
            atime_min_str = f"{atime.minute}"
        aTime = f"{atime.year}/{atime.month}/{atime.day} {atime_hour_str}:{atime_min_str}"
        duration = f"{route[i].duration.hour}小时{route[i].duration.minute}分钟"
        on_route_duration = f"{route[i].on_route_duration.hour}小时{route[i].on_route_duration.minute}分钟"
        transfer_duration = f"{route[i].transfer_duration.hour}小时{route[i].transfer_duration.minute}分钟"
        print("price = %d" % route[i].price)
        root_info = ["点此展开", j[0], j[1], carrier, f"{route[i].price}", dTime, aTime, duration, on_route_duration,
                     transfer_duration, f"{route[i].transfer_num}"]
        root = query.addTreeRoot(root_info)
#        p = route[i].first_ticket_info[0]
        
        t_num = get_ticket_info_num(route[i].first_ticket_info)
        print("t_num = %d" % t_num)
        t_array = get_ticket_info_array(route[i].first_ticket_info)
#        while p:
        for k in range(t_num):
            # 离开时间
            dtime = t_array[k].departure_time
            if dtime.hour < 10:
                dtime_hour_str = f"0{dtime.hour}"
            else:
                dtime_hour_str = f"{dtime.hour}"
            if dtime.minute < 10:
                dtime_min_str = f"0{dtime.minute}"
            else:
                dtime_min_str = f"{dtime.minute}"
            dTime = f"{dtime.year}/{dtime.month}/{dtime.day} {dtime_hour_str}:{dtime_min_str}"
            # 到达时间
            atime = t_array[k].arrival_time
            if atime.hour < 10:
                atime_hour_str = f"0{atime.hour}"
            else:
                atime_hour_str = f"{atime.hour}"
            if atime.minute < 10:
                atime_min_str = f"0{atime.minute}"
            else:
                atime_min_str = f"{atime.minute}"
            aTime = f"{atime.year}/{atime.month}/{atime.day} {atime_hour_str}:{atime_min_str}"
            duration = f"{t_array[k].duration.hour}小时{t_array[k].duration.minute}分钟"
            leaf_info = [str(t_array[k].id.decode('ascii')), str(t_array[k]._from.decode('ascii')), str(t_array[k].to.decode('ascii')), carrier, f"{t_array[k].price}", dTime, aTime, duration, "**", "**", "**"]
            query.addTreeLeaf(root, leaf_info)
    record.addTable(2, j[0], j[1], f"一共查找到{r_num}条")


if __name__ == '__main__':

    app = QApplication(sys.argv)
    welcome = WelcomePanel()
    system = SystemPanel()
    record = RecordPanel()
    query = QueryPanel()
    
    # 页面切换
    welcome.welcome_sig.connect(wel_to_sys)
    system.change_sig_que.connect(sys_to_que)
    system.change_sig_rec.connect(sys_to_rec)
    record.change_sig_sys.connect(rec_to_sys)
    record.change_sig_que.connect(rec_to_que)
    query.change_sig_sys.connect(que_to_sys)
    query.change_sig_rec.connect(que_to_rec)

    system.gList_sig.connect(show_all)
    system.insert_sig.connect(insert_new_ticket_info)
    system.insert_file_sig.connect(add_ticket_info_from_txt)
    system.delete_sig.connect(delete_ticket_info)
    query.query_sig.connect(queryRoute)

    G = TRAFFIC_GRAPH()
    init_graph()
    welcome.show()
    sys.exit(app.exec_())