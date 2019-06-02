from subprocess import Popen, PIPE
import file_printer
import mqtt_pub_parameters


def send(line):

	command = 'sudo mosquitto_pub -m "' + line + '"' + \
		mqtt_pub_parameters.fixed_paramter

	Popen([command], shell=True, stdout=PIPE)

	file_printer.create_or_append_file_with_prefix(file_printer.READIED, line)
