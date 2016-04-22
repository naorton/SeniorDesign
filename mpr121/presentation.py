import smbus
import time

bus = smbus.SMBus(1)

print 'Press Ctrl-C to quit'

while True:

		device_addr = bus.read_byte(0x9)
		print device_addr
		time.sleep(.5)
