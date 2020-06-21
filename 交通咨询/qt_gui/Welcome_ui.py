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
        Form.resize(899, 640)
        self.lbl_bg = QtWidgets.QLabel(Form)
        self.lbl_bg.setGeometry(QtCore.QRect(0, 0, 901, 641))
        self.lbl_bg.setMinimumSize(QtCore.QSize(901, 641))
        self.lbl_bg.setMaximumSize(QtCore.QSize(901, 641))
        self.lbl_bg.setStyleSheet("QLabel{\n"
"    border-radius:10px;\n"
"}\n"
"")
        self.lbl_bg.setText("")
        self.lbl_bg.setObjectName("lbl_bg")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(30, 0, 521, 31))
        self.label_3.setStyleSheet("color:rgb(126,124,160);\n"
"font: 14pt \"Avenir Next Condensed\";")
        self.label_3.setObjectName("label_3")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(120, 330, 231, 51))
        self.label_2.setStyleSheet("QLabel{\n"
"    font: 48pt \"Hannotate SC\";\n"
"    color:white\n"
"}")
        self.label_2.setObjectName("label_2")
        self.label_4 = QtWidgets.QLabel(Form)
        self.label_4.setGeometry(QtCore.QRect(110, 400, 241, 61))
        self.label_4.setStyleSheet("QLabel{\n"
"    font: 60pt \"Hannotate SC\";\n"
"    color:rgb(255,217,102);\n"
"}")
        self.label_4.setObjectName("label_4")
        self.label_5 = QtWidgets.QLabel(Form)
        self.label_5.setGeometry(QtCore.QRect(350, 400, 121, 61))
        self.label_5.setStyleSheet("QLabel{\n"
"    font: 60pt \"Hannotate SC\";\n"
"    color:white\n"
"}")
        self.label_5.setObjectName("label_5")
        self.pushButton = QtWidgets.QPushButton(Form)
        self.pushButton.setGeometry(QtCore.QRect(120, 490, 341, 31))
        self.pushButton.setStyleSheet("QPushButton{\n"
"    font: 16pt \"Heiti SC\";\n"
"    border-radius:10px;\n"
"    color:white\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    background-color: rgb(255,217,102);\n"
"}\n"
"\n"
"\n"
"QPushButton:pressed{\n"
"    background-color: rgb(46,49,146);\n"
"}")
        self.pushButton.setObjectName("pushButton")

        self.retranslateUi(Form)
        self.pushButton.clicked.connect(Form.welcome)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "GKD交通咨询系统"))
        self.label_3.setText(_translate("Form", "2020 数据结构大作业    作者: ZZY YBR WZR"))
        self.label_2.setText(_translate("Form", "欢迎进入"))
        self.label_4.setText(_translate("Form", "交通咨询"))
        self.label_5.setText(_translate("Form", "系统"))
        self.pushButton.setText(_translate("Form", "============点击开始体验============"))

