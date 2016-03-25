import smbus
import time

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:

	for i in xrange(0, 255):
		bus.write_byte(i,1)
		time.sleep(.1)
		data = bus.read_byte(i)
		print data

	address = input('Enter an address: ')
	command = input('Enter command: ')

	bus.write_byte(address,command)
	time.sleep(.1)
	device_addr = bus.read_byte(address)

	print device_addr