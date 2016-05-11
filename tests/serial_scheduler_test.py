#!/usr/bin/python
import serial
import time

ser = serial.Serial( port='/dev/ttyUSB0', baudrate=57600 )

t = time.time()
while True:
    for char in ser.read(1):
	print time.time() - t, ","
	t = time.time()

ser.close()
