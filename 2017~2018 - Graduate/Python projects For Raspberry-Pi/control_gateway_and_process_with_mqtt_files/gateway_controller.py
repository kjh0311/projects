import time
import gpio_controller
import threading
from subprocess import call, Popen, PIPE
from file_printer import make_file_name_with_date_and_ext, PACKET_FORWARDER
from file_printer import create_or_append_file_with_prefix, RESETTED_TIME_OF_PACKET_FORWARDER



RESET_TIME = 40 # seconds



gateway = None
repair_timer = None



def run_gateway():
	global gateway

	#gpio_controller.RST_TO_LOW()

	result_file_name = make_file_name_with_date_and_ext(PACKET_FORWARDER)
	result_file = open(result_file_name, "w")

	gateway = Popen(\
			['./lora_pkt_fwd'],\
			#shell=True, stdout=PIPE)
			shell=True, \
			stdin=PIPE, \
			stdout=result_file)

	#time.sleep(1)
	while gateway.poll() is None:
		pass

	return gateway
	


def start_gateway_repair_timer():

	global repair_timer
	repair_timer = threading.Timer\
		(RESET_TIME, reset_gateway_and_timer_and_record)
	repair_timer.start()
	return repair_timer



def restart_gateway_repair_timer():
	global repair_timer
	if repair_timer != None:
		repair_timer.cancel()
		return start_gateway_repair_timer()
	else:
		return None



def reset_gateway_and_timer_and_record():
	global gateway, repair_timer
	print('reset_gateway')
	if gateway != None:
		gateway.kill()
	gateway = run_gateway()
	
	repair_timer = restart_gateway_repair_timer()

	string_time = time.strftime('%Y-%m-%d %H:%M:%S')
	create_or_append_file_with_prefix(\
		RESETTED_TIME_OF_PACKET_FORWARDER,\		
		string_time)	
