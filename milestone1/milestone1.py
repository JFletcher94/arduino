import time
import serial
import numpy as np
    
ser = serial.Serial('COM3')
ser.timeout = 1
time.sleep(2)

s = ''
while (s != 'K'):
    time.sleep(1)
    ser.write('?')		
    s = ser.read(10)
print('connected')

#action while connected

ser.close()
print('disconnected')
