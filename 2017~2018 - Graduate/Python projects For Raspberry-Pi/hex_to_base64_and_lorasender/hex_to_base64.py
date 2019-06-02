

def hex_to_base64 (hex_string):
    import base64


    if len(hex_string) %2 != 0:
        hex_string = "0" + hex_string
    

    hex_data = bytes.fromhex(hex_string)

    #print ( "hex_data: ", end="" )
    #print ( hex_data )

    base64_bytes = base64.b64encode( hex_data )

    return base64_bytes.decode("utf-8")


