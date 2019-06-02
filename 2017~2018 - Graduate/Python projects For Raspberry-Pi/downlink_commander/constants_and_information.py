PARAMETER_DICTIONARY_INDEX_OF_FPORT = 0
FPORT_AUTO_SENDING					= 1
FPORT_LED							= 2
FPORT_NORMAL						= 3

MAX_PORT							= 2223
MAX_SENDING_INTERVAL				= 65535 # seconds
MAX_LED_CONTROL						= 4

#confirmed = "false"
CONFIRMED = "true"


ask_continue_or_not = "\nDo you want to continue? (Y/N) "


port_number_information = \
"\
1. CONTROL AUTO SENDING\n\
2. CONTROL LED\n\
\n\
3~223: SENDING HEX DATA (FPort)\n\
\n\
\n\
INPUT NUMBER\n\
\n"



auto_sending_control_information = "\
CONTROL AUTO SENDING\n\
\n\
1. STOP\n\
2. CONTINUE\n\
3. SEND ONCE\n\
4~65535: SENDING INTERVAL (second)\n\
\n\
\n\
INPUT NUMBER\n\
\n"


led_control_information = "\
CONTROL LED\n\
\n\
1. GREEN ON\n\
2. RED ON\n\
3. GREEN OFF\n\
4. RED OFF\n\
\n\
\n\
INPUT NUMBER\n\
\n"


hex_string_information = \
	"INPUT HEX STRING\n" + \
	" Example: 12345678ABCDEF\n"