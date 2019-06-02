from int_to_base64 import int_to_base64
from subprocess import Popen, PIPE
from ctypes import *


FPORT_SENDING_INTERVAL = 1

#confirmed = "false"
CONFIRMED = "true"

sending_interval_information = \
	"input sending interval (4~65535): "

command_format_string = \
	'mosquitto_pub -h 127.0.0.1' + \
	' -t "application/1/node/0000000000000000/tx"' + \
	' -m "{{\\"confirmed\\": {0},\\"fPort\\":{1},' + \
	'\\"data\\": \\"{2}\\"}}"'


def make_command_string(base64_string):
	global CONFIRMED, FPORT_SENDING_INTERVAL
	return command_format_string.format (CONFIRMED, FPORT_SENDING_INTERVAL, base64_string)


def input_port_number():
	while True:
		port = input (port_number_information)
		try:
			# if port is not number string, it rase ValueError
			int_port = int(port)
			# The range of port number is 1 to 223
			if int_port <1 or int_port > 223:
				raise ValueError
		except ValueError:
			print ("port must be number in 1 to 223")
			continue
		else:
			break
	return port
	
	
def input_sending_interval_and_convert_to_base64():
	
#>>> x = (ctypes.c_ulong*5)()
	while True:
		sending_interval_string = input (sending_interval_information)
		try:
			print (sending_interval_string)
			#sending_interval_low = int (sending_interval_string[2])
			#sending_interval_high = int (sending_interval_string[0])
			sending_interval = int (sending_interval_string)
			print (sending_interval)
			
			if sending_interval < 4 or sending_interval > 65535:
				if sending_interval < 4:
					raise ValueError
					print ("less than 4")
				elif sending_interval > 65535:
					raise ValueError
					print ("more than 65535")				
				
			base64_string = int_to_base64 (sending_interval)
			print ( "base64_string: " + base64_string )
		except ValueError:
			print ("sending interval must be number in 4 to 65535")
			continue
		except:
			print ("check input")
			continue
		else:
			break
	return base64_string


base64_string = input_sending_interval_and_convert_to_base64 ()
command_string = make_command_string (base64_string)

#print ( "command_string: " + command_string )

Popen([command_string], shell=True, stdout=PIPE)
