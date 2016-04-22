import smbus
import time
import RPi.GPIO as GPIO

bus = smbus.SMBus(1)
GPIO.setmode(GPIO.BOARD)
GPIO.setup(7, GPIO.OUT)


bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:

    device_output = bus.read_byte(0x9)
    print device_output

    if device_output == 1:

    	GPIO.setup(7, GPIO.HIGH)
    	time.sleep(.5)
    	GPIO.setup(7, GPIO.LOW)
