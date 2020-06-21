#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR
File    : Judge.py
Time    : 2020-06-14
'''

import sys
from PyQt5.Qt import *
from Judge_ui import Ui_Form

class JudgePanel(QWidget, Ui_Form):
    judge_sig = pyqtSignal(list)
    returnWel_sig = pyqtSignal()

    def __init__(self, parent=None, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)
        self.setupUi(self)
        self.tableWidget.setColumnWidth(0, 280)
        self.tableWidget.setColumnWidth(1, 210)
        self.tableWidget.setColumnWidth(2, 210)
        self.label.setPixmap(QPixmap('images/bg.png'))

    def returnWel(self):
        self.returnWel_sig.emit()

    def judge_time(self):
        j = []
        j.append(self.num.value())
        j.append(self.groupnum.value())
        j.append(self.comboBox.currentIndex())
        self.judge_sig.emit(j)

    def add_table(self, name, time, extimes):
        row = self.tableWidget.rowCount()
        self.tableWidget.setRowCount(row + 1)
        if name == 0:
            real_name = 'radix_10_sort'
        elif name == 1:
            real_name = 'radix_101_sort'
        elif name == 2:
            real_name = 'merge_sort'
        elif name == 3:
            real_name = 'quick_sort'
        elif name == 4:
            real_name = 'bubble_sort'
        elif name == 5:
            real_name = 'insert_sort'
        elif name == 6:
            real_name = 'shell_sort'
        elif name == 7:
            real_name = 'heap_sort'
        nameItem = QTableWidgetItem(real_name)
        self.tableWidget.setItem(row, 0, nameItem)
        timeItem = QTableWidgetItem(f"{time}")
        self.tableWidget.setItem(row, 1, timeItem)
        extimesItem = QTableWidgetItem(f"{extimes}")
        self.tableWidget.setItem(row, 2, extimesItem)

    def clear(self):
        self.tableWidget.clearContents()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = JudgePanel()
    win.show()
    sys.exit(app.exec_())




