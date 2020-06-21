# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'welcome.ui'
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
        self.welcome_btn = QtWidgets.QPushButton(Form)
        self.welcome_btn.setEnabled(True)
        self.welcome_btn.setGeometry(QtCore.QRect(400, 430, 131, 61))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(14)
        self.welcome_btn.setFont(font)
        self.welcome_btn.setStyleSheet("QPushButton{\n"
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
        self.welcome_btn.setObjectName("welcome_btn")
        self.welcome_btn_2 = QtWidgets.QPushButton(Form)
        self.welcome_btn_2.setEnabled(True)
        self.welcome_btn_2.setGeometry(QtCore.QRect(580, 430, 131, 61))
        font = QtGui.QFont()
        font.setFamily("Heiti SC")
        font.setPointSize(14)
        self.welcome_btn_2.setFont(font)
        self.welcome_btn_2.setStyleSheet("QPushButton{\n"
"    background-color: rgb(120,122,206);\n"
"    border-radius:5px;\n"
"    color:white\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(85,152,222);\n"
"}\n"
"\n"
"QPushButton:pressed{\n"
"    background-color: rgb(167,97,192);\n"
"}")
        self.welcome_btn_2.setObjectName("welcome_btn_2")
        self.label_bg = QtWidgets.QLabel(Form)
        self.label_bg.setGeometry(QtCore.QRect(0, 0, 781, 361))
        self.label_bg.setMinimumSize(QtCore.QSize(781, 351))
        self.label_bg.setText("")
        self.label_bg.setObjectName("label_bg")
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(510, 170, 251, 91))
        self.label.setStyleSheet("font: 60pt \"Avenir Next Condensed\";\n"
"color:white;")
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(40, 250, 721, 101))
        font = QtGui.QFont()
        font.setFamily("DIN Alternate")
        font.setPointSize(72)
        font.setBold(False)
        font.setItalic(False)
        font.setWeight(50)
        self.label_2.setFont(font)
        self.label_2.setStyleSheet("font: 72pt \"DIN Alternate\";\n"
"color:white;")
        self.label_2.setObjectName("label_2")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(30, 0, 701, 41))
        self.label_3.setStyleSheet("color:rgb(89,80,107);\n"
"font: 14pt \"Avenir Next Condensed\";")
        self.label_3.setObjectName("label_3")
        self.label_bg.raise_()
        self.welcome_btn.raise_()
        self.welcome_btn_2.raise_()
        self.label.raise_()
        self.label_2.raise_()
        self.label_3.raise_()

        self.retranslateUi(Form)
        self.welcome_btn.clicked.connect(Form.welcome)
        self.welcome_btn_2.clicked.connect(Form.welcome_2)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "GKD多关键字排序系统--欢迎界面"))
        self.welcome_btn.setText(_translate("Form", "比较排序性能"))
        self.welcome_btn_2.setText(_translate("Form", "获得排序结果"))
        self.label.setText(_translate("Form", "欢迎来到"))
        self.label_2.setText(_translate("Form", "GKD多关键字排序系统"))
        self.label_3.setText(_translate("Form", "2020 数据结构大作业    作者: ZZY YBR WZR    version: 1.0.3"))

