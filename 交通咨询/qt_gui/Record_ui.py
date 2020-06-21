# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'record.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(901, 641)
        Form.setMinimumSize(QtCore.QSize(901, 641))
        Form.setMaximumSize(QtCore.QSize(901, 641))
        self.tableWidget = QtWidgets.QTableWidget(Form)
        self.tableWidget.setGeometry(QtCore.QRect(270, 150, 611, 471))
        self.tableWidget.setMouseTracking(False)
        self.tableWidget.setFrameShape(QtWidgets.QFrame.StyledPanel)
        self.tableWidget.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.tableWidget.setAlternatingRowColors(False)
        self.tableWidget.setObjectName("tableWidget")
        self.tableWidget.setColumnCount(4)
        self.tableWidget.setRowCount(0)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(0, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(1, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(2, item)
        item = QtWidgets.QTableWidgetItem()
        font = QtGui.QFont()
        font.setPointSize(14)
        item.setFont(font)
        self.tableWidget.setHorizontalHeaderItem(3, item)
        self.pB_cP1 = QtWidgets.QPushButton(Form)
        self.pB_cP1.setEnabled(True)
        self.pB_cP1.setGeometry(QtCore.QRect(240, 50, 98, 41))
        self.pB_cP1.setMinimumSize(QtCore.QSize(0, 0))
        self.pB_cP1.setMaximumSize(QtCore.QSize(98, 100))
        self.pB_cP1.setSizeIncrement(QtCore.QSize(75, 50))
        self.pB_cP1.setStyleSheet("QPushButton{\n"
"    font: 14pt \"Hannotate SC\";\n"
"    background-color: rgb(224,124,106);\n"
"    border-radius:20px;\n"
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
        self.pB_cP1.setObjectName("pB_cP1")
        self.lbl_l = QtWidgets.QLabel(Form)
        self.lbl_l.setGeometry(QtCore.QRect(0, 0, 251, 641))
        self.lbl_l.setStyleSheet("QLabel{\n"
"    background-color: rgb(100,94,135);\n"
"}")
        self.lbl_l.setText("")
        self.lbl_l.setObjectName("lbl_l")
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(490, 50, 171, 41))
        self.label.setStyleSheet("font: 24pt \"Heiti SC\";\n"
"color : rgb(255, 255, 255)")
        self.label.setObjectName("label")
        self.getList_2 = QtWidgets.QPushButton(Form)
        self.getList_2.setEnabled(True)
        self.getList_2.setGeometry(QtCore.QRect(240, 100, 98, 41))
        self.getList_2.setMinimumSize(QtCore.QSize(0, 0))
        self.getList_2.setMaximumSize(QtCore.QSize(98, 100))
        self.getList_2.setSizeIncrement(QtCore.QSize(75, 50))
        self.getList_2.setStyleSheet("QPushButton{\n"
"    font: 14pt \"Hannotate SC\";\n"
"    background-color: rgb(100,94,135);\n"
"    border-radius:20px;\n"
"    color:white\n"
"}\n"
"")
        self.getList_2.setObjectName("getList_2")
        self.lbl_bg = QtWidgets.QLabel(Form)
        self.lbl_bg.setEnabled(False)
        self.lbl_bg.setGeometry(QtCore.QRect(0, 0, 901, 641))
        self.lbl_bg.setMaximumSize(QtCore.QSize(16777215, 641))
        self.lbl_bg.setAutoFillBackground(False)
        self.lbl_bg.setStyleSheet("QLabel{\n"
"    background-color: rgb(72,60,108);\n"
"}")
        self.lbl_bg.setText("")
        self.lbl_bg.setScaledContents(False)
        self.lbl_bg.setObjectName("lbl_bg")
        self.label_4 = QtWidgets.QLabel(Form)
        self.label_4.setGeometry(QtCore.QRect(40, 70, 171, 21))
        self.label_4.setStyleSheet("font: 16pt \"Heiti SC\";\n"
"color : rgb(255,217,102);")
        self.label_4.setObjectName("label_4")
        self.label_8 = QtWidgets.QLabel(Form)
        self.label_8.setGeometry(QtCore.QRect(40, 110, 91, 16))
        self.label_8.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: rgb(255,217,102)")
        self.label_8.setObjectName("label_8")
        self.pB_cP2 = QtWidgets.QPushButton(Form)
        self.pB_cP2.setEnabled(True)
        self.pB_cP2.setGeometry(QtCore.QRect(240, 0, 98, 41))
        self.pB_cP2.setMinimumSize(QtCore.QSize(0, 0))
        self.pB_cP2.setMaximumSize(QtCore.QSize(98, 100))
        self.pB_cP2.setSizeIncrement(QtCore.QSize(75, 50))
        self.pB_cP2.setStyleSheet("QPushButton{\n"
"    font: 14pt \"Hannotate SC\";\n"
"    background-color: rgb(224,124,106);\n"
"    border-radius:20px;\n"
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
        self.pB_cP2.setObjectName("pB_cP2")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(30, 450, 191, 171))
        self.label_3.setStyleSheet("QLabel{\n"
"    background-color: rgb(140,142,173);\n"
"    border-radius:20px;\n"
"    color:white\n"
"}\n"
"")
        self.label_3.setText("")
        self.label_3.setObjectName("label_3")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(30, 40, 191, 391))
        self.label_2.setStyleSheet("QLabel{\n"
"    background-color: rgb(140,142,173);\n"
"    border-radius:20px;\n"
"    color:white\n"
"}\n"
"")
        self.label_2.setText("")
        self.label_2.setObjectName("label_2")
        self.label_7 = QtWidgets.QLabel(Form)
        self.label_7.setGeometry(QtCore.QRect(40, 150, 131, 16))
        self.label_7.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_7.setObjectName("label_7")
        self.label_9 = QtWidgets.QLabel(Form)
        self.label_9.setGeometry(QtCore.QRect(60, 180, 131, 16))
        self.label_9.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_9.setObjectName("label_9")
        self.label_10 = QtWidgets.QLabel(Form)
        self.label_10.setGeometry(QtCore.QRect(60, 210, 131, 16))
        self.label_10.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_10.setObjectName("label_10")
        self.label_11 = QtWidgets.QLabel(Form)
        self.label_11.setGeometry(QtCore.QRect(60, 240, 131, 16))
        self.label_11.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_11.setObjectName("label_11")
        self.pB_getL = QtWidgets.QPushButton(Form)
        self.pB_getL.setEnabled(True)
        self.pB_getL.setGeometry(QtCore.QRect(770, 50, 91, 41))
        self.pB_getL.setMinimumSize(QtCore.QSize(0, 0))
        self.pB_getL.setMaximumSize(QtCore.QSize(98, 100))
        self.pB_getL.setSizeIncrement(QtCore.QSize(75, 50))
        self.pB_getL.setStyleSheet("QPushButton{\n"
"    font: 14pt \"Hannotate SC\";\n"
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
        self.pB_getL.setObjectName("pB_getL")
        self.lbl_bg.raise_()
        self.tableWidget.raise_()
        self.label.raise_()
        self.getList_2.raise_()
        self.pB_cP1.raise_()
        self.pB_cP2.raise_()
        self.lbl_l.raise_()
        self.label_2.raise_()
        self.label_3.raise_()
        self.label_4.raise_()
        self.label_8.raise_()
        self.label_7.raise_()
        self.label_9.raise_()
        self.label_10.raise_()
        self.label_11.raise_()
        self.pB_getL.raise_()

        self.retranslateUi(Form)
        self.pB_cP2.clicked.connect(Form.switchSystem)
        self.pB_cP1.clicked.connect(Form.switchQuery)
        self.pB_getL.clicked.connect(Form.clear)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.tableWidget.setSortingEnabled(True)
        item = self.tableWidget.horizontalHeaderItem(0)
        item.setText(_translate("Form", "操作种类"))
        item = self.tableWidget.horizontalHeaderItem(1)
        item.setText(_translate("Form", "出发地"))
        item = self.tableWidget.horizontalHeaderItem(2)
        item.setText(_translate("Form", "目的地"))
        item = self.tableWidget.horizontalHeaderItem(3)
        item.setText(_translate("Form", "备注"))
        self.pB_cP1.setText(_translate("Form", "查询路线"))
        self.label.setText(_translate("Form", "🌞历史记录表🌞"))
        self.getList_2.setText(_translate("Form", "历史记录"))
        self.label_4.setText(_translate("Form", "====查询历史记录===="))
        self.label_8.setText(_translate("Form", "🌞 内容说明"))
        self.pB_cP2.setText(_translate("Form", "修改时刻表"))
        self.label_7.setText(_translate("Form", "操作种类共有三种："))
        self.label_9.setText(_translate("Form", "DEL 删除路线"))
        self.label_10.setText(_translate("Form", "ADD 添加路线"))
        self.label_11.setText(_translate("Form", "SEA 查询路线"))
        self.pB_getL.setText(_translate("Form", "清空历史记录"))

