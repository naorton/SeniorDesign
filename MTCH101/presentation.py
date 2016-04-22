import smbus
import time
<<<<<<< HEAD
import RPi.GPIO as GPIO

bus = smbus.SMBus(1)
GPIO.setmode(GPIO.BCM)
GPIO.setwarnings(False)
GPIO.setup(17, GPIO.OUT)
=======

bus = smbus.SMBus(1)

>>>>>>> fe3ab14b13da8672da39dd6ab66e84e1e73c9305
print 'Press Ctrl-C to quit'

while True:

<<<<<<< HEAD
    device_addr = bus.read_byte(0x9)
    print device_addr
    GPIO.setup(17, GPIO.HIGH)
    time.sleep(.5)
    GPIO.setup(17, GPIO.LOW)

=======
		device_addr = bus.read_byte(0x9)
		print device_addr
		time.sleep(.5)
>>>>>>> fe3ab14b13da8672da39dd6ab66e84e1e73c9305
