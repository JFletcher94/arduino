import time
import serial
import numpy as np
import matplotlib.pyplot as plt
    
kmax = 200;
X = np.arange(kmax)
Y = np.zeros(shape=(2, kmax))
    
ser = serial.Serial('COM3') //windows
ser.timeout = 1
time.sleep(2)

s = ''
while (not 'K' in s):
    time.sleep(1)
    ser.write('?')		
    s = ser.read(10).strip()
print('connected')

s = ''
while (not 'K' in s):
    time.sleep(1)
    ser.write('g')		
    s = ser.read(10).strip()
print('reading')

for i in range(kmax):
    s = ser.readline().strip()
    while (s == ''):
        s = ser.readline().strip()
    Y[0][i] = float(s)
    
s = ''
while (not 'K' in s):
    time.sleep(1)
    ser.write('g')		
    s = ser.read(10).strip()
print('reading')

for i in range(kmax):
    s = ser.readline().strip()
    while (s == ''):
        s = ser.readline().strip()
    Y[1][i] = float(s)
    
plt.subplot(2, 1, 1)
plt.title('Pmax/10   Imax/10')
plt.xlabel('steps')
plt.ylabel('voltage')
plt.plot(X, Y[0], 'r')
plt.subplot(2, 1, 2)
plt.xlabel('steps')
plt.ylabel('output')
plt.plot(X, Y[1], 'b')
plt.show()

ser.close()
print('disconnected')
