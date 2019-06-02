import time
import os


READIED = 0
SENT    = 1
PACKET_FORWARDER	= 2 # only used in open, do not call write or append
RESETTED_TIME_OF_PACKET_FORWARDER		= 3
ADMIN	= 4				# only used in open, do not call write or append
FCNT	= 5



# format of file name
# readied_201803141624.txt
# sent_201803141624.txt
prefix_file_name={}
prefix_file_name[READIED] = "readied_"
prefix_file_name[SENT] = "sent_"
prefix_file_name[PACKET_FORWARDER] = "packet_forwarder_"
prefix_file_name[RESETTED_TIME_OF_PACKET_FORWARDER] = "resetted_time_of_packet_forwarder_"
prefix_file_name[ADMIN] = "admin_"
prefix_file_name[FCNT] = "fcnt_"


record_file_extension = ".txt"

file_name = {}
file_name[READIED] = None
file_name[SENT] = None
file_name[RESETTED_TIME_OF_PACKET_FORWARDER] = None
file_name[FCNT] = None



def create_or_append_file_with_prefix(PREFIX, line):
	if file_name[PREFIX] == None:
		file_name[PREFIX] = make_file_name_with_date_and_ext(PREFIX)
		write_file(file_name[PREFIX], line)
	else:
		append_file(file_name[PREFIX], line)



def make_file_name_with_date_and_ext(PREFIX):
	prefix = prefix_file_name[PREFIX]
	string_time = time.strftime('%Y%m%d%H%M%S')
	return prefix + string_time + record_file_extension



def print_time_and_eui_fCnt(dev_eui, fCnt):
	line = "dev_eui: {0}, fCnt: {1}, time: {2}"\
			.format(dev_eui, fCnt,\
			 time.strftime('%Y%m%d%H%M%S') )
	create_or_append_file_with_prefix(FCNT, line)



is_first_packet_time_writed = False
count = 0

def count_line_and_write_file():
	global is_first_packet_time_writed
	global count

	string_time = time.strftime('%Y/%m/%d %H:%M:%S')
	if is_first_packet_time_writed:
		write_file("counts_test/last_packet_time.txt", string_time)
	else:
		write_file("counts_test/first_packet_time.txt", string_time)
		is_first_packet_time_writed = True

	count = count + 1
	write_file("counts_test/count.txt", str(count))



def write_file(str_file_name, str_text):
	print ("create and write file name:" + str_file_name)
	print ("content: " + str_text)
	#if os.path.isfile(str_file_name):
	#	os.remove(str_file_name)
	f = open(str_file_name, 'w')
	#f.truncate()
	f.write(str_text + "\n")
	f.close()

	os.chmod(str_file_name, 0o777)



def append_file(str_file_name, str_text):
	print ("append file name:" + str_file_name)
	print ("content: " + str_text)
	original_size = os.path.getsize(str_file_name)
	new_size = original_size
	while original_size == new_size:
		with open(str_file_name, "a") as myfile:
			myfile.write(str_text + "\n")
		new_size = os.path.getsize(str_file_name)
