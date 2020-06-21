# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'query.ui'
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
        Form.setMaximumSize(QtCore.QSize(901, 16777215))
        self.pB_cP1 = QtWidgets.QPushButton(Form)
        self.pB_cP1.setEnabled(True)
        self.pB_cP1.setGeometry(QtCore.QRect(240, 0, 98, 41))
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
        self.label.setGeometry(QtCore.QRect(490, 50, 251, 41))
        self.label.setStyleSheet("font: 24pt \"Heiti SC\";\n"
"color : rgb(255, 255, 255)")
        self.label.setObjectName("label")
        self.getList_2 = QtWidgets.QPushButton(Form)
        self.getList_2.setEnabled(True)
        self.getList_2.setGeometry(QtCore.QRect(240, 50, 98, 41))
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
        self.label_4 = QtWidgets.QLabel(Form)
        self.label_4.setGeometry(QtCore.QRect(40, 60, 171, 21))
        self.label_4.setStyleSheet("font: 16pt \"Heiti SC\";\n"
"color : rgb(255,217,102);")
        self.label_4.setObjectName("label_4")
        self.label_8 = QtWidgets.QLabel(Form)
        self.label_8.setGeometry(QtCore.QRect(40, 90, 91, 16))
        self.label_8.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: rgb(255,217,102)")
        self.label_8.setObjectName("label_8")
        self.pB_cP2 = QtWidgets.QPushButton(Form)
        self.pB_cP2.setEnabled(True)
        self.pB_cP2.setGeometry(QtCore.QRect(240, 100, 98, 41))
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
        self.pB_query = QtWidgets.QPushButton(Form)
        self.pB_query.setGeometry(QtCore.QRect(120, 400, 81, 21))
        self.pB_query.setStyleSheet("QPushButton{\n"
"    font: 14pt \"Heiti SC\";\n"
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
        self.pB_query.setObjectName("pB_query")
        self.label_5 = QtWidgets.QLabel(Form)
        self.label_5.setGeometry(QtCore.QRect(40, 130, 41, 16))
        self.label_5.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_5.setObjectName("label_5")
        self.textEdit_3 = QtWidgets.QTextEdit(Form)
        self.textEdit_3.setGeometry(QtCore.QRect(90, 170, 111, 21))
        self.textEdit_3.setObjectName("textEdit_3")
        self.label_6 = QtWidgets.QLabel(Form)
        self.label_6.setGeometry(QtCore.QRect(40, 170, 41, 16))
        self.label_6.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_6.setObjectName("label_6")
        self.label_10 = QtWidgets.QLabel(Form)
        self.label_10.setGeometry(QtCore.QRect(40, 290, 61, 16))
        self.label_10.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_10.setObjectName("label_10")
        self.textEdit_2 = QtWidgets.QTextEdit(Form)
        self.textEdit_2.setGeometry(QtCore.QRect(90, 130, 111, 21))
        self.textEdit_2.setDocumentTitle("")
        self.textEdit_2.setObjectName("textEdit_2")
        self.label_12 = QtWidgets.QLabel(Form)
        self.label_12.setGeometry(QtCore.QRect(40, 210, 41, 21))
        self.label_12.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_12.setObjectName("label_12")
        self.comboBox = QtWidgets.QComboBox(Form)
        self.comboBox.setGeometry(QtCore.QRect(90, 210, 111, 26))
        self.comboBox.setObjectName("comboBox")
        self.comboBox.addItem("")
        self.comboBox.setItemText(0, "")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.comboBox.addItem("")
        self.dateTimeEdit = QtWidgets.QDateTimeEdit(Form)
        self.dateTimeEdit.setGeometry(QtCore.QRect(40, 320, 171, 24))
        self.dateTimeEdit.setSpecialValueText("")
        self.dateTimeEdit.setAccelerated(True)
        self.dateTimeEdit.setDate(QtCore.QDate(2020, 6, 22))
        self.dateTimeEdit.setTime(QtCore.QTime(10, 8, 0))
        self.dateTimeEdit.setCurrentSection(QtWidgets.QDateTimeEdit.YearSection)
        self.dateTimeEdit.setCalendarPopup(True)
        self.dateTimeEdit.setObjectName("dateTimeEdit")
        self.treeWidget = QtWidgets.QTreeWidget(Form)
        self.treeWidget.setGeometry(QtCore.QRect(270, 150, 611, 471))
        self.treeWidget.setAutoScroll(True)
        self.treeWidget.setAnimated(False)
        self.treeWidget.setAllColumnsShowFocus(False)
        self.treeWidget.setWordWrap(False)
        self.treeWidget.setHeaderHidden(False)
        self.treeWidget.setObjectName("treeWidget")
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(0, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(1, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(2, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(3, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(4, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(5, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(6, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(7, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(8, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(9, font)
        font = QtGui.QFont()
        font.setPointSize(14)
        self.treeWidget.headerItem().setFont(10, font)
        self.treeWidget.header().setVisible(True)
        self.label_11 = QtWidgets.QLabel(Form)
        self.label_11.setGeometry(QtCore.QRect(40, 360, 61, 16))
        self.label_11.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_11.setObjectName("label_11")
        self.comboBox_2 = QtWidgets.QComboBox(Form)
        self.comboBox_2.setGeometry(QtCore.QRect(90, 360, 104, 26))
        self.comboBox_2.setObjectName("comboBox_2")
        self.comboBox_2.addItem("")
        self.comboBox_2.setItemText(0, "")
        self.comboBox_2.addItem("")
        self.comboBox_2.addItem("")
        self.comboBox_2.addItem("")
        self.comboBox_2.addItem("")
        self.comboBox_2.addItem("")
        self.comboBox_2.addItem("")
        self.comboBox_2.addItem("")
        self.label_13 = QtWidgets.QLabel(Form)
        self.label_13.setGeometry(QtCore.QRect(40, 250, 61, 21))
        self.label_13.setStyleSheet("font: 14pt \"Hannotate SC\";\n"
"color: white")
        self.label_13.setObjectName("label_13")
        self.comboBox_3 = QtWidgets.QComboBox(Form)
        self.comboBox_3.setGeometry(QtCore.QRect(110, 250, 91, 26))
        self.comboBox_3.setObjectName("comboBox_3")
        self.comboBox_3.addItem("")
        self.comboBox_3.setItemText(0, "")
        self.comboBox_3.addItem("")
        self.comboBox_3.addItem("")
        self.lbl_bg.raise_()
        self.pB_cP1.raise_()
        self.label.raise_()
        self.getList_2.raise_()
        self.pB_cP2.raise_()
        self.lbl_l.raise_()
        self.label_2.raise_()
        self.label_3.raise_()
        self.label_4.raise_()
        self.label_8.raise_()
        self.pB_query.raise_()
        self.label_5.raise_()
        self.textEdit_3.raise_()
        self.label_6.raise_()
        self.label_10.raise_()
        self.textEdit_2.raise_()
        self.label_12.raise_()
        self.comboBox.raise_()
        self.dateTimeEdit.raise_()
        self.treeWidget.raise_()
        self.label_11.raise_()
        self.comboBox_2.raise_()
        self.label_13.raise_()
        self.comboBox_3.raise_()

        self.retranslateUi(Form)
        self.pB_query.clicked.connect(Form.queryRoute)
        self.pB_cP1.clicked.connect(Form.switchSystem)
        self.pB_cP2.clicked.connect(Form.switchRecord)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.pB_cP1.setText(_translate("Form", "修改时刻表"))
        self.label.setText(_translate("Form", "🌞推荐路线表🌞"))
        self.getList_2.setText(_translate("Form", "查询路线"))
        self.label_4.setText(_translate("Form", "====路线查询系统===="))
        self.label_8.setText(_translate("Form", "🌞 查询信息"))
        self.pB_cP2.setText(_translate("Form", "历史记录"))
        self.pB_query.setText(_translate("Form", "查询"))
        self.label_5.setText(_translate("Form", "出发地"))
        self.label_6.setText(_translate("Form", "目的地"))
        self.label_10.setText(_translate("Form", "出发时间"))
        self.label_12.setText(_translate("Form", "优先级"))
        self.comboBox.setItemText(1, _translate("Form", "经济优先"))
        self.comboBox.setItemText(2, _translate("Form", "时间优先"))
        self.comboBox.setItemText(3, _translate("Form", "中转次数优先"))
        self.treeWidget.setSortingEnabled(True)
        self.treeWidget.headerItem().setText(0, _translate("Form", "车次"))
        self.treeWidget.headerItem().setText(1, _translate("Form", "出发地"))
        self.treeWidget.headerItem().setText(2, _translate("Form", "目的地"))
        self.treeWidget.headerItem().setText(3, _translate("Form", "交通方式"))
        self.treeWidget.headerItem().setText(4, _translate("Form", "票价"))
        self.treeWidget.headerItem().setText(5, _translate("Form", "出发时间"))
        self.treeWidget.headerItem().setText(6, _translate("Form", "到达时间"))
        self.treeWidget.headerItem().setText(7, _translate("Form", "总时长"))
        self.treeWidget.headerItem().setText(8, _translate("Form", "乘坐时长"))
        self.treeWidget.headerItem().setText(9, _translate("Form", "中转时长"))
        self.treeWidget.headerItem().setText(10, _translate("Form", "中转次数"))
        self.label_11.setText(_translate("Form", "星期"))
        self.comboBox_2.setItemText(1, _translate("Form", "一"))
        self.comboBox_2.setItemText(2, _translate("Form", "二"))
        self.comboBox_2.setItemText(3, _translate("Form", "三"))
        self.comboBox_2.setItemText(4, _translate("Form", "四"))
        self.comboBox_2.setItemText(5, _translate("Form", "五"))
        self.comboBox_2.setItemText(6, _translate("Form", "六"))
        self.comboBox_2.setItemText(7, _translate("Form", "七"))
        self.label_13.setText(_translate("Form", "出行方式"))
        self.comboBox_3.setItemText(1, _translate("Form", "飞机"))
        self.comboBox_3.setItemText(2, _translate("Form", "火车"))

