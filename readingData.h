#ifndef READING_DATA_H
#define READING_DATA_H

// Estructura de datos de los clientes
typedef struct ClientInfo {
  int arrivalTime; // tiempo que tarda en llegar con respecto al anterior cliente
  int waitingTime; // tiempo que el cliente puede estar sentado en las sillas de espera
  int cuttingTime; // tiempo que demora el corte con el barbero
} ClientInfo;

// Estructura de datos de la barberia
typedef struct BarbershopInfo {
  int clientChairs;  // sillas de espera
  int numBarbers;    // numero de barberos
  int barberChairs;; // sillas de barbero
} BarbershopInfo;

// Lectura de datos de la barberia
BarbershopInfo *readBarbershopData(const char *filename, int *numReadings);

// Lectura de datos de los clientes
ClientInfo *readClientsData(const char *filename, int *numReadings);




#endif // READING_DATA_H