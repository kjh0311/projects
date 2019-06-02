from subprocess import Popen, PIPE
import threading
import gateway_controller, sender
import file_printer, mqtt_pub_parameters
from parse_line_and_process import parse_line_and_process




def run_all_threads():

	run_thread(parse_and_process, run_mqtt_sub_for_received())
	run_thread(record_sent_data, run_mqtt_sub_for_sent())


def run_thread(poll_function, parameter = None):

	thread = threading.Thread(target = poll_function, args = (parameter, ))
	thread.start()


def parse_and_process(mqtt_sub):

	while mqtt_sub.poll() is None:
		line = mqtt_sub.stdout.readline().decode('ascii')
		result = parse_line_and_process(line)
		if result != None:
			sender.send(result)
			print("result: " + result)
		#gateway_controller.restart_gateway_repair_timer()
		

def record_sent_data(mqtt_sub):
	while mqtt_sub.poll() is None:
		line = mqtt_sub.stdout.readline().decode('ascii')
		line = line.rstrip('\n')
		file_printer.create_or_append_file_with_prefix(file_printer.SENT, line)



def run_mqtt_sub_for_received():
	return Popen(['sudo mosquitto_sub -v\
				 -t "application/+/node/+/rx" \
				 -u loraroot -P cjfgkrwk1'],\
				shell=True, \
				stdout=PIPE)


def run_mqtt_sub_for_sent():
	command = 'sudo mosquitto_sub ' + \
		mqtt_pub_parameters.fixed_paramter
	return Popen([command], shell=True, stdout=PIPE)
	
	
	