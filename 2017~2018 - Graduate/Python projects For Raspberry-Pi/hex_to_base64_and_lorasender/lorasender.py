from hex_to_base64 import hex_to_base64
from subprocess import Popen, PIPE


#confirmed = "false"
confirmed = "true"


port_number_information = "input port number (1~223): "

hex_string_information = \
	"input hex string\n" + \
	" Example: 12345678ABCDEF\n"

command_format_string = \
	'mosquitto_pub -h 127.0.0.1' + \
	' -t "application/1/node/0000000000000000/tx"' + \
	' -m "{{\\"confirmed\\": {0},\\"fPort\\":{1},' + \
	'\\"data\\": \\"{2}\\"}}"'


def make_command_string(port, base64_string):
	global confirmed
	return command_format_string.format (confirmed, port, base64_string)


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
	
	
def input_hex_string_and_convert_to_base64():
	while True:
		hex_string = input (hex_string_information)
		try:
			base64_string = hex_to_base64 (hex_string)
			#print ( "base64_string: " + base64_string )
		except:
			print ("check input string")
			continue
		else:
			break
	return base64_string




port = input_port_number ()
base64_string = input_hex_string_and_convert_to_base64 ()

#print ( "base64: " + base64_string )

command_string = make_command_string (port, base64_string)

#print ( "command_string: " + command_string )

Popen([command_string], shell=True, stdout=PIPE)
