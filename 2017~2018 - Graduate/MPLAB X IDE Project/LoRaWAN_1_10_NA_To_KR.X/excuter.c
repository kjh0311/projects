/*
 * File:   excuter.c
 * Author: 김진희
 *
 * Created on 2017년 11월 9일 (목), 오후 5:03
 */

#include "mcc_generated_files/mcc.h"
#include "mac_get_set.h"
void UART_Print_Result (LorawanError_t result);


#define STRING	0



typedef void (*Getter4more)(uint8_t* buffer, char* param);
typedef uint32_t (*Getter4)();
typedef uint16_t (*Getter2)();
typedef uint8_t (*Getter1)();
typedef LorawanError_t (*Setter4more)(uint8_t* param1);
typedef LorawanError_t (*Setter4)(uint32_t param1);
typedef LorawanError_t (*Setter2)(uint16_t param1);
typedef LorawanError_t (*Setter1)(uint8_t param1);

LorawanError_t Setter4moreDummy(uint8_t*) {}
LorawanError_t Setter4Dummy(uint32_t) {}
LorawanError_t Setter2Dummy(uint16_t) {}
LorawanError_t Setter1Dummy(uint8_t) {}

void Getter4moreDummy(uint8_t* buffer, char* param) {}
uint32_t Getter4Dummy() {}
uint16_t Getter2Dummy() {}
uint8_t Getter1Dummy() {}

uint8_t EUSART1_Read();

/*
void excute_setter_function(void* setter, Buffer *pBuffer, uint8_t len){}
void excute_getter_function(void* getter, Buffer *pBuffer, uint8_t len, char* param){}
*/
//void ExcuteSetterFunction(void* setter, Buffer *pBuffer, uint8_t len);
//void ExcuteGetterFunction(void* getter, Buffer *pBuffer, uint8_t len, char* param);


void excute_setter_function(void* setter, Buffer *pBuffer, uint8_t len) {
    //char test[100];
    //uint8_t test_len = 0;
    // 이거 안 해놓으면 파라미터를 전혀 인식 못 함.
    Setter4more setter4more = Setter4moreDummy;
    Setter4 setter4 = Setter4Dummy;
    Setter2 setter2 = Setter2Dummy;
    Setter1 setter1 = Setter1Dummy;
	
	LorawanError_t result;
	
    
	// len이 4,2,1아니면 다 포인터로 처리(0이나 3이나 5나 8이나 다 포인터로 처리)
    switch (len) {
        case 4:
            //sprintf(test, "pBuffer->byte4: 0x%08X\r\n", pBuffer->byte4);
            setter4 = setter;
            result = setter4(pBuffer->byte4);
            break;
        case 2:
            setter2 = setter;
            result = setter2(pBuffer->byte2);
            break;
        case 1:
            //sprintf(test, "pBuffer->byte1: 0x%08X\r\n", pBuffer->byte1);
            setter1 = setter;
            result = setter1(pBuffer->byte1);
            break;
		case STRING:
			setter4more = setter;
            result = setter4more(pBuffer->pointer);
			break;
        default:
            setter4more = setter;
            result = setter4more(pBuffer->all);
            break;
    }
    UART_Print_Result(result);
}


void excute_getter_function(void* getter, Buffer *pBuffer, uint8_t len, char* param) {
    
    Getter4more getter4more = Getter4moreDummy;
    Getter4 getter4 = Getter4Dummy;
    Getter2 getter2 = Getter2Dummy;
    Getter1 getter1 = Getter1Dummy;
    
    switch (len) {
        case 4:
            getter4 = getter;
            pBuffer->byte4 = getter4();
            break;
        case 2:
            getter2 = getter;
            pBuffer->byte2 = getter2();
            break;
        case 1:
            getter1 = getter;
            pBuffer->byte1 = getter1();
            break;
        default:
            getter4more = getter;
            getter4more(pBuffer->all, param);
            break;
    }
}
 