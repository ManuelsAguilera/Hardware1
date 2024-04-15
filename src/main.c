#include <stdio.h>
#include "readingData.h"
#include <stdlib.h>

int main(int argc, char *args[]) {
  // Barberia
  BarbershopInfo *barberia = readBarbershopData("data/file0.txt");
  if (barberia == NULL) {
    printf("Error al leer los datos de la barberia.\n");
    return 1;
  }

  printf("Datos de la barberia:\n");
  printf("sillas_clientes: %i num_barberos: %i sillas_barberos: %i\n\n", barberia->clientChairs, barberia->numBarbers, barberia->barberChairs);

  
  // Clientes
  int size;
  ClientInfo *clientes = readClientsData("data/file0.txt", &size);
  if (clientes == NULL) {
    printf("Error al leer los datos de los clientes.\n");
    return 1;
  }

  printf("\n\nDatos de los clientes:\n");
  for (int i = 0; i < size; i++) {
    printf("Cliente %d: Tiempo de llegada: %d, Tiempo de corte: %d, Tiempo de espera: %d\n",
           i + 1, clientes[i].arrivalTime, clientes[i].cuttingTime, clientes[i].waitingTime);
  }

  free(clientes);
  free(barberia);
  return 0;
}
