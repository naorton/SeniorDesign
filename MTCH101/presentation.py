import smbus
import time
import RPi.GPIO as GPIO

bus = smbus.SMBus(1)
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(17, GPIO.OUT)
print 'Press Ctrl-C to quit'

while True:

    device_addr = bus.read_byte(0x9)
    print device_addr
    GPIO.setup(17, GPIO.HIGH)
    time.sleep(.5)
    GPIO.setup(17, GPIO.LOW)

