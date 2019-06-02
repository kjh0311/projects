

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


