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
    
    return

def get_str(ser):
    establish_comm(ser, 'K', 'G')

    return

if __name__ == "__main__":
    ser = connect_ser();
    establish_comm(ser, 'K', '?')

    put_str(ser, 'hello, world!')

    ser.close()
    print('disconnected')
