import time
import serial
import numpy as np
import matplotlib.pyplot as plt
    
ser = serial.Serial('COM3')
ser.timeout = 1
time.sleep(2)

s = ''
while (s != 'K'):
    time.sleep(1)
    ser.write('?')		
    s = ser.read(10)
print('connected')

while True:
    plt.clf()
    ser.write('g')
    ttime = float(ser.readline().rstrip())/512.
    nums = np.zeros(512)
    for i in range(512):
        nums[i] = int(ser.readline().rstrip())
    axis = np.arange(0, 512*ttime, ttime)
    plt.subplot(2, 1, 1)
    plt.xlabel('microseconds')
    plt.ylabel('light intensity')
    plt.plot(axis, nums, 'b')
    
    k = np.arange(-0.5, 0.5, 1./512)
    Y = np.fft.fftshift(np.fft.fft(nums))/512.
    plt.subplot(2, 1, 2)
    plt.xlabel('megahertz')
    plt.plot(k, abs(Y), 'r')
    plt.show()
    plt.pause(0.05)

ser.close()
print('disconnected')