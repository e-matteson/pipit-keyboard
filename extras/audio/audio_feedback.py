#!/bin/python3

# Requires `aplay` for playing audio files

from __future__ import division

import subprocess
import serial
from time import sleep
import os

tty_name = '/dev/ttyACM0'

sounds = {b'A':'tick1.wav',
          b'W':'tick2.wav',
          b'M':'tick3.wav',
          b'S':'tick4.wav',
          b'U':'tick5.wav'}


def play_wav(filename):
    command = ['aplay', filename]
    DEVNULL = open(os.devnull, 'wb')
    subprocess.Popen(command, stdout=DEVNULL, stderr=DEVNULL)

def open_serial():
    while True:
        try:
            port = serial.Serial(tty_name, 115200, timeout=None)
        except serial.serialutil.SerialException as exception:
            print(exception)
            sleep(5)
        else:
            return port

def monitor_serial():
    while True:
        # open and close to flush old bytes
        port = open_serial()
        port.close()

        port = open_serial()
        while True:
            try:
                code = port.read()
            except serial.serialutil.SerialException as exception:
                # if read failed, start again and try to re-open the port
                print(exception)
                port.close()
                break
            play_wav(sounds[code])

def main():
    monitor_serial()

main()
