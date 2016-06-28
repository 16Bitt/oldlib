#include "stdlib.h"
#include "stdio.h"
#include "oldlib.h"

int oldlib_error = OLDLIB_LOUD;

void oldlib_error_level(int level){
	oldlib_error = level;
}

void oldlib_warning_msg(const char* file, const char* function, int line, char* message){
	if(oldlib_error == OLDLIB_QUIET)
		return;

	fprintf(stderr, "Warning@%s:%d in %s(): %s\n", file, line, function, message);

	if(oldlib_error == OLDLIB_STRICT){
		OLDLIB_ERR("Warnings in STRICT mode are fatal. Aborting.");
	}
}

void oldlib_error_msg(const char* file, const char* function, int line, char* message){
	fprintf(stderr, "Error@%s:%d in %s(): %s\n", file, line, function, message);
	exit(1);
}
