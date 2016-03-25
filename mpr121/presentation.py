import smbus
import time

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

for device in range(128):

	try:
		bus.read_byte(device)
		print(hex(device))
	except:
		pass

while True:

	address = input('Enter an address: ')
	command = input('Enter command: ')

	bus.write_byte(address,command)
	time.sleep(.1)
	device_addr = bus.read_byte(address)

	print device_addr