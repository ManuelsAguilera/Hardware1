#include <pthread.h>
#include <stdlib.h>

typedef struct SillasEspera {
  int max_sillas;
  pthread_t *sillas;

} SillasEspera;

SillasEspera* makeSillaEspera(int InputMax_sillas) {
  SillasEspera *newSilla;
  newSilla->max_sillas = InputMax_sillas;
  // alocate sillas memory
  newSilla->sillas = malloc(sizeof(pthread_t) * newSilla.max_sillas);
  return newSilla;
}

void addSilla(SillasEspera *silla, pthread_t InputSilla)
{
	
}