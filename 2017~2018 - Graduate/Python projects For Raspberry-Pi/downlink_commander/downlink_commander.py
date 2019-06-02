#from int_to_base64 import int_to_base64
import base64_encoder

from subprocess import Popen, PIPE
#from ctypes import *
from constants_and_information import *


input_parameter_dictionary = {}
input_parameter_dictionary[PARAMETER_DICTIONARY_INDEX_OF_FPORT] = ("port", port_number_information, MAX_PORT)
input_parameter_dictionary[FPORT_AUTO_SENDING] = ("auto sending control value", auto_sending_control_information, MAX_SENDING_INTERVAL)
input_parameter_dictionary[FPORT_LED] = ("led control value", led_control_information, MAX_LED_CONTROL)


print (input_parameter_dictionary[FPORT_LED][0])


command_format_string = \
	'mosquitto_pub -h 127.0.0.1' + \
	' -t "application/1/node/0000000000000000/tx"' + \
	' -m "{{\\"confirmed\\": {0},\\"fPort\\":{1},' + \
	'\\"data\\": \\"{2}\\"}}"'


def make_command_string(string_port, base64_string):
	global command_format_string, CONFIRMED
	return command_format_string.format (CONFIRMED, string_port, base64_string)


def input_nonnegative_integer_until_correct (parameter_tuple):
	
	string_name = parameter_tuple[0]
	information = parameter_tuple[1]
	maximum		= parameter_tuple[2]
	
	while True:
		string_value = input (information)
		try:
			# if port is not number string, it rase ValueError
			int_value = int(string_value)
			# The range of port number is 1 to 223
			if int_value <1 or int_value > maximum:
				raise ValueError
		except ValueError:
			print ("{0} must be number in 1 to {1}".format (string_name, maximum) )
			continue
		else:
			break	
	return string_value, int_value



def input_hex_string_and_convert_to_base64():
	while True:
		hex_string = input (hex_string_information)
		hex_string = hex_string.upper()
		try:
			base64_string = base64_encoder.hex_to_base64 (hex_string)
			#print ( "base64_string: " + base64_string )
		except:
			print ("check input string")
			continue
		else:
			break
	return base64_string



while True:
	string_port, int_port = input_nonnegative_integer_until_correct(input_parameter_dictionary[PARAMETER_DICTIONARY_INDEX_OF_FPORT])

	print ("\nport: " + string_port)
	print ("\n")

	if int_port < FPORT_NORMAL:	
		string_value, int_value = input_nonnegative_integer_until_correct (input_parameter_dictionary[int_port])
		print ("value: " + string_value)
		base64_string = base64_encoder.int_to_base64 (int_value)
	else:
		base64_string = input_hex_string_and_convert_to_base64()

	command_string = make_command_string (string_port, base64_string)

	#print ( "command_string: " + command_string )

	Popen([command_string], shell=True, stdout=PIPE)
	
	
	continue_or_not = input (ask_continue_or_not)
	continue_or_not = continue_or_not.upper()
	if continue_or_not == 'Y':
		print ("\n")
		continue
	else:
		break
