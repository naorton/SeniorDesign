import smbus
import time
import requests
#import RPi.GPIO as GPIO

sensorLocation = {
		 0x09 : 'A0',
		 0x10 : 'A2',
		 0x11 : 'A4',
		 0x12 : 'A8',	
}

bus = smbus.SMBus(1)
#GPIO.setmode(GPIO.BCM)
#GPIO.setwarnings(False)
#GPIO.setup(4, GPIO.OUT)

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:

	for sensor in sensorLocation:

		sensor_output = bus.read_byte(sensor)

		if sensor_output == 1:
			requests.get('http://raspberrypi/locations/%s' % (sensorLocation[sensor]))
    	

