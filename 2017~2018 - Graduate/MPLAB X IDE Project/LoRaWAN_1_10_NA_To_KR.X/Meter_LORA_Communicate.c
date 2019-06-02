/*
 * File:   UART_LORA_Communicate.c
 * Author: 김진희
 *
 * Created on 2018년 2월 1일 (목), 오후 7:54
 */


#include "mcc_generated_files/mcc.h"
#include "Timer_In_LoRaMote.h"
#include "mcc_generated_files/LoRaWAN/sw_timer.h"
#include "mcc_generated_files/LoRaWAN/lorawan_na.h"
#include "meter_protocol.h"
#include "led.h"
#include "UART_Print_Functions.h"


//#define SENDING_HEADER


#define SENSOR_TYPE		WATER
static SensorType sensor_type = SENSOR_TYPE;
extern LoRa_t loRa;
//#define METER_READ_COUNT	10000
#define METER_READ_COUNT	400000
static TransmissionType_t confirmed_or_not = CNF;

static bool auto_sending = true;
//TransmissionType_t confirmed_or_not = UNCNF;


//#define METER_REQUEST_INTERVAL			20000	//ms
//#define METER_REQUEST_INTERVAL			   17	// second
#define DEFAULT_SEND_INTERVAL				15UL	// second, range: 4~65535
//#define METER_REQUEST_INTERVAL			   8	// second
#define METER_RECEIVE_INTERVAL			   20	//ms, transition
#define LORA_RESEND_INTERVAL				    5	// second
#define METER_RECEIVE_TIMEOUT_INTERVAL	 5000	//ms

#define FIX_INTERVAL					   50


// 3bytes structure
typedef union {
	uint8_t byte;
	struct {
		uint8_t max_partion_index	:4;
		uint8_t partion_index		:4; // number of one partion
	};
}DataMergeInformation;

static DataMergeInformation data_merge_information;

static uint8_t meter_request_timer_id;
static uint8_t meter_receive_timer_id;
static uint8_t lora_send_timer_id;
static uint8_t meter_one_receive_timer_id;
static uint8_t meter_receive_timeout_timer_id;


static MeterReadBuffer_t meterReadBuffer;

uint8_t receiving = 0;
static uint8_t sending = 0;
static uint8_t max_size;

static uint8_t receive_ended = 1;

static uint16_t interval_of_sending = DEFAULT_SEND_INTERVAL;


void delay_seconds(uint8_t seconds);
uint8_t LORAWAN_GetMaxPayloadSize (void);
uint8_t Get_SwitchValue(void);
uint8_t get_length(SensorType sensor_type);
uint8_t validate_head_data(SensorType sensor_type);
static LorawanError_t lora_send_meter_data(SensorType sensor_type);
uint8_t read_byte();


LorawanError_t meter_request_callback();
LorawanError_t meter_receive_callback();
void lora_send_callback();
void meter_one_receive_callback();
void meter_receive_timeout_callback();
//void meter_request_data(SensorType sensor_type);
void delay_seconds(uint8_t seconds);

char* SendingControl (uint8_t* pData, uint8_t data_length);


void Meter_LORA_Communicate()
{	
	uint32_t count = 0; 
	LATC5 = 1;
	sensor_type = Get_SwitchValue() + 2;
	LorawanError_t result, prev_result;

	prev_result = OK;
	while (1)
	{		
		LORAWAN_Mainloop();		
		if ( loRa.macStatus.macState == IDLE )
		{
			//uint16_t a = 0x123;
			//result = LORAWAN_Send(UNCNF, sensor_type, &a, 1);
			result = meter_request_callback();
			if (result == OK)
			{
				delay_seconds (interval_of_sending);
				LORAWAN_SetCurrentDataRate (3);
			}
		}		
	}
}


char* SetAutoSending (bool true_or_false);
char* SendOnce();
char* SetSendingInterval(uint16_t interval);

char* SendingControl (uint8_t* pData, uint8_t data_length) // length must be 2 bytes.
{
	uint16_t two_byte_data, *pTwoBytes;
	switch (data_length) {
		case 1:
			two_byte_data = (uint16_t) pData[0];
			break;
		case 2:
			pTwoBytes = (uint16_t*) pData;
			two_byte_data = *pTwoBytes;
			break;
		default:
			return "data length must be 1 or 2 bytes";
	}
	
	
	switch (two_byte_data) {
		case 0UL:
			return "sending control value can't be zero.";
		case 1UL:
			return SetAutoSending (false);
		case 2UL:
			return SetAutoSending (true);
		case 3UL:
			//return SendOnce();
			return "function SendOnce is not yet implemented";
		default:
			return SetSendingInterval (two_byte_data);
	}
}


char* SetAutoSending (bool true_or_false)
{
	static uint8_t buffer[50];
	char* string_result;
	
	auto_sending = true_or_false;
	
	if (auto_sending==true) {
		string_result = "true";
	} else {
		string_result = "false";
	}	
	sprintf(buffer, "auto sending is set to %s", string_result);
	return buffer;
}


char* SendOnce()
{
	LorawanError_t result;
	
	result = meter_request_callback();
	if (result == OK)
		return "Success in sending once";
	else
		return "Faliure in sending once";
}


char* SetSendingInterval(uint16_t interval)
{
	static uint8_t buffer[50];
	interval_of_sending = interval;	
	sprintf(buffer, "sending interval is set to %u seconds", interval_of_sending);
	return buffer;
}



LorawanError_t meter_request_callback()
{
	LorawanError_t result;
	//RedLedOn();	

	meter_rs485_enable();
	meter_request_data(sensor_type);
	sending = 1;
	
	//uint8_t a = 0xFF;
	//result = LORAWAN_Send(UNCNF, sensor_type, &a, 1);	

	// 20ms 뒤에 데이터를 수신함.
	__delay_ms(20);
	result = meter_receive_callback();
	//if (result == OK)
	//{
	//	__delay_ms(20);
	//}
	//StartTimer( meter_receive_timer_id, METER_RECEIVE_INTERVAL );	
	
	return result;
	
	//LATC5 = 1;
	
	/*
	static uint8_t count = 0;	
	count++;
	if ( count > 100 )
	{
		count-= 100;
		//RedLedOn();	
	
		meter_rs485_enable();
		meter_request_data(sensor_type);
		sending = 1;

		// 20ms 뒤에 데이터를 수신함.
		StartTimer( meter_receive_timer_id, METER_RECEIVE_INTERVAL );	
		//LATC5 = 1;
	}
	else
	{
		StartTimer( meter_request_timer_id, METER_REQUEST_INTERVAL );
	}
	 */	
}


LorawanError_t meter_receive_callback()
{
	LorawanError_t result;
	//uint8_t a = 0xFF;
	//result = LORAWAN_Send(UNCNF, sensor_type, &a, 1);
	//return result;
	// first one byte is space for data_merge_information
	uint8_t length = get_length(sensor_type) + 1;	
	uint8_t* data = meterReadBuffer.data;	
	uint8_t result_of_validate;	
	// expire 설정
	//StartTimer( meter_receive_timeout_timer_id, METER_RECEIVE_TIMEOUT_INTERVAL );	
	sending = 0;
	meter_rs485_disable();
	receiving = 1;	
	// block until get head data
	//uint8_t a = 0xFF;
	//return LORAWAN_Send(UNCNF, sensor_type, &a, 1);
	
#ifdef SENDING_HEADER
	result_of_validate = 1;
#else
	result_of_validate = validate_head_data(sensor_type);
	length -= HEADER_LENGTH;
#endif
	//result_of_validate = 0;
	if ( result_of_validate )
	{		
		// data[0]: single data or data number
		for ( uint8_t i = 1; i < length ; i++  )
		{
			uint8_t received = 0;			
			//for (uint32_t j=0; j<1000; j++)
			for (uint32_t j=0; j<METER_READ_COUNT; j++)
			//while(1)
			{
				LORAWAN_Mainloop();
				//__delay_ms(1);
				if ( eusart1RxCount )
				{
					data[i] = EUSART1_Read();
					//EUSART1_Read();
					//memcpy(data + (4*i), &j, 4);
					received = 1;
					break;
				}			
			}

			if ( received )
			{	
				received = 0;
			}
			else
			{			
				uint8_t a = 0xFC;
				result = LORAWAN_Send(confirmed_or_not, sensor_type, &a, 1);
				break;
				//StartTimer( meter_request_timer_id,	METER_REQUEST_INTERVAL );
			}
		}

		// tail은 걍 버림
		length -= TAIL_LENGTH;

		meterReadBuffer.length = length;
		result = lora_send_meter_data(sensor_type);
		//uint8_t a = 0xFF;
		//result = LORAWAN_Send(UNCNF, sensor_type, &a, 1);
	}
	else
	{
		uint8_t a = 0xFD;
		result = LORAWAN_Send(confirmed_or_not, sensor_type, &a, 1);
		//StartTimer( meter_request_timer_id,	METER_REQUEST_INTERVAL );
	}
	
	
	//receive_ended = 1;
	//StartTimer( meter_request_timer_id, METER_REQUEST_INTERVAL );
	//SwTimerStart( meter_request_timer_id );
	/*

	*/
	return result;
}


uint8_t read_byte()
{
	/*
	uint8_t received = 0;
	
	for (uint16_t j=0; j<1000; j++) {			
		if ( eusart1RxCount ) {
			received_data[i] = EUSART1_Read();
			received = 1;
			break;
		}			
	}

	if ( received )
	{	
		received = 0;
	}
	else
	{			
		return 0;
	}
	*/
	/*
	uint32_t i;
	for(i=0; 0 == eusart1RxCount || i < 100000; i++);
	
	if (i >= 100000)
		return 0;
	else
		return EUSART1_Read();
	*/
	return 0;
}


static LorawanError_t lora_send_meter_data(SensorType sensor_type)
{
	LorawanError_t result;
	uint8_t *data;
	uint8_t length, max_length, i;
	
	data = meterReadBuffer.data;
	length = meterReadBuffer.length;
	max_length = LORAWAN_GetMaxPayloadSize ();	
	
	if ( length + 4 <= max_length )
	{
		// attatch data_merge_information to head
		data[0] = 0; // max_partion_index and partion_index are 0.		
		// attatch sensor in mote data to tail
		i = length;
		data[i] = 0x12; data[i+1] = 0x34; i+=2;
		data[i] = 0x12; data[i+1] = 0x34; i+=2;
		length = i;
		meterReadBuffer.length = length;
		//UART_Put_Hex(data, length);
		result = LORAWAN_Send(confirmed_or_not, sensor_type, data, length);
		//result = LORAWAN_Send(UNCNF, sensor_type, 0, 1);
	}
	else
	{		
		// attatch data_merge_information to head
		data_merge_information.max_partion_index = 1;
		data_merge_information.partion_index = 0;
		data[0]= data_merge_information.byte;		
		result = LORAWAN_Send(confirmed_or_not, sensor_type, data, max_length);
		if (result == OK)
		{
			delay_seconds(LORA_RESEND_INTERVAL);
			// attatch data_merge_information to head
			data_merge_information.max_partion_index = 1;
			data_merge_information.partion_index = 1;
			data[max_length-1] = data_merge_information.byte;
			
			i = length;
			data[i] = 0x12; data[i+1] = 0x34; i+=2;
			data[i] = 0x12; data[i+1] = 0x34; i+=2;
			length = i;
			
			result = LORAWAN_Send(confirmed_or_not, 1, data + max_length - 1, length - max_length + 1);
		}
		//StartTimer( lora_send_timer_id, LORA_SEND_INTERVAL );
		//
	}

	//SwTimerStop( meter_receive_timeout_timer_id );

	receiving = 0;
	return result;
	//StartTimer( meter_request_timer_id,	METER_REQUEST_INTERVAL );
}


void lora_send_callback()
{
	uint8_t *data;
	uint8_t length, max_length;
	
	data = meterReadBuffer.data;
	length = meterReadBuffer.length;
	max_length = meterReadBuffer.max_length;	
	
	//LATC5 = 0;
	//LATD5 = 1;
	LORAWAN_Send(UNCNF, 1, data + max_length, length - max_length); //port 1	
}


void meter_receive_timeout_callback()
{	
	uint8_t a[2];
	
	//LATC5 = 0;
	//LATD5 = 1;
	
	a[0] = 0xFF;
	a[1] = eusart1RxCount;
	
	LORAWAN_Send(UNCNF, 1, &a, 2);
	receiving = 0;
	
	//StartTimer( meter_request_timer_id,	METER_REQUEST_INTERVAL );
}


unsigned char Get_SwitchValue(void)
{
    unsigned char value;
    
    value = (PORTA & 0x0F);
    
    return value;
}