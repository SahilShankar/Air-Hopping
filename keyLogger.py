from pynput.keyboard import Key, Listener
import logging
import serial
import time

log_dir = r"C:/Users/hwata/Desktop/"
logging.basicConfig(filename=(log_dir + "keyLog1.txt"),
                    level=logging.DEBUG, filemode='w', format='%(message)s')

ArduinoSerial = serial.Serial('com5',9600)
time.sleep(2)

def on_press(key):
    if(len(str(key)) > 3):
        keys = 0
        print(str(key).replace("Key.", ""))
        if(str(key).replace("Key.", "") == "backspace"):
            keys = 8
            print(keys)
        elif(str(key).replace("Key.", "") == "enter"):
            keys = 13
        elif(str(key).replace("Key.", "") == "space"):
            keys = 32
        elif(str(key).replace("Key.", "") == "tab"):
            keys = 9
        elif(str(key).replace("Key.", "") == "ctrl"):
            keys = 17
        elif(str(key).replace("Key.", "") == "cmd"):
            keys = 146
        elif(str(key).replace("Key.", "") == "up"):
            keys = 160
        elif(str(key).replace("Key.", "") == "down"):
            keys = 161
        elif(str(key).replace("Key.", "") == "right"):
            keys = 171
        elif(str(key).replace("Key.", "") == "left"):
            keys = 172
        print('{0:08b}'.format(keys)+" == "+str(key))
        logging.info('{0:08b}'.format(keys))

    else:
        print('{0:08b}'.format(ord(str(key).replace("'", "")))+" == "+str(key))
        logging.info('{0:08b}'.format(ord(str(key).replace("'", ""))))
    filepath = r"C:/Users/hwata/Desktop/keyLog1.txt"
    with open(filepath) as fp:
        lines = fp.readlines()
        print(len(lines[-1].encode()))
        ArduinoSerial.write(lines[-1].encode()) #send 1


with Listener(on_press=on_press) as listener:
    listener.join()


