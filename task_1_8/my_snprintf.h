#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

const int BUFFER_IS_NULL = -1;
const int FORMAT_IS_NULL = 0;
//const int INVALID_PLACEHOLDER = -2;
const int BUFFER_TOO_SMALL = -3;
const int EMPTY_PLACEHOLDER = -4;
const int PLACEHOLDER_BUFFER_TOO_SMALL = -5;
const int INVALID_PLACEHOLDER_CURRENCY_SPEC = -6;
const int INVALID_PLACEHOLDER_SIZE_SPEC = -7;

const int PLACEHOLDER_MAX_SIZE = 32;

int my_snprintf(char* buffer, int size, const char* format, int argc, ...);
int placeholder_handler(char* buff, int size, const char* format);
