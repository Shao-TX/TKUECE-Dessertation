# -*- coding: utf-8 -*-

from PyQt5 import QtWidgets
from PyQt5.QtWidgets import *
from PyQt5 import QtCore, QtGui, QtWidgets
import shapeshift_ui as ui
from PyQt5.QtCore import QFile
from smbus import SMBus 
import time
import tqdm
import random
import os
import sys

addr = [0x8,0x9,0xA,0xB,0xC,0xD] # address list
device_num = len(addr) # device num
motor_num = 6 # only for test
i2c = SMBus(1) #indicates /dev/ic2-1
cont = True #控制程式迴圈





class Main(QMainWindow, ui.Ui_MainWindow):
    def __init__(self):
         super().__init__()
         self.setupUi(self)
    def readFile(self):
        fname = QFileDialog.getOpenFileName(self, "Open File", "./", "txt (*.txt)")

        if fname[0]:                                                                   #判断路径非空
            #f = QFile(fname[0])                                                       #创建文件对象，不创建文件对象也不报错 也可以读文件和写文件
            with open(fname[0], "r", encoding="utf8") as File:
                data = File.readlines()
                #data = data.split(",")
            for i in range(len(data)):
                data[i] = data[i].strip("\n").split(",")
                if(len(data[i])!=6):
                    print("Import Format Error!")
                    return
                for j in range(len(data[i])):
                    try:
                        data[i][j] = int(data[i][j])
                    except:
                        print("Unable Type for Integer Input")
                motor_map[i] = data[i]
                    
            if(len(data)!=device_num or len(data[i])!=motor_num):
                print("Number of Input Data Error!")
                return
            print(f"data list : {data} \n data length : {len(data)}")
                #讀檔
    def writeFile(self):
        fname = QFileDialog.getSaveFileName(self, "Write File", "./", "All (*.*)")      #写入文件首先获取文件路径
        if fname[0]:                                                                    #如果获取的路径非空                                                     #以写入的方式打开文件
            with open(fname[0], "w") as File:
                output = {}
                for i in range(device_num):
                    output[i] = [0]*motor_num
                    temp = ""
                    for j in range(motor_num):
                        output[i][j] = motor_map[i][j]
                        temp += str(output[i][j])+","
                    File.write(temp[:-1]+'\n')
            print("File Write Success")
                #寫檔

app = QtWidgets.QApplication(sys.argv)
window = Main()

motor_map = {0:[0]*motor_num,
             1:[0]*motor_num,
             2:[0]*motor_num,
             3:[0]*motor_num,
             4:[0]*motor_num,
             5:[0]*motor_num,
             }
btn_map = {0:[window.btn1,window.btn2,window.btn3,window.btn4,window.btn5,window.btn6],
           1:[window.btn7,window.btn8,window.btn9,window.btn10,window.btn11,window.btn12],
           2:[window.btn13,window.btn14,window.btn15,window.btn16,window.btn17,window.btn18],
           3:[window.btn19,window.btn20,window.btn21,window.btn22,window.btn23,window.btn24],
           4:[window.btn25,window.btn26,window.btn27,window.btn28,window.btn29,window.btn30],
           5:[window.btn31,window.btn32,window.btn33,window.btn34,window.btn35,window.btn36],
           }

btnList = ['( σ՞ਊ ՞)σ ',window.btn1,window.btn2,window.btn3,window.btn4,window.btn5,window.btn6,window.btn7,window.btn8,window.btn9,window.btn10,window.btn11,window.btn12,window.btn13,window.btn14,window.btn15,window.btn16,window.btn17,window.btn18,window.btn19,window.btn20,window.btn21,window.btn22,window.btn23,window.btn24,window.btn25,window.btn26,window.btn27,window.btn28,window.btn29,window.btn30,window.btn31,window.btn32,window.btn33,window.btn34,window.btn35,window.btn36]


def readPosition():
    print("Reading Data...")
    for i in range(device_num):
        motor_map[i] = i2c.read_i2c_block_data(addr[i],0,motor_num)
        for j in range(motor_num):
            btn_map[i][j].setText(str(motor_map[i][j]))
    print("Read Data Success")

def writePosition():
    print("Writting Data...")
    for i in range(device_num):
        temp = i2c.read_i2c_block_data(addr[i],0,motor_num)
        if(motor_map[i]==temp):
            continue;
        i2c.write_i2c_block_data(addr[i],0,motor_map[i])
    print("Write Data Success")

def pinControl():
    if(window.lineEdit.text()=='' or window.lineEdit_2.text()==''):
        print("please type in")
        return
    print("Pin Control Start")
    pin = window.lineEdit.text()
    value = window.lineEdit_2.text()
    print("pin : "+pin+" , value : "+value)
    pin = int(pin)-1
    value = int(value)
    window.lineEdit.clear()
    window.lineEdit_2.clear()
    readPosition()
    time.sleep(1)
    
    motor_map[pin//motor_num][pin%motor_num] = value
    print(motor_map)
    try:
        writePosition()
    except:
        print("Data Writting Error!")
        return
    time.sleep(1)
    readPosition()
    print("Pin Control Success")

def pinReset():
    print("Pin Reset Start")
    readPosition()
    time.sleep(1)
    
    for i in range(device_num):
        for j in range(motor_num):
            motor_map[i][j]=0
    
    try:
        writePosition()
    except:
        print("Data Writting Error!")
        return
    time.sleep(1)
    readPosition()
    time.sleep(1)
    
    print("Pin Reset Success")
    

def main():


    window.gridLayoutWidget.setGeometry(QtCore.QRect(10, 10, 700, 700))
    window.verticalLayoutWidget.setGeometry(QtCore.QRect(720, 10, 140, 300))
    window.formLayoutWidget.setGeometry(QtCore.QRect(720, 410, 140, 300))


    sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
    
    for i in range(1,37):
        
        btnList[i].setSizePolicy(sizePolicy)
        btnList[i].setMinimumSize(98,98)
        btnList[i].setText("")
    #     # btnList[i].setFixedSize(100,100)

    window.ExitBtn.clicked.connect(window.close)
    window.ImportBtn.clicked.connect(window.readFile)
    window.ExportBtn.clicked.connect(window.writeFile)
    window.OptionBtn.clicked.connect(readPosition)
    window.PinResetBtn.clicked.connect(pinReset)
    window.sendBtn.clicked.connect(pinControl)

    

    window.setWindowIcon(QtGui.QIcon('icon.ico'))
    window.resize(880, 720)
    window.setWindowTitle("ShapeShift v1.1")
    window.show()
    
    try:
        readPosition()
    except:
        print("Initialization Error!")
        #exit(-1)

    sys.exit(app.exec_())



if __name__ == '__main__':
    main()
    