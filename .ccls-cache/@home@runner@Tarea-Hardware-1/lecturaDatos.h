#ifndef LECTURA_DATOS_H
#define LECTURA_DATOS_H

typedef struct Reading {
  int clientChairs;
  int numBarbers;
  int berberChairs;;
} Reading;

Reading *readData(const char *filename, int *numReadings);


#endif // LECTURA_DATOS_H