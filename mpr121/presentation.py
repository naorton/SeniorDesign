import smbus
import time

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:

	address = input('Enter an address: ')
	command = input('Enter command: ')

	if command == 1:

		bus.write_byte(address,command)
		time.sleep(.3)
		device_addr = bus.read_byte(address)
		print device_addr

	elif command == 2:

		bus.write_byte(address, command)
		time.sleep(.3)