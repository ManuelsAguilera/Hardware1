#include <stdio.h>
#include <stdlib.h>
#include "readingData.h"

#define MAX_LINE_LENGTH 100
#define MAX_READINGS 100

Reading *readData(const char *filename, int *numReadings) {
  FILE *file;
  char line[MAX_LINE_LENGTH];
  Reading *reaings = malloc(MAX_READINGS * sizeof(Reading));
 *numReadings = 0;

  // Abrir el archivo
  file = fopen(filename, "r");

  // Asegurar de que el archivo se abrio correctamente
  if (file == NULL) {
    printf("Error al abrir el archivo.\n");
    return NULL;
  }

  // Leer los datos del archivo
  while (fgets(line, sizeof(line), file) != NULL) {
    sscanf(line, "%d %d %d",reading)
  }
}
