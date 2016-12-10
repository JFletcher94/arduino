import time
import serial
import numpy as np
import matplotlib.pyplot as plt
    
ser = serial.Serial('COM3') //windows
ser.timeout = 1
time.sleep(2)

s = ''
while (s != 'K'):
    time.sleep(1)
    ser.write('?')		
    s = ser.read(10).rstrip()
print('connected')

s = ''
while (s != 'K'):
    time.sleep(1)
    ser.write('g')		
    s = ser.read(10).rstrip()
print('reading')

X = np.arange(256)
Y = np.zeros(256)
for i in range(256):
    s = ser.readline().rstrip()
    while (s == ''):
        s = ser.readline().rstrip()
    Y[i] = int(s)
plt.plot(X, Y)
plt.xlabel('analogWrite voltage')
plt.ylabel('Volts')
plt.show()

ser.close()
print('disconnected')
