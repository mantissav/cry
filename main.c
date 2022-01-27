#include "mainheader.h"

extern char* load_file(char* name);

char** files = NULL;

int MODE, MACHINE;

int main(int argc, char* argv[]) {
	MODE = MODE_32;
	MACHINE = MACHINE_LITTLE_EDIAN;
	lexer_init();
	lexer(load_file("main.txt"));
	/*files = calloc(argc - 1, sizeof(char*));
	for (int i = 1; i < argc; ++i) { //load all files specified by the user
		 files[i - 1] = load_file(argv[i]);
	}
	for (int i = 0; i < argc - 1; ++i)
		lexer(files[i]);*/
}

char* load_file(char* name) {
	FILE* fp = fopen(name, "r");
	if (fp) {
		fseek(fp, 0, SEEK_END); //get size
		unsigned int fsize = ftell(fp);
		fseek(fp, 0, SEEK_SET);

		//now read
		char* tmp_buf = calloc(fsize + 1, sizeof(char));
		fread(tmp_buf, sizeof(char), fsize, fp); 
		return tmp_buf;
	}
	else {
		printf("ERR: Could not open file %s", name);
		return NULL;
	}
}