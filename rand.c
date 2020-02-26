#include "rand.h"

static unsigned int next = 1;

void srand(unsigned int seed){
	next = seed;
}

int rand(void){
	next = next * 1103515245 + 12345;
        return((unsigned)(next/65536) % 32768);
}
