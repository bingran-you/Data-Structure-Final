#!/usr/bin/env python
# -*- coding: utf-8 -*-

'''
Author  : WZR
File    : welcome_panel.py
Time    : 2020-06-13
Software: PyCharm
'''

import sys
from PyQt5.Qt import *
from Welcome_ui import Ui_Form

class WelcomePanel(QWidget, Ui_Form):
    welcome_sig = pyqtSignal()
    welcome_sig_2 = pyqtSignal()

    def __init__(self, parent=None, *args, **kwargs):
        super().__init__(parent, *args, **kwargs)
        self.setupUi(self)
        self.label_bg.setPixmap(QPixmap('images/bg.png'))

    def welcome(self):
        self.welcome_sig.emit()

    def welcome_2(self):
        self.welcome_sig_2.emit()


if __name__ == '__main__':
    app = QApplication(sys.argv)
    win = WelcomePanel()
    win.show()
    sys.exit(app.exec_())
