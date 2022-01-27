#include "mainheader.h"
#include "lex.h"

int wordlen(char* str) {
	int i;
	for (i = 0; str[i] != 32 && str[i] != 0 && str[i] != 10; ++i)
	{
	}
	return i;
}
char* wordstr(char* str, int wrdlen) {
	char* tmp_buf = calloc(wrdlen + 1, sizeof(char));
	for (int i = 0; i < wrdlen; ++i)
		tmp_buf[i] = str[i];
	return tmp_buf;
}
symbol keyword_check(char* str) {
	if ((str[0] < '0' || str[0] > '9') && (str[1] < '0' || str[1] > '9')) {
		int wrdlen = wordlen(str);
		keyword* returned_keyword = NULL;
		HASH_FIND_STR(keyword_patterns, wordstr(str, wrdlen), returned_keyword);
		printf(" ||%p||\n", returned_keyword);
		if (returned_keyword)
			return (symbol) { returned_keyword->tok, returned_keyword->specifier };
		else {
			if (str[0] != 32 && str[0] != 10 && str[0] != 0)
				return (symbol) { IDENTIFIER, (int)str };
			else
				return (symbol) { NONE, NONE };
		}
	} //TODO: DIFFERIENCATE BETWEEN DIFFERENT TYPES OF CONSTANTS HERE
	else return (symbol) { INTEGER_CONSTANT, (int)str };
}
//returns the amount you need to incremant to make it to the first letter of the next word
int nextword(char* str, int cur) {
	return wordlen(&str[cur]) + 1;
}
void lexer_init(void) {
	for (int i = 0; i < SPECIFICATION_SIZE; ++i) {
		keyword* tmp_keyword = &specification[i];
		HASH_ADD_KEYPTR(hh, keyword_patterns, tmp_keyword->substr, strlen(tmp_keyword->substr), tmp_keyword);
	}
}
//takes in a buffer and returns a tokenized and compiler-friendly buffer
void lexer(char* buffer) {
	unsigned char* output = calloc(strlen(buffer), sizeof(char));
	printf("begins %p | ends %p \n", output, output + strlen(buffer));
	int out_idx = 0; //current location in output buffer
	//first pass
	for (int i = 0; i < strlen(buffer); i += nextword(buffer,i)) { 
		//printf("%d : %d\n", keyword_check(&buffer[i]).tok, i); for lex debug
		symbol sym = keyword_check(&buffer[i]);
		//do some checking on this symbol first
 		if (sym.tok != IDENTIFIER && sym.tok != INTEGER_CONSTANT && sym.tok != NONE) {
			output[out_idx] = sym.tok, output[out_idx + 1] = sym.specifier;
			out_idx += 2;
		}
		else if (sym.tok == IDENTIFIER) {
			output[out_idx] = sym.tok;
			for (int j = 0; j < wordlen((char*)sym.specifier); ++j)
				output[out_idx + 1 + j] = ((char*)sym.specifier)[j];
			output[out_idx + 1 + wordlen((char*)sym.specifier)] = IDENTIFIER_END;
			output = output + 2 + wordlen((char*)sym.specifier);
		}
		else if (sym.tok == INTEGER_CONSTANT) {
			output[out_idx] = sym.tok;
			char* constant = (char*)sym.specifier;
			output[out_idx + 1] = constant[0] == '-' ? SIGNED : UNSIGNED;
			output[out_idx + 2] = MACHINE;
			output[out_idx + 3] = MODE;
			if (output[out_idx + 1] == SIGNED) {
				int tmp = atoi(wordstr(constant, wordlen(constant)));
				int offset;
				for (offset = 0; offset < MODE; ++offset)
					output[out_idx + 4 + offset] = MACHINE == MACHINE_BIG_EDIAN ? ((unsigned char*)&tmp)[MODE - 1 - offset] : ((unsigned char*)&tmp)[offset];
				output[out_idx + 4 + offset] = INTEGER_CONSTANT_END;
			}
			else {
				unsigned int tmp = atoi(wordstr(constant, wordlen(constant)));
				int offset;
				for (offset = 0; offset < MODE; ++offset)
					output[out_idx + 4 + offset] = MACHINE == MACHINE_BIG_EDIAN ? ((unsigned char*)&tmp)[MODE - 1 - offset] : ((unsigned char*)&tmp)[offset];
				output[out_idx + 4 + offset] = INTEGER_CONSTANT_END;
			}

		}
	}
	puts("w"); //here for breakpoints I guess
}