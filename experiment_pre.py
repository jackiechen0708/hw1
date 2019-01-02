# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'experiment_pre.ui'
#
# Created by: PyQt5 UI code generator 5.9.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.resize(400, 300)
        self.buttonBox = QtWidgets.QDialogButtonBox(Dialog)
        self.buttonBox.setGeometry(QtCore.QRect(30, 240, 341, 32))
        self.buttonBox.setOrientation(QtCore.Qt.Horizontal)
        self.buttonBox.setStandardButtons(QtWidgets.QDialogButtonBox.Cancel|QtWidgets.QDialogButtonBox.Ok)
        self.buttonBox.setObjectName("buttonBox")
        self.textBrowser = QtWidgets.QTextBrowser(Dialog)
        self.textBrowser.setGeometry(QtCore.QRect(70, 30, 256, 192))
        self.textBrowser.setObjectName("textBrowser")

        self.retranslateUi(Dialog)
        self.buttonBox.accepted.connect(Dialog.accept)
        self.buttonBox.rejected.connect(Dialog.reject)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
        self.textBrowser.setHtml(_translate("Dialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'SimSun\'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Consider the following problem carefully, then write down your decision. On the table are two urns, labeled A and B, containing red and blue marbles, and you have to draw a marble from one of the urns without looking. If you get a blue marble, you will be entered into a £30 lottery draw. Urn A contains 50 red marbles and 50 blue marbles. Urn B contains 100 marbles in an unknown color ratio, from 100 red marbles and 0 blue marbles to 0 red marbles and 100 blue marbles. The mixture of red and blue marbles in Urn B has been decided by writing the numbers 0, 1, 2, . . ., 100 on separate slips of paper, shuffling the slips thoroughly, and then drawing one of them at random. The number chosen was used to determine the number of blue marbles to be put into Urn B, but you do not know the number. Every possible mixture of red and blue marbles in Urn B is equally likely. You have to decide whether you prefer to draw a marble at random from Urn A or Urn B. What you hope is to draw a blue marble and be entered for the £30 lottery draw. Consider very carefully from which urn you prefer to draw the marble, then write down your decision below. You will draw a marble from your chosen urn straight afterwards. I prefer to draw a marble from Urn A/Urn B</p></body></html>"))

