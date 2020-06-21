# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'judge.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(781, 548)
        Form.setMinimumSize(QtCore.QSize(781, 548))
        Form.setMaximumSize(QtCore.QSize(781, 548))
        Form.setAutoFillBackground(False)
        self.tableWidget = QtWidgets.QTableWidget(Form)
        self.tableWidget.setEnabled(True)
        self.tableWidget.setGeometry(QtCore.QRect(30, 130, 721, 391))
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(3)
        self.tableWidget.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(2, item)
        self.num = QtWidgets.QSpinBox(Form)
        self.num.setGeometry(QtCore.QRect(100, 60, 81, 21))
        self.num.setMaximum(10000)
        self.num.setProperty("value", 200)
        self.num.setObjectName("num")
        self.return_btn = QtWidgets.QPushButton(Form)
        self.return_btn.setGeometry(QtCore.QRect(680, 20, 51, 21))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(14)
        self.return_btn.setFont(font)
        self.return_btn.setDefault(False)
        self.return_btn.setFlat(True)
        self.return_btn.setObjectName("return_btn")
        self.judge_btn = QtWidgets.QPushButton(Form)
        self.judge_btn.setEnabled(True)
        self.judge_btn.setGeometry(QtCore.QRect(680, 60, 50, 30))
        self.judge_btn.setMinimumSize(QtCore.QSize(50, 30))
        self.judge_btn.setMaximumSize(QtCore.QSize(50, 30))
        self.judge_btn.setSizeIncrement(QtCore.QSize(75, 50))
        self.judge_btn.setStyleSheet("QPushButton{\n"
"    background-color: rgb(224,124,106);\n"
"    border-radius:5px;\n"
"    color:white\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(234,172,91);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    background-color: rgb(220,83,129);\n"
"}")
        self.judge_btn.setObjectName("judge_btn")
        self.groupnum = QtWidgets.QSpinBox(Form)
        self.groupnum.setGeometry(QtCore.QRect(300, 60, 81, 21))
        self.groupnum.setMinimum(5)
        self.groupnum.setMaximum(8)
        self.groupnum.setObjectName("groupnum")
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(0, 110, 791, 441))
        self.label.setStyleSheet("QLabel{\n"
"    border-radius:5px;\n"
"}\n"
"")
        self.label.setText("")
        self.label.setObjectName("label")
        self.comboBox = QtWidgets.QComboBox(Form)
        self.comboBox.setGeometry(QtCore.QRect(510, 60, 104, 21))
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(30, 0, 521, 41))
        self.label_3.setStyleSheet("color:rgb(89,80,107);\n"
"font: 14pt \"Avenir Next Condensed\";")
        self.label_3.setObjectName("label_3")
        self.label_4 = QtWidgets.QLabel(Form)
        self.label_4.setGeometry(QtCore.QRect(20, 60, 161, 21))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(16)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.label_4.setFont(font)
        self.label_4.setStyleSheet("QLabel{\n"
"    background-color: rgb(229,141,100);\n"
"    border-radius:10px;\n"
"    color:white\n"
"}\n"
"")
        self.label_4.setObjectName("label_4")
        self.label_6 = QtWidgets.QLabel(Form)
        self.label_6.setGeometry(QtCore.QRect(400, 60, 221, 21))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(16)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.label_6.setFont(font)
        self.label_6.setStyleSheet("QLabel{\n"
"    background-color: rgb(229,141,100);\n"
"    border-radius:10px;\n"
"    color:white\n"
"}\n"
"")
        self.label_6.setObjectName("label_6")
        self.label_5 = QtWidgets.QLabel(Form)
        self.label_5.setGeometry(QtCore.QRect(190, 60, 201, 21))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(16)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.label_5.setFont(font)
        self.label_5.setStyleSheet("QLabel{\n"
"    background-color: rgb(229,141,100);\n"
"    border-radius:10px;\n"
"    color:white\n"
"}\n"
"")
        self.label_5.setObjectName("label_5")
        self.label_5.raise_()
        self.label_6.raise_()
        self.label_4.raise_()
        self.label.raise_()
        self.tableWidget.raise_()
        self.num.raise_()
        self.return_btn.raise_()
        self.judge_btn.raise_()
        self.groupnum.raise_()
        self.comboBox.raise_()
        self.label_3.raise_()

        self.retranslateUi(Form)
        self.judge_btn.clicked.connect(Form.judge_time)
        self.return_btn.clicked.connect(Form.returnWel)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "GKD多关键字排序系统--函数性能评测"))
        item = self.tableWidget.horizontalHeaderItem(0)
        item.setText(_translate("Form", "算法名称"))
        item = self.tableWidget.horizontalHeaderItem(1)
        item.setText(_translate("Form", "时间"))
        item = self.tableWidget.horizontalHeaderItem(2)
        item.setText(_translate("Form", "交换次数"))
        self.return_btn.setText(_translate("Form", "返回"))
        self.judge_btn.setText(_translate("Form", "测试"))
        self.comboBox.setItemText(0, _translate("Form", "时间优先"))
        self.comboBox.setItemText(1, _translate("Form", "交换次数优先"))
        self.label_3.setText(_translate("Form", "2020 数据结构大作业    作者: ZZY YBR WZR    version: 1.0.3"))
        self.label_4.setText(_translate("Form", "  数据个数"))
        self.label_6.setText(_translate("Form", "  性能比较选择"))
        self.label_5.setText(_translate("Form", "  测试数据组数"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Form = QtWidgets.QWidget()
    ui = Ui_Form()
    ui.setupUi(Form)
    Form.show()
    sys.exit(app.exec_())

