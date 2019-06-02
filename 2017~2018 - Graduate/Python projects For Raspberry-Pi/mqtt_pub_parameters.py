send_data_topic = "hems_dev"
#host = "192.168.137.2"
host = "14.63.213.41"
#host = "166.104.245.40"
user = "loraroot"
password = "cjfgkrwk1"


fixed_paramter =\
	' -t "' + send_data_topic + '"' + \
	' -h "' + host + '"' + \
	' -u ' + user + \
	' -P ' + password + \
	''
