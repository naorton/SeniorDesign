
import smbus


MPR121_E0FDL	= 0x04
MPR121_E0FDH	= 0x05
MPR121_I2C_ADDR = 0x5A
MPR121_ECR		= 0x5E









class MPR121(object):

	def __init__(self):

		self.bus = smbus.SMBus(1)


	def start(self):

		old_reg = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_ECR)
		new_reg = 0b11110001 & old_reg

		self.bus.write_byte_data(MPR121_I2C_ADDR, MPR121_ECR, new_reg)

	def stop(self):

		old_reg = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_ECR)
		new_reg = 0b11110000 & old_reg

		self.bus.write_byte_data(MPR121_I2C_ADDR, MPR121_ECR, new_reg)

	def read(self):

		value_low = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_E0FDL)
		value_high = self.bus.read_byte_data(MPR121_I2C_ADDR, MPR121_E0FDH)

		value = (value_high << 8) | value_low

		return value 

