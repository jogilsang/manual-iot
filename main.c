#include "bt.h"
#include "main.h"
#include <math.h>

int main(void){
	jrpc_init();
	while(1){
		sleep(60); 
	}
	jrpc_exit();
	return 0;
}

