#define __MAIN_C__
#include "main.h"

int main(int argc, char **argv)
{
    _i16 retVal = sl_Start(0, 0, 0);
    if (retVal < 0) {
    	DEBUG("Can not start device");
    	return -1;
    }
    bool error = false;

    if (argc != 2) {
    	fprintf(stderr, "Wrong amount of arguments\n");
    	fprintf(stderr, "USAGE: cc3100-info read|write\n");
    	error = true;
    	goto end;
    }

    if (strcmp("read", argv[1]) == 0) {
    	int retVal = cc3100_read();
    	error = retVal < 0;
    } else if (strcmp("write", argv[1]) == 0) {
    	int retVal = cc3100_write();
    	error = retVal < 0;
    }

end:
    retVal = sl_Stop(SL_STOP_TIMEOUT);
    if (retVal < 0) {
    	DEBUG("Can not stop device correctly");
    	return -1;
    }
    return error ? -1 : 0;
}
