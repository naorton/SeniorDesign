
import smbus



MPR121_TOUCHSTATUSL	= 0x00
MPR121_TOUCHSTATUSH = 0x01
MPR121_E0FDL		= 0x04
MPR121_E0FDH		= 0x05
MPR121_TOUCHTH_0	= 0x41
MPR121_RELEASETH_0	= 0x42
MPR121_I2C_ADDR 	= 0x5A
MPR121_ECR			= 0x5E



class MPR121(object):

	def __init__(self):

		self.bus = smbus.SMBus(1)


	def start(self):
		#Puts the device into Run mode.
		old_reg = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_ECR)    
		new_reg = 0b11110001 & old_reg

		self.bus.write_byte_data(MPR121_I2C_ADDR, MPR121_ECR, new_reg)

	def stop(self):
		#Puts the device into Stop mode.
		#Can put device into stop mode using ele_select
		old_reg = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_ECR)
		new_reg = 0b11110000 & old_reg

		self.bus.write_byte_data(MPR121_I2C_ADDR, MPR121_ECR, new_reg)

	def read(self):
		#Reads Electrode filtered data for pin 0, composed of an LSB and MSB.
		value_low = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_E0FDL)
		value_high = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_E0FDH)

		value = (value_high << 8) | value_low

		return value 

	def ele_select(self, pin):
		#Selects measurement electrodes, from ELE0 to ELE0-11, 12 in total.
		#If pin = 0 , then the device is put into stop mode.

		assert pin >= 0 and pin <12 'pin must be between 0-11'

		old_reg = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_ECR)
		new_reg = 0b11110000 | pin		#This line masks the default values for CL and ELEPROX and then ORs it with the 4 bit value for the selected electrodes

		self.bus.write_byte_data(MPR121_I2C_ADDR, MPR121_ECR, new_reg)


	def touch_status(self, pin):
		#Takes in a pin value to return the touch status. Will return 1 if touched, or 0 if released.
		#the MSB on register 0x01 is an over current flag(read and write), 1 if over current is detected and 0 for normal conditions.

		assert pin >= 0 and pin <12 'pin must be between 0-11'

		touch = self.bus.read_word_data(MPR121_I2C_ADDR, MPR121_TOUCHSTATUSL)

		return (touch & (1 << pin)) > 0

	def set_threshold(self, touch, release):
		#This will take in a touch threshold(0-255) and a release threshold(0-255) and write
		#that value to the appropriate registers for all electrodes.

		assert touch >=0 and touch <=255 'touch threshold must be between 0 and 255'
		assert release >=0 and release <=255 'release threshold must be between 0 and 255'

		for i in range(12):
			self.write_byte_data(MPR121_I2C_ADDR, MPR121_TOUCHTH_0 + 2*i, touch)
			self.write_byte_data(MPR121_I2C_ADDR, MPR121_RELEASETH_0 + 2*i, release)


