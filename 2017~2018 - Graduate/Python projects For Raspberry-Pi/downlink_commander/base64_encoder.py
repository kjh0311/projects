

def int_to_base64 (integer):
	import base64	
	#base64_bytes = base64.b64encode( integer )
	#base64_bytes = base64.b64encode( b'\01' )
	#print ("print bytes")
	#print (bytes([3]))
	#base64_bytes = base64.b64encode(bytes([1]))
	#base64_bytes = base64.b64encode( bytes([integer]) )
	#converted_bytes = (integer).to_bytes(2)	
	#converted_bytes = bytes ([255])
	
	if integer > 255:
		converted_bytes = bytes ( [integer % 256, integer // 256] )
	else:
		converted_bytes = bytes ([integer])
	base64_bytes = base64.b64encode( converted_bytes )
	return base64_bytes.decode("utf-8")



def hex_to_base64 (hex_string):
    import base64


    if len(hex_string) %2 != 0:
        hex_string = "0" + hex_string
    

    hex_data = bytes.fromhex(hex_string)

    #print ( "hex_data: ", end="" )
    #print ( hex_data )

    base64_bytes = base64.b64encode( hex_data )

    return base64_bytes.decode("utf-8")
