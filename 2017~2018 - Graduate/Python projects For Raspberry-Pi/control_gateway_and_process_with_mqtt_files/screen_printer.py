import parse_line_and_process
import time


def print_time_and_eui_fCnt(dev_eui, fCnt):
	string_time = time.strftime('%H:%M:%S')

	print()
	print()
	print()
	print("time: " + string_time)
	print()
	print()
	print()
	print ("dev_eui: " + str(dev_eui) )
	print ("fCnt: " + str(fCnt) )


def print_time_and_received_data(hex_received_data):
	string_received_data = parse_line_and_process.hex_data_to_string( hex_received_data )
	#print ("meter_type(fPort): " + str(fPort) )
	print ("received data: " + string_received_data)
