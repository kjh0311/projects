/*
 * File:   Interpret_UART_Command.c
 * Author: 김진희
 *
 * Created on November 6, 2017, 2:27 PM
 */
#include "Interpret_UART_Command.h"


void UART_Put_String(const char *string);
void UART_Print_Result (LorawanError_t result);


typedef enum { NOT_EXCUTED, EXCUTED } ExcutedOrNot;


ExcutedOrNot excute_if_next_string_equals(char* next, StringAndFunction* array_of_string_and_functions);
void excute_and_print_result(Function function, char* param);




void Interpret_UART_Command(char* buffer)
{
	char* token = buffer;
	char* next = tokenize_string(token);
	StringAndCommandArrays *array_of_string_and_arrays = command_array_of_string_and_arrays;
	
	
	ExcutedOrNot excuted_or_not = NOT_EXCUTED;
	

	for (int8_t i=0; array_of_string_and_arrays[i].string != NULL; i++)	{
		char* string = array_of_string_and_arrays[i].string;
		// 문자열이 일치할 경우
		if ( str_equals( string, token) )
		{			
			
			
			CommandArrays *pArrays = array_of_string_and_arrays[i].pArrays;			
			StringAndFunction *array_of_string_and_functions = pArrays->string_and_functions;			
			if ( array_of_string_and_functions != NULL ) {			
				// 함수와 대응되는 명령이 있으면 찾아서 실행(예: token이 mac, next가 join, tx 등등)
				excuted_or_not = excute_if_next_string_equals(next, pArrays->string_and_functions);
				if (excuted_or_not == EXCUTED) {
					break;
				}
			}			
			array_of_string_and_arrays = pArrays->string_and_arrays;
			if ( array_of_string_and_arrays == NULL )
			{
				break;
			}
			else
			{
				token = next;
				next = tokenize_string(token);
				i = -1; // 재귀호출의 효과를 만들기 위해서 이런 트릭을 사용함.
			}
		}
	}
	
	// 실행이 안 된 경우 에러메시지 출력
	if ( excuted_or_not == NOT_EXCUTED ) {
		UART_Print_Result(ERROR);
	}
}



ExcutedOrNot excute_if_next_string_equals(char* next, StringAndFunction* array_of_string_and_functions)
{
	ExcutedOrNot excuted_or_not = NOT_EXCUTED;	
	char* command = next;
	char* param = tokenize_string(command);
	
	
	for (int8_t i=0; array_of_string_and_functions[i].string != NULL; i++)
	{
		if (str_equals(command, array_of_string_and_functions[i].string))
		{
			excute_and_print_result(array_of_string_and_functions[i].function, param);
			excuted_or_not = EXCUTED;
			break;
		}
	}
	
	if ( excuted_or_not == NOT_EXCUTED  ) {
		param[-1] = ' ';
	}
	
	
	return excuted_or_not;
}


void excute_and_print_result(Function function, char* param)
{
	LorawanError_t result = ERROR;
	
	if (function != NULL )
	{
		result = function(param);				
	}
	
	if (result != GETTER && result != PRINTED)
	{
		UART_Print_Result(result);
	}
}

/*
typedef struct {
	char* class, *command, *param;
} TokenizedString;

LorawanError_t interpret_command_with_one_class_array
	(StringAndFunction *array_of_string_and_function, TokenizedString *pInput);



void Interpret_UART_Command(char* buffer)
{
	TokenizedString input_strings;	
	LorawanError_t result;
	
	input_strings.class = buffer;
    input_strings.command = tokenize_string(input_strings.class);
	input_strings.param = tokenize_string(input_strings.command);
	
	
	// 아래 for문 안에서 if 문에 한 번도 안 걸리면 result는 ERROR
	result = ERROR;
	
	for (int8_t i=0; array_of_class_string_and_command_array[i].class_string != NULL; i++) {
		if ( str_equals (input_strings.class, array_of_class_string_and_array[i].class_string) ) {
			result = interpret_command_with_one_class_array
						(array_of_class_string_and_command_array[i]
						.array_of_command_string_and_function, &input_strings);
			break;
		}		
	}	
	
	// 입력한 명령이 get이고, 에러가 없다면 여기서 끝
	if (str_equals(input_strings.command, "get") && result != ERROR  ) {
		return;
	}	
	else { // 그렇지 않다면 결과에 따라서 출력함.
		UART_Print_Result(result); // result가 ERROR가 아니면 input.command가 "get"이 아닐 경우에만 출력
	}
}



// Interpret_UART_Command 함수에서 class 문자열이 일치할 때 진입하는 함수.
LorawanError_t interpret_command_with_one_class_array
	(StringAndFunction *array_of_command_string_and_function, TokenizedString *pInputStrings)
{	
	// for 문안에서 if 문에 한 번도 안 걸리면 result는 ERROR
	LorawanError_t result = ERROR;
	
	for (int8_t i=0; array_of_command_string_and_function[i].command_string != NULL; i++)
	{		
		// 입력받은 명령이 배열에 있는 명령과 일치하면 배열에 있는 함수를 실행함.
		if ( str_equals ( pInputStrings->command, array_of_command_string_and_function[i].command_string ) )
		{
			result = array_of_command_string_and_function[i].function( pInputStrings->param );
			break;
		}		
	}
	return result;
}
*/
