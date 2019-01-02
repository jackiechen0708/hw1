import sys
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
import UI.consent
import UI.demographics
QApplication.setAttribute(Qt.AA_EnableHighDpiScaling)
app = QApplication(sys.argv)

window = QMainWindow()

UI.consent.Ui_Dialog().setupUi(window)
window.show()
UI.demographics.Ui_Dialog().setupUi(window)
window.show()
sys.exit(app.exec_())