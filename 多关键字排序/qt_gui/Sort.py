#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR
File    : Sort.py
Time    : 2020-06-14
'''

import sys
from PyQt5.Qt import *
from Sort_ui import Ui_Form

class SortPanel(QWidget, Ui_Form):
    sort_sig = pyqtSignal(list)
    returnWel_sig = pyqtSignal()

    def __init__(self, parent=None, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)
        self.setupUi(self)
        self.tableWidget.setColumnWidth(0, 142)
        self.tableWidget.setColumnWidth(1, 142)
        self.tableWidget.setColumnWidth(2, 142)
        self.tableWidget.setColumnWidth(3, 142)
        self.tableWidget.setColumnWidth(4, 142)
        self.label.setPixmap(QPixmap('images/bg.png'))

    def returnWel(self):
        self.returnWel_sig.emit()

    def sort_data(self):
        s = [1,2,3,4,5]
        j = []
        j.append(self.spinBox.value())
        a = self.comboBox.currentIndex()
        if s[a] == 0:
            for i in s:
                if i != 0:
                    a = i - 1
                    s[a] = 0
                    break
        j.append(a)
        a = self.comboBox_2.currentIndex()
        if s[a] == 0:
            for i in s:
                if i != 0:
                    a = i - 1
                    s[a] = 0
                    break
        j.append(a)
        a = self.comboBox_3.currentIndex()
        if s[a] == 0:
            for i in s:
                if i != 0:
                    a = i - 1
                    s[a] = 0
                    break
        j.append(a)
        a = self.comboBox_4.currentIndex()
        if s[a] == 0:
            for i in s:
                if i != 0:
                    a = i - 1
                    s[a] = 0
                    break
        j.append(a)
        a = self.comboBox_5.currentIndex()
        if s[a] == 0:
            for i in s:
                if i != 0:
                    a = i - 1
                    s[a] = 0
                    break
        j.append(a)
        j.append(self.comboBox_6.currentIndex())
        j.append(self.comboBox_7.currentIndex())
        a = self.comboBox_9.currentIndex()
        j.append(2 * a - 1)
        a = self.comboBox_10.currentIndex()
        j.append(2 * a - 1)
        a = self.comboBox_11.currentIndex()
        j.append(2 * a - 1)
        a = self.comboBox_12.currentIndex()
        j.append(2 * a - 1)
        a = self.comboBox_13.currentIndex()
        j.append(2 * a - 1)
        self.sort_sig.emit(j)

    def add_table(self, k1,k2,k3,k4,k5):
        row = self.tableWidget.rowCount()
        self.tableWidget.setRowCount(row + 1)
        k1Item = QTableWidgetItem(f"{k1}")
        self.tableWidget.setItem(row, 0, k1Item)
        k2Item = QTableWidgetItem(f"{k2}")
        self.tableWidget.setItem(row, 1, k2Item)
        k3Item = QTableWidgetItem(f"{k3}")
        self.tableWidget.setItem(row, 2, k3Item)
        k4Item = QTableWidgetItem(f"{k4}")
        self.tableWidget.setItem(row, 3, k4Item)
        k5Item = QTableWidgetItem(f"{k5}")
        self.tableWidget.setItem(row, 4, k5Item)

    def clear(self):
        self.tableWidget.clearContents()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = SortPanel()
    win.show()
    sys.exit(app.exec_())