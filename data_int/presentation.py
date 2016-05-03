import smbus
import requests
import vending


sensorLocation = {

		 0x09 : 0,
		 0x0A : 1,
		 0x0B : 2,
		 0x0C : 3

}

bus = smbus.SMBus(1)

def sensorRead(address):

	try:
		reading = bus.read_byte(address)
	except:
		reading = 0
		pass
	return reading	

print 'Press Ctrl-C to quit'

while True:

	for address in sensorLocation:

		initial = sensorRead(address)

		if initial == 1:
			#debounce
			for i in range(5):
				data = sensorRead(address)
			if data == 0:
				break
			elif data == 1:
				print sensorLocation[address]
				string = vending.GetProduct(sensorLocation[address])
				vending.TextToSpeech(string)
				while sensorRead(address) == 1:
					pass

    	






