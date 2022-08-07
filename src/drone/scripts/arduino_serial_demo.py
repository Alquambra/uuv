import sys

import serial
import time
import struct

arduino = serial.Serial('/dev/ttyUSB0', 9600, bytesize=serial.EIGHTBITS, timeout=1)

class _Getch:
    """Gets a single character from standard input.  Does not echo to the screen."""
    def __init__(self):
        try:
            self.impl = _GetchWindows()
        except ImportError:
            self.impl = _GetchUnix()

    def __call__(self): return self.impl()


class _GetchUnix:
    def __init__(self):
        import tty, sys

    def __call__(self):
        import sys, tty, termios
        fd = sys.stdin.fileno()
        old_settings = termios.tcgetattr(fd)
        try:
            tty.setraw(sys.stdin.fileno())
            ch = sys.stdin.read(1)
        finally:
            termios.tcsetattr(fd, termios.TCSADRAIN, old_settings)
        return ch


class _GetchWindows:
    def __init__(self):
        import msvcrt

    def __call__(self):
        import msvcrt
        return msvcrt.getch()


getch = _Getch()

time.sleep(2)
lock = True

left_alt = 0
right_alt = 0
left_heading = 0
right_heading = 0
back_alt = 0
light = 0

start_bit = 0x55
len = 11

frame = {
    "header": 0x55,
    "len": 0,
    "data": [0, 0, 0, 0, 0, 0, 0, 0],
    "crc": 0
}

def frame_to_serial(frame):
    data = [
        frame["header"],
        frame["len"],
        *[item for item in frame["data"]],
        frame["crc"]
    ]
    # frame["data"] = bytes(frame["data"])
    data = struct.pack("11B", frame["header"], frame["len"], *frame["data"], frame["crc"])
    return data


while True:

    inp = getch()

    try:
        inp = int(inp)
        if int(inp) in range(-100, 101):
            left_alt = inp * 10
    except ValueError:
        if inp == 'e':
            lock = not lock
        if inp == 'c':
            sys.exit()

    frame["header"] = 0x55
    frame["data"] = [left_alt, 0, 0, 0, 0, 0, lock, 0]
    frame["len"] = 8
    frame["crc"] = sum(frame["data"])
    msg = frame_to_serial(frame)
    arduino.write(msg)
    print(msg)
    print([a for a in msg])
    time.sleep(1)
