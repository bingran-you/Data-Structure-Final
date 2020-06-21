#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR ZZY
File    : c_wrap.py
Time    : 2020-06-13
Software: PyCharm
'''

from ctypes import *
sort = CDLL('../lib/libsort.so')

class TIME(Structure):
    _fields_ = [("sumtime", c_int),
                ("name", c_int),
                ("extimes", c_int)]


class INFO(Structure):
    _fields_ = [("name", c_char_p),
                ("gender", c_char)]


class ID_INFO(Structure):
    _fields_ = [("id", c_int),
                ("info", INFO)]


class ENTRY(Structure):
    _fields_ = [("data", c_int * 5),
                ("id_info", ID_INFO)]


class LIST(Structure):
    _fields_ = [("entry", POINTER(ENTRY)),
                ("len", c_int),
                ("sorted", c_int * 5)]


def timeList(j):
    time_judge = sort.time_judge
    time_judge.restype = POINTER(TIME)
    time_judge.argtypes = (c_int, c_int, c_int)
    return time_judge(c_int(j[0]), c_int(j[1]), c_int(j[2]))


def sortList(j):
    sort_data = sort.get_sorted_result
    sort_data.restype = POINTER(LIST)
    FiveIntegers = c_int * 5
    sort_data.argtypes = (c_int, POINTER(FiveIntegers), c_int, c_int, POINTER(FiveIntegers))
    seq = FiveIntegers(j[1], j[2], j[3], j[4], j[5])
    endian = FiveIntegers(j[8], j[9], j[10], j[11], j[12])
    return sort_data(c_int(j[0]), pointer(seq), c_int(j[7]), c_int(j[6]), pointer(endian))

