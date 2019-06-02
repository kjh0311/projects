/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef STRING_AND_COMMAND_ARRAYS_H
#define	STRING_AND_COMMAND_ARRAYS_H

/* TODO
 * 다음 세 가지 구조를 만든다.
 * StringAndFunction, StringAndSubTrees, Tree
 * StringAndFunction: 명령어와 함수로 구성
 * StringAndSubTrees: 명령어와 서브트리의 배열로 구성
 * Tree: StringAndFunction 배열와 StringAndSubTrees 배열로 구성 
 */


#ifndef STRING_AND_FUNCTION_H
#define	STRING_AND_FUNCTION_H
//#include "CommandArray.h"


#include "tokenize_string.h"
#include "Function.h"

typedef struct {
	char* string;
	Function function;
} StringAndFunction;

#endif	/* STRING_AND_FUNCTION_H */


// 아래 두 구조체는 상호의존적임.
// 배열만을 담는 구조체
typedef struct {
	StringAndFunction* string_and_functions;
	struct StringAndCommandArrays* string_and_arrays;
} CommandArrays;


typedef struct {
	char* string;
	CommandArrays* pArrays;
}
StringAndCommandArrays;


typedef struct {
	char* string; // key
    // External Nodes (Leaves)
	StringAndFunction* string_and_functions;
    // Internal Nodes (Sub Trees)
	struct StringAndCommandArrays* string_and_arrays;
}
StringAndCommandArrays;




#endif	/* STRING_AND_COMMAND_ARRAYS_H */

