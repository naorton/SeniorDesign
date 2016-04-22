import smbus
import time

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'


def getDevicesOnBus(busNo):
    devices = []
    bus = SMBus(busNo)
    for addr in range(3, 178):
        try:
            bus.write_quick(addr)
            devices += [addr]
        except IOError:
            pass
    return devices

devices = getDevicesOnBus(1)
print(devices)

while True:
	
	print "Choose a command: \n1.Scan the bus\n2.Change address of sensor\n3."
	command = input('Enter command: ')
	print "Enter an address"
	address = input('Enter an address: ')

	if command == 1:

		bus.write_byte(address,command)
		time.sleep(.5)
		device_addr = bus.read_byte(address)
		print device_addr

	elif command == 2:

		bus.write_byte(address, command)
		time.sleep(.5)