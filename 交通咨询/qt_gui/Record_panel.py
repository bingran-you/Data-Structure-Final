#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR
File    : Record_panel.py
Time    : 2020-06-21
'''

import sys
from PyQt5.Qt import *
from Record_ui import Ui_Form

class RecordPanel(QWidget, Ui_Form):
    change_sig_sys = pyqtSignal()
    change_sig_que = pyqtSignal()

    def __init__(self, parent=None, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)
        self.setupUi(self)
        self.label_3.setPixmap(QPixmap('images/icon.png'))

    def switchSystem(self):
        self.change_sig_sys.emit()

    def switchQuery(self):
        self.change_sig_que.emit()

    def addTable(self, k1,k2,k3,k4):
        row = self.tableWidget.rowCount()
        self.tableWidget.setRowCount(row + 1)
        if k1 == 0:
            type = "DEL"
        elif k1 == 1:
            type = "ADD"
        elif k1 == 2:
            type = "SEA"
        k1Item = QTableWidgetItem(type)             # 种类
        self.tableWidget.setItem(row, 0, k1Item)
        k2Item = QTableWidgetItem(k2)               # 出发地
        self.tableWidget.setItem(row, 1, k2Item)
        k3Item = QTableWidgetItem(k3)               # 目的地
        self.tableWidget.setItem(row, 2, k3Item)
        k4Item = QTableWidgetItem(k4)               # 备注
        self.tableWidget.setItem(row, 3, k4Item)

    def clear(self):
        self.tableWidget.setRowCount(0)
        self.tableWidget.clearContents()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = RecordPanel()
    win.show()
    sys.exit(app.exec_())