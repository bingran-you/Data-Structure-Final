#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR
File    : System_panel.py
Time    : 2020-06-20
Software: PyCharm
'''

import sys
from PyQt5.Qt import *
from System_ui import Ui_Form

class SystemPanel(QWidget, Ui_Form):
    change_sig_que = pyqtSignal()
    gList_sig = pyqtSignal()
    change_sig_rec = pyqtSignal()
    insert_sig = pyqtSignal(list)
    insert_file_sig = pyqtSignal(list)
    delete_sig = pyqtSignal(list)

    def __init__(self, parent=None, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)
        self.setupUi(self)

    def switchQuery(self):
        self.change_sig_que.emit()

    def getList(self):
        self.gList_sig.emit()

    def switchRecord(self):
        self.change_sig_rec.emit()

    def openFile(self):
        fname = QFileDialog.getOpenFileName(self, '打开文件...', './', 'TXT文件(*.txt)')
        self.textEdit_4.setText(fname[0])

    def insertTicket(self):
        j = []
        j.append(self.textEdit.toPlainText())    # 车次 航班号
        j.append(self.textEdit_2.toPlainText())  # 出发地
        j.append(self.textEdit_3.toPlainText())  # 目的地
        j.append(self.comboBox.currentIndex())   # 交通方式
        j.append(int(self.timeEdit.time().toString("hh")))  # 时
        j.append(int(self.timeEdit.time().toString("mm")))  # 分
        j.append(int(self.timeEdit_2.time().toString("hh")))  # 时
        j.append(int(self.timeEdit_2.time().toString("mm")))  # 分
        j.append(self.spinBox.value())          # 班次信息
        j.append(self.spinBox_2.value())        # 票价
        self.insert_sig.emit(j)

    def insertTicketfile(self):
        j = []
        j.append(self.textEdit_4.toPlainText())
        self.insert_file_sig.emit(j)

    def deleteTicket(self):
        j = []
        j.append(self.textEdit_7.toPlainText())  # 车次 航班号
        j.append(self.textEdit_6.toPlainText())  # 出发地
        j.append(self.textEdit_5.toPlainText())  # 目的地
        j.append(self.comboBox_2.currentIndex()) # 交通方式
        print(j)
        self.delete_sig.emit(j)

    def addTable(self, k1, k2, k3, k4, k5, k6, k7, k8, k9):
        row = self.tableWidget.rowCount()
        self.tableWidget.setRowCount(row + 1)
        k1Item = QTableWidgetItem(k1)  # 车次
        self.tableWidget.setItem(row, 0, k1Item)
        k2Item = QTableWidgetItem(k2)  # 出发地
        self.tableWidget.setItem(row, 1, k2Item)
        k3Item = QTableWidgetItem(k3)  # 目的地
        self.tableWidget.setItem(row, 2, k3Item)
        k4Item = QTableWidgetItem(k4)  # 种类
        self.tableWidget.setItem(row, 3, k4Item)
        k5Item = QTableWidgetItem(k5)  # 出发时间
        self.tableWidget.setItem(row, 4, k5Item)
        k6Item = QTableWidgetItem(k6)  # 到达时间
        self.tableWidget.setItem(row, 5, k6Item)
        k7Item = QTableWidgetItem(k7)  # 时长
        self.tableWidget.setItem(row, 6, k7Item)
        k8Item = QTableWidgetItem(k8)  # 班次
        self.tableWidget.setItem(row, 7, k8Item)
        k9Item = QTableWidgetItem(k9)  # 价格
        self.tableWidget.setItem(row, 8, k9Item)

    def clear(self):
        self.tableWidget.clearContents()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = SystemPanel()
    win.show()
    sys.exit(app.exec_())