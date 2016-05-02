import smbus
import time
import requests
#import RPi.GPIO as GPIO

sensorLocation = {

		 0x09 : 'A0',
		 0x0A : 'A2',
		 0x0B : 'A4',
		 0x0C : 'A6'
}

bus = smbus.SMBus(1)
#GPIO.setmode(GPIO.BCM)
#GPIO.setwarnings(False)
#GPIO.setup(4, GPIO.OUT)

print 'Press Ctrl-C to quit'

while True:

	for sensor in sensorLocation:

		try:
			sensor_output = bus.read_byte(sensor)
		except:
			pass

		if sensor_output == 1:
			requests.get('http://raspberrypi/locations/%s' % (sensorLocation[sensor]))
    	

