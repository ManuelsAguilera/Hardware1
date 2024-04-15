#include <pthread.h>
#include <stdlib.h>

typedef struct Barberia {
  int max_sillas;
	int barberos;	
	pthread_t* sillas;
	

} Barberia;