// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef KEVIN_LAB_DATA_FORMAT_H
#define	KEVIN_LAB_DATA_FORMAT_H

typedef union {
	uint8_t data[66];
	struct {
		uint8_t id[20], time[14], meter, mwh[8], m_3[8], sc[4], rc[4], start[2], end[2], err, err_con, real;	
	};
} Kevin_Lab_SendingFormatBody;

#endif	/* KEVIN_LAB_DATA_FORMAT_H */

