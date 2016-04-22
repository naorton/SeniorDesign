import smbus
import time
import RPi.GPIO as GPIO

bus = smbus.SMBus(1)
GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)


bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:

    device_output = bus.read_byte(0x9)

    if device_output == 1:
    	print device_output
    	GPIO.setup(4, GPIO.HIGH)
    	time.sleep(.5)
    	GPIO.setup(4, GPIO.LOW)
