/*
 * File:   tokenize_string.c
 * Author: 김진희
 *
 * Created on 2017년 11월 9일 (목), 오후 1:49
 */


#include <string.h>

char* tokenize_string(char* string) {
    string = strchr(string, ' ');
    *string = '\0';
    return string + 1;
}