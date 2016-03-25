import smbus
import time

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:
	address = input('Enter an address: ')
	command = input('Enter command: ')

	bus.write_byte(address,command)
	time.sleep(1)
	data = bus.read_byte(address)

	print data	