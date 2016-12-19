import time
import serial
import sys
    
sname = '/dev/ttyACM0' 
    #serial port name: machine-specific
    #currently running Linux Mint 18

def kill():
    '''terminate program if kill switch was flipped'''
    sys.stderr.write('Tampering detected. Encryption key erased. Goodbye.\n')
    sys.exit()

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
        if (s == '|'):
            kill()

def ser_write(ser, data):
    '''send string over serial'''
    ser.write('{')
    size = len(data)
    index = 0
    while (index < size):
        chunk = data[index:index+16]
        ser.write(chunk)
        ser.write('|')
        s = ''
        while (s != 'K'):
            s = ser.read(size=1)
            if (s == '|'):
                kill()
            time.sleep(0.01)
        index += 16
    ser.write('}')

def ser_read(ser):
    '''receive string over serial'''
    s = c = ''
    while (c != '{'):
        if (ser.in_waiting):
            c = ser.read(size=1)
            if (c == '|'):
                kill()
    while (c != '}'):
        if (ser.in_waiting):
            c = ser.read(size=1)
            if (c == '|'):
                kill()
            s += c
    return s[:-1]

def get_str(ser, name):
    '''decrypt file called name'''
    f = open(name, 'r')
    data = f.read().rstrip()
    f.close()
    establish_comm(ser, 'K', 'G')
    ser_write(ser, data)
    go_keys()
    f = open(name, 'w')
    f.write(ser_read(ser) + '\n')
    f.close()
    sys.stderr.write(name + ' decrypted\n')

def put_str(ser, name):
    '''encrypt file called name'''
    f = open(name, 'r')
    data = f.read().rstrip()
    f.close()
    data.replace('\n', ' ') #characters not supported
    data.replace('{', '[')
    data.replace('}', ']')
    data.replace('|', '\\')
    data.replace('~', '`')
    establish_comm(ser, 'K', 'P')
    ser_write(ser, data)
    go_keys()
    f = open(name, 'w')
    f.write(ser_read(ser) + '\n')
    f.close()
    sys.stderr.write(name + ' encrypted\n')

def go_keys():
    '''guide user through key-turning process'''
    establish_comm(ser, 'K', 'K')
    sys.stderr.write('Please turn both keys to "Ready"\n')
    establish_comm(ser, 'K', 'K')
    sys.stderr.write('Please turn both keys to "Start"\n')
    establish_comm(ser, 'K', 'K')
    sys.stderr.write('Please turn both keys to "Off"\n')
    establish_comm(ser, 'K', 'K')
    sys.stderr.write('Keys accepted\n')
    return

if __name__ == "__main__":
    ser = connect_ser();
    c = ''
    while (c != 'q'):
        establish_comm(ser, 'K', '?')
        sys.stderr.write('Encrypt, Decrypt or Quit? (e/d/q)\n')
        c = raw_input()
        if (c == 'e'):
            sys.stderr.write('This will destroy currently stored decryption key. Is that okay? (y/n)\n')
            s = raw_input()
            if (s == 'y'): 
                sys.stderr.write('Enter filename\n')
                s = raw_input()
                put_str(ser, s)
        elif (c == 'd'):
            sys.stderr.write('Enter filename\n')
            s = raw_input()
            s = get_str(ser, s)
    ser.write('Q')
    ser.close()
    sys.stderr.write('disconnected\n')

