#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : Wang ZIrui
File    : welcome_panel.py
Time    : 2020-06-13
Software: PyCharm
'''

import sys
from PyQt5.Qt import *
from Welcome import WelcomePanel
from Sort import SortPanel
from Judge import JudgePanel
from c_wrap import *


if __name__ == '__main__':
    import sys

    app = QApplication(sys.argv)
    welcome = WelcomePanel()
    sort = SortPanel()
    judge = JudgePanel()

    def switch_mode():
        welcome.hide()
        judge.show()
        judge.clear()

    def switch_mode2():
        welcome.hide()
        sort.show()
        sort.clear()

    def judge_to_wel():
        judge.clear()
        judge.hide()
        welcome.show()

    def sort_to_wel():
        sort.clear()
        sort.hide()
        welcome.show()

    def c_judge(j):
        judge.clear()
        judge.tableWidget.setRowCount(0)
        p = timeList(j)
        for i in range(8):
            judge.add_table(p[i].name, p[i].sumtime, p[i].extimes)

    def c_sort(j):
        sort.clear()
        sort.tableWidget.setRowCount(0)
        p = sortList(j)
        for i in range(j[0]):
            sort.add_table(p[0].entry[i].data[0], p[0].entry[i].data[1], p[0].entry[i].data[2], p[0].entry[i].data[3], p[0].entry[i].data[4])

    welcome.welcome_sig.connect(switch_mode)
    welcome.welcome_sig_2.connect(switch_mode2)
    judge.returnWel_sig.connect(judge_to_wel)
    judge.judge_sig.connect(c_judge)
    sort.returnWel_sig.connect(sort_to_wel)
    sort.sort_sig.connect(c_sort)

    welcome.show()
    sys.exit(app.exec_())