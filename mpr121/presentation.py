import smbus

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:
	address = input('Enter an address: ')
	blink = input('Enter the number of led blinks: ')

	bus.write_byte(address,blink)
	data = bus.read_byte(address)
	print data	