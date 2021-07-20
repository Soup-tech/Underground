#include <stdio.h>

int main(int argc, char ** argv) {
	char * p;

	printf("** argv : %c\n", **argv);
	printf("* argv : %s\n", *argv);	
	argc = atoi(* (++argv));
	printf("argc : %d\n", argc);
	return 0;

}
