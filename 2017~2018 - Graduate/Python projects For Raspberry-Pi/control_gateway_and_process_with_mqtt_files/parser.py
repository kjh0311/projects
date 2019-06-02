import json
import base64
import time
import file_printer
import screen_printer
import data_merge_controller


# usage: previous_fCnt_dictionary[dev_eui] = fCnt
previous_fCnt_dictionary = {}



def parse_line_and_process(mqtt_line):
	global previous_fCnt_dictionary
	print (mqtt_line)
	file_printer.count_line_and_write_file()
	json_string = get_json_string(mqtt_line)
	dictionary = json.loads(json_string)


	dev_eui = dictionary['devEUI']
	fCnt = dictionary['fCnt']
	screen_printer.print_time_and_eui_fCnt(dev_eui, fCnt)

	fCnt_is_same = check_if_fCnt_is_same_previous(dev_eui, fCnt)
	if fCnt_is_same:
		print ("Drop: fCnt is same previous")
		# if result is none,
		# do not send result in 'poll' function in 'mqtt_polling_controller.py'
		return None
	else:
		previous_fCnt_dictionary[dev_eui] = fCnt


		base64_data = dictionary['data']
		hex_received_data = base64.b64decode(base64_data)
		screen_printer.print_time_and_received_data(hex_received_data)
		hex_received_data_header = hex_received_data[0]
		hex_received_data_without_header = hex_received_data[1:]


		hex_data_is_partial = data_merge_controller.check_if_hex_data_is_partial(hex_received_data_header)
		if hex_data_is_partial:
			hex_received_data = data_merge_controller.\
				store_partial_data_or_merge(dev_eui, hex_received_data_header, hex_received_data_without_header)
		else:
			hex_received_data = hex_received_data_without_header


		# if partitial_data is not merged (because not yet all partion received),
		# hex_received_data is None
		if hex_received_data == None:
			return None
		else:
			meter_type = dictionary['fPort']
			string_data = process_hex_data( dev_eui, meter_type, hex_received_data )
			return string_data



def get_json_string(line):
	return line[line.index('{'):]



def check_fCnt_for_device():
	global previous_fCnt_dictionary
	return (dev_eui in previous_fCnt_dictionary)\
	and (fCnt == previous_fCnt_dictionary[dev_eui])



CALORIE = 0x5
WATT = 0x6
#def send_error_data(fPort):
#	if meter_type == WATT:
#		string_data = create_error_string_data()
def process_hex_data( dev_eui, meter_type, hex_data ):
	if meter_type == WATT:
		start = 'e'
		end = 'f'
	else:
		start = 'a'
		end = 'b'
	body_cnt = '1 '
	#serial_20byte = "2018"+dev_eui
	serial_20byte = "test-2018-6-0001    "
	string_time = time.strftime('%Y%m%d%H%M%S')
	# '0': normal, '1': error, this is normal supposed
	err_con = '0'
	# '0': test, '1':real
	test_or_real = '0'

	length= len(hex_data)
	string_meter_type = format(meter_type, 'X')

	print ("\n\n")
	print ("hex_data length: " + str(length) )
	if hex_data[0] == 0xFF:
		err_con = "1" # error
		string_data = "0" * 8 * 22
		node_data = "0" * 8
	else:
		err_con = "0" # normal

		node_data = hex_data[length-4:length]
		hex_data = hex_data[0:length-4]
		if meter_type == WATT:
			string_data = hex_watt_data_to_string(hex_data)
		elif meter_type == CALORIE and length == 19:
			string_data = hex_calorimeter_data_to_string(hex_data)
		elif 0x02 <= meter_type and meter_type <= 0x04 and length == 11:
			string_data = hex_other_meter_data_to_string(hex_data)
		else:
			print ("DROP!")
			return None

		node_data = hex_data_to_string(node_data)

	print ("string_data length: " + str(len(string_data)) )
	print ("string_node_data length: " + str(len(node_data)) )
	print ("\n\n")

	if meter_type == WATT:
		result = start + body_cnt + serial_20byte + string_time + string_meter_type + \
			err_con + string_data + node_data + end
	else:
		result = start + body_cnt + serial_20byte + string_time + string_meter_type + \
			string_data + err_con + test_or_real + node_data + end
	print ("result: " + result)
	return result



def hex_calorimeter_data_to_string(hex_data):
	string = ""
	last_index = len(hex_data)-1
	for i in range(0, last_index):
		string += format(hex_data[i], '02X')
	string += format(hex_data[last_index], 'X')
	return string



def hex_other_meter_data_to_string(hex_data):
	string = ""
	last_index = len(hex_data)-1
	#empty calori
	string += "00000000"
	# 4byte hex to 8byte ascii
	string += hex_data_to_string(hex_data[0:4])
	#empty celcious
	string += "00000000"
	string += hex_data_to_string(hex_data[4:6])
	string += format(hex_data[last_index], 'X')
	return string



def hex_watt_data_to_string( hex_data ):

#	listed_data = list( hex_data )
#	for i in range(0, len(listed_data), 4):
#		listed_data[i:i+4] = process_watt_data_4bytes( listed_data[i:i+4] )

#	hex_data = bytes ( listed_data )
	string_data = hex_data_to_string( hex_data )

	return string_data


def hex_data_to_string(hex_data):
	string = ""
	for one in hex_data:
		string += format(one, '02X')
	return string


def process_watt_data_4bytes( data_4bytes ):

	list_2bytes = [0,0]
	list_2bytes[0:2] = data_4bytes[0:2]
	data_4bytes[0:2] = data_4bytes[2:4]
	data_4bytes[2:4] = list_2bytes[0:2]

	return data_4bytes
