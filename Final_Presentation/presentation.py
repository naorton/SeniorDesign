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

	for address in sensorLocation:

		if sensorRead(address) == 1:
			#debounce
			for i in range(5):
				data = sensorRead(address)
				print data
			if data == 0:
				break
			elif data == 1:
				print sensorLocation[address]
				requests.get('http://raspberrypi/locations/%s' % (sensorLocation[address]))
				while sensorRead(address) == 1:
					pass

    	

def sensorRead(address):

	try:
		data = bus.read_byte(address)
	except:
		pass
	return data	




