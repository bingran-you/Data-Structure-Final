#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR
File    : Query.py
Time    : 2020-06-20
Software: PyCharm
'''

import sys
from PyQt5.Qt import *
from Query_ui import Ui_Form

class QueryPanel(QWidget, Ui_Form):
    query_sig = pyqtSignal(list)
    change_sig_sys = pyqtSignal()
    change_sig_rec = pyqtSignal()

    def __init__(self, parent=None, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)
        self.setupUi(self)
        self.label_3.setPixmap(QPixmap('images/icon.png'))

    def queryRoute(self):
        j = []
        j.append(self.textEdit_2.toPlainText())                     # 出发地
        j.append(self.textEdit_3.toPlainText())                     # 目的地
        j.append(self.comboBox.currentIndex() - 1)                  # 优先级
        j.append(self.comboBox_3.currentIndex() - 1)                # 出行方式
        j.append(int(self.dateTimeEdit.date().toString("yyyy")))    # 年
        j.append(int(self.dateTimeEdit.date().toString("MM")))      # 月
        j.append(int(self.dateTimeEdit.date().toString("dd")))      # 日
        j.append(int(self.dateTimeEdit.time().toString("hh")))      # 时
        j.append(int(self.dateTimeEdit.time().toString("mm")))      # 分
        j.append(self.comboBox_2.currentIndex() - 1)                # 星期几
        self.query_sig.emit(j)

    def switchSystem(self):
        self.change_sig_sys.emit()

    def switchRecord(self):
        self.change_sig_rec.emit()

    def clear(self):
        self.tableWidget.clearContents()

    def addTreeRoot(self, root_info):
        root = QTreeWidgetItem(self.treeWidget)
        for i in range(11):
            root.setText(i, root_info[i])
        return root

    def addTreeLeaf(self, root, leaf_info):
        leaf = QTreeWidgetItem(root)
        for i in range(11):
            leaf.setText(i, leaf_info[i])

    def clear(self):
        self.treeWidget.clear()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = QueryPanel()
    win.show()
    sys.exit(app.exec_())