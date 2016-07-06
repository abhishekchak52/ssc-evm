import serial
import time
import subprocess
import sys

bdaddr = "98:D3:31:90:71:B1"
port = "/dev/rfcomm2"
baudrate = 9600


def server():
    """The server part of the script. Responsible for the actual communication during voting"""
    # Open the serial port

    ser = serial.Serial(port, baudrate)
    # Print welcome message
    if raw_input("Send enable?(y/n)") == "y":
        ser.write("enable")
#    while True:
#        if ser.in_waiting >= 4:
#            print ser.read(4)


def connect():
    """connect to the slave using the serial port"""
    subprocess.call(["sudo", "rfcomm", "-i", "hci0", "connect", port, bdaddr, "1"])


if __name__ == "__main__":
    if sys.argv[1] == "connect":
        connect()
    elif sys.argv[1] == "runserver":
        server()
