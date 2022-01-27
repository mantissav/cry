#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//hash datastructure for optimization
#include "uthash.h"

#define MODE_64 8
#define MODE_32 4
#define MACHINE_LITTLE_EDIAN 1
#define MACHINE_BIG_EDIAN 2
extern unsigned int MODE;
extern unsigned int MACHINE;


extern void lexer(char* buffer);
extern void lexer_init();