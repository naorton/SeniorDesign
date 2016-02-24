
import smbus


MPR121_E0FDL		= 0x04
MPR121_E0FDH		= 0x05
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

		assert pin >= 0 and pin <=12 'pin must be between 0-12'

		old_reg = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_ECR)
		new_reg = 0b11110000 | pin		#This line masks the default values for CL and ELEPROX and then ORs it with the 4 bit value for the selected electrodes

		self.bus.write_byte_data(MPR121_I2C_ADDR, MPR121_ECR, new_reg)

