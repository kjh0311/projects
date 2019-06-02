// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SENSOR_TYPE_H
#define	SENSOR_TYPE_H


typedef enum
{
	WATER = 2, 
	HOTWATER ,
	GAS      ,
	CALORIE,
	WATT
} SensorType;

#define HEADER_LENGTH	3
#define TAIL_LENGTH		2

#define CALORIE_METER_RESPONSE_SIZE		20
#define WATT_METER_RESPONSE_SIZE		93
#define OTHER_METER_RESPONSE_SIZE		12


#endif	/* SENSOR_TYPE_H */

