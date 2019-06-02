#ifndef DATA_LENGTH_H
#define	DATA_LENGTH_H

typedef enum {
	len_devaddr			= 4,
	len_deveui			= 8,
	len_appeui			= 8,
	len_nwkskey			= 16,
	len_appskey			= 16,
	len_appkey			= 16,
	len_sync			= 1,
	len_status			= 2,			
	len_class			= 1,
	len_pwridx			= 1,
	len_dr				= 1,
	len_bat				= 1,
	len_retx			= 1,
	len_linkchk			= 2,
	len_rxdelay1		= 2,
	len_rxdelay2		= 2,
	len_acceptDelay1	= 2,
	len_acceptDelay2	= 2,
	len_upctr			= 4,
	len_dnctr			= 4,
	len_adr				= 1,
	len_ar				= 1,
} DataLength;


//static DataLength length = { 4, 8, 8, ;


/*
typedef struct {
	uint8_t devaddr, deveui;
} DataLength;
*/


//const uint8_t length_array[] = { 4, 8 };


#endif	/* DATA_LENGTH_H */

