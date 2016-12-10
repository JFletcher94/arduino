import time
import serial
    
sname = '/dev/ttyACM0'


def connect_ser():
    ser = serial.Serial(sname, 9600)
    ser.timeout = 1
    print('connected to ' + sname)
    time.sleep(2)
    return ser

def establish_comm(ser, c_in, c_out):
    s = ''
    while (s != c_in):
        ser.write(c_out)
        time.sleep(1)
        s = ser.read(size=4).rstrip()
        time.sleep(1)

def put_str(ser, data):
    establish_comm(ser, 'K', 'P')
    print(str(ser.write(data)) + ' byte(s) written')
    time.sleep(1)

def get_str(ser):
    time.sleep(1)
    establish_comm(ser, 'K', 'G')
    s = ser.read(size=1024).rstrip()
    return s

if __name__ == "__main__":
    ser = connect_ser();
    establish_comm(ser, 'K', '?')

    c = ''
    while (c != 'q'):
        c = raw_input('Read, Write or Quit?(r/w/q)\n');
        if (c == 'w'):
            s = raw_input('Write a message\n')
            put_str(ser, s)
        elif (c == 'r'):
            s = get_str(ser)
            print(s)

    ser.close()
    print('disconnected')
