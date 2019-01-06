#define __MAIN_C__
#include "main.h"

#define USAGE "USAGE: cc3100-info read|active|passive\n"

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Wrong amount of arguments\n");
		fprintf(stderr, USAGE);
		return -1;
	}

	if (strcmp("read", argv[1]) == 0) {
		return cc3100_read();
	}

	if (strcmp("active", argv[1]) == 0) {
		return cc3100_initForActiveScan();
	}

	if (strcmp("passive", argv[1]) == 0) {
		return cc3100_initForPassiveScan();
	}

	fprintf(stderr, "Wrong argument\n");
	fprintf(stderr, USAGE);
	return -1;
}
