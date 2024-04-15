#include <stdio.h>
#include <stdlib.h>
#include "readingData.h"

#define MAX_LINE_LENGTH 100
#define MAX_READINGS 100

// Lectura de datos de la barberia
BarbershopInfo *readBarbershopData(const char *filename) {
  char line[MAX_LINE_LENGTH];
  BarbershopInfo *readings=malloc(sizeof(BarbershopInfo));

  // Abrir el archivo
  FILE *file = fopen(filename, "r");
  
  // Asegurar de que el archivo se abrio correctamente
  if (file == NULL) {
    printf("Error al abrir el archivo. barber\n");
    return NULL;
  }
  
  // Leer los datos del archivo
  if (fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%i %i %i", &readings->clientChairs, &readings->numBarbers, &readings->barberChairs);
  }
  
  // Cerrar el archivo
  fclose(file);

  return readings;
}


// Lectura de datos de los clientes
ClientInfo *readClientsData(const char *filename, int *numReadings) {
  char line[MAX_LINE_LENGTH];
  ClientInfo *readings = malloc(MAX_READINGS * sizeof(ClientInfo));
  *numReadings = 0;

  // Abrir el archivo
  FILE *file = fopen(filename, "r");

  // Asegurar de que el archivo se abrio correctamente
  if (file == NULL) {
    printf("Error al abrir el archivo clients.\n");
		printf("Filename: %s\n", filename);
    return NULL;
  }
  
  // Leer los datos del archivo
  while (*numReadings < MAX_READINGS && fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%i %i %i", &readings[*numReadings].arrivalTime, &readings[*numReadings].waitingTime, &readings[*numReadings].cuttingTime);
    (*numReadings)++;
  }

  // Cerrar el archivo
  fclose(file);

  return readings;
}
