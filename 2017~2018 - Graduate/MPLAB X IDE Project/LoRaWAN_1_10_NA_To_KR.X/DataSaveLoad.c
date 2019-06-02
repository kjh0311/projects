/*
 * File:   DataGetSet.c
 * Author: 김진희
 *
 * Created on 2017년 10월 16일 (월), 오후 8:59
 */
#include "mac_get_set.h"
#include "mcc_generated_files/memory.h"
#include "DataSaveLoad.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "UART_Print_Functions.h"


void LoadData(char* buffer, uint32_t addr, uint8_t len) {
    for(int8_t i = 0; i < len; i++) {
       buffer[i] = DATAEE_ReadByte(addr+i);
    }
}

void SaveData(char* buffer, uint32_t addr, uint8_t len) {
    for(int8_t i = 0; i < len; i++) {
        DATAEE_WriteByte(addr+i, buffer[i]);
    }
}


/*
void LoadOneDataByLibrarySetterFunctions(uint32_t addr, NameLenGetterSetter* pNameLenGetterSetter);

void LoadAllDataByLibrarySetterFunctions() {
    uint32_t addr = 0;
    
    for (int8_t i=0; i<NUM_PROP_CLASS; i++) {
        
        NameLenGetterSetter* name_len_getter_setter_array = props_array[i].name_len_getter_setter_array;
        uint8_t array_len = props_array[i].array_len;        
        //continue;
        for (int8_t j=0; j<array_len; j++) {
			
            if ( name_len_getter_setter_array[i].saving_or_not == SAVING ) {
                LoadOneDataByLibrarySetterFunctions(addr, name_len_getter_setter_array+i);
            }
			
            addr += name_len_getter_setter_array[i].len;
            //break;
			
        }
    }
}

// 포인터 쓰기 딱 좋은 완벽한 사례
void LoadOneDataByLibrarySetterFunctions(uint32_t addr, NameLenGetterSetter* pNameLenGetterSetter) {
    uint8_t len = pNameLenGetterSetter->len;
    void* setter = pNameLenGetterSetter->setter;
    Buffer buffer;
    
    LoadData(buffer.all, addr, len);
    
    //char buf[30];
    //sprintf(buf, "name: %s\r\n", pNameLenGetterSetter->name);
    //UART_Put_String(buf);
    
    ExcuteSetterFunction(setter, &buffer, len);
}
*/