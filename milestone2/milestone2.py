import time
import serial
import sys
    
sname = '/dev/ttyACM0' 
    #serial port name: machine-specific
    #currently running Linux Mint 18

def connect_ser():
    '''establish serial connection'''
    ser = serial.Serial(sname, 9600)
    ser.timeout = 1
    sys.stderr.write('connected to ' + sname + '\n')
    time.sleep(2)
    return ser

def establish_comm(ser, c_in, c_out):
    '''establish/syncronize communication'''
    s = ''
    while (s != c_in):
        ser.write(c_out)
        time.sleep(0.01)
        s = ser.read(size=1).rstrip()

def put_str(ser, data):
    '''send string over serial'''
    establish_comm(ser, 'K', 'P')
    ser.write('<')
    size = len(data)
    index = 0
    num_bytes = 0
    while (index < size):
        chunk = data[index:index+16]
        num_bytes += ser.write(chunk)
        ser.write('|')
        s = ''
        while (s != 'K'):
            s = ser.read(size=1)
            time.sleep(0.01)
        index += 16
    ser.write('>')
    sys.stderr.write(str(num_bytes) + ' byte(s) written\n')

def get_str(ser):
    '''receive string over serial'''
    establish_comm(ser, 'K', 'G')
    s = c = ''
    while (c != '<'):
        if (ser.in_waiting):
            c = ser.read(size=1)
        time.sleep(0.01)
    while (c != '>'):
        if (ser.in_waiting):
            c = ser.read(size=1)
            s += c
    return s[:-1]

if __name__ == "__main__":
    ser = connect_ser();
    c = ''
    while (c != 'q'):
        establish_comm(ser, 'K', '?')
        sys.stderr.write('Read, Write or Quit? (r/w/q)\n')
        c = raw_input()
        if (c == 'w'):
            sys.stderr.write('Write a message\n')
            s = raw_input()
            put_str(ser, s)
        elif (c == 'r'):
            s = get_str(ser)
            sys.stdout.write(s + '\n')
    ser.write('Q')
    ser.close()
    sys.stderr.write('disconnected\n')

