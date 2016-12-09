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
        print(str(ser.write(c_out)) + ' byte(s) written')
        time.sleep(1)
        s = ser.read(size=4).rstrip()
        print('received: ' + s)

def put_str(ser, data):
    establish_comm(ser, 'K', 'P')
    print(str(ser.write(data)) + ' byte(s) written')

def get_str(ser):
    establish_comm(ser, 'K', 'G')

if __name__ == "__main__":
    ser = connect_ser();
    establish_comm(ser, 'K', '?')

    s = raw_input('Type a message\n');
    put_str(ser, s)

    ser.close()
    print('disconnected')
