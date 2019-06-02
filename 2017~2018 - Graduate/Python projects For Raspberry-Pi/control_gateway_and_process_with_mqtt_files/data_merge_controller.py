import ctypes
import parse_line_and_process


c_uint8 = ctypes.c_uint8


# way of access: splited_data_list[i][j]

#usage
#add device: splited_data_list_dictionary[dev_eui] = []
#add data in device: splited_data_list_dictionary[dev_eui][partion_index] = data
splited_data_dictionary = {}



class DataMergeInformation_nibbles(ctypes.Structure):
    _fields_ = [
            ("max_partition_index", c_uint8, 4),
            ("partition_index", c_uint8, 4),
        ]

class DataMergeInformation(ctypes.Union):
    _fields_ = [("nibbles", DataMergeInformation_nibbles),
                ("as_byte", c_uint8)]



def check_if_hex_data_is_partial(hex_received_data_header):
	if hex_received_data_header != 0xFF and \
	   hex_received_data_header != 0:
		return True
	else:
		return False



def store_partial_data_or_merge \
	( dev_eui, data_merge_information_byte, data_without_header ) :
	global splited_data_dictionary


	data_merge_information = DataMergeInformation()
	data_merge_information.as_byte = data_merge_information_byte
	max_partition_index = data_merge_information.nibbles.max_partition_index
	partition_index = data_merge_information.nibbles.partition_index

	#add device: splited_data_dictionary[dev_eui] = {}
	#add data in device: splited_data_dictionary[dev_eui][partion_index] = hex_data
	#splited_data_dictionary = {}
	if not dev_eui in splited_data_dictionary :
		splited_data_dictionary[dev_eui] = {}

	splited_data_dictionary[dev_eui][partition_index] = data_without_header
	# all partition received
	if all_partition_received(dev_eui, max_partition_index):
		return merge_splited_data(splited_data_dictionary[dev_eui])
	else:
		return None# only store, not send


def all_partition_received(dev_eui, max_partition_index):
	global splited_data_dictionary

	return len(splited_data_dictionary[dev_eui]) - 1 == max_partition_index


def merge_splited_data(splited_data_dictionary):

	merged_data = bytearray()

	for partition_index in splited_data_dictionary:
		splited_data = splited_data_dictionary[partition_index]
		#print( str(splited_data) )
		print("splited_data: " + parse_line_and_process.hex_data_to_string(splited_data) )
		merged_data.extend(splited_data)

	return merged_data
