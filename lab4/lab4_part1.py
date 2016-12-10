import time
import serial

ser = serial.Serial('COM3') //windows
time.sleep(2)

ser.write('?')
s = ser.read()
print(s)

ser.close()
