import time
import serial
    
sname = '/dev/ttyACM0'

ser = serial.Serial(sname, 9600)
ser.timeout = 1
print('connected to ' + sname)
time.sleep(2)

s = ''
while (s != 'K'):
    print(str(ser.write('?')) + ' byte(s) written')
    time.sleep(1)
    s = ser.read(size=4).rstrip()
    print('received: ' + s)
print('communication established')

#action while connected

ser.close()
print('disconnected')
