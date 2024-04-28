#ifndef BARBERSHOP_INFO_H
#define BARBERSHOP_INFO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Estructura de datos de los clientes
struct ClientInfo
{
  int arrivalTime; // tiempo que tarda en llegar con respecto al anterior cliente
  int waitingTime; // tiempo que el cliente puede estar sentado en las sillas de espera
  int cuttingTime; // tiempo que demora el corte con el barbero
  int id;
};

typedef struct ClientInfo ClientInfo;

// Estructura de datos de la barberia
struct BarbershopInfo
{
  int clientChairs; // num sillas de espera
  int numBarbers;   // num numero de barberos
  int barberChairs; // num sillas de barbero
};

typedef struct BarbershopInfo BarbershopInfo;

// Estructura de las sillas de barbero
struct BarberChairs {
  int chairId; // id de la silla de barbero
  bool isFree;  // 1: libre | 0: ocupada 
};

typedef struct BarberChairs BarberChairs;

// Estructura de las sillas de espera
struct ClientChairs {
  int chairId; // id de la silla de espera
  bool isFree;  // silla libre? 
};

typedef struct ClientChairs ClientChairs;

// Estructura de las sillas de la barberia
struct ChairInfo {
  BarberChairs* barberChairs; // Estructura silla barbero
  ClientChairs* clientChairs; // Estructura silla cliente
  ClientInfo* client; // cliente que esta sentado en la silla
};

typedef struct ChairInfo ChairInfo;


BarbershopInfo* ReadBarbershopData(const char* filename);
void PrintBarbershopInfo(BarbershopInfo* info);
void DestroyBarbershopInfo(BarbershopInfo* info);

ClientInfo* ReadClientsData(const char* filename, int* size);
void PrintClientsInfo(ClientInfo* clients, int size);
void DestroyClientsInfo(ClientInfo* clients);

ChairInfo* CreateChairsInfo(int clientChairs, int barberChairs);
void PrintChairsInfo(ChairInfo* info, BarbershopInfo* size);
void DestroyChairsInfo(ChairInfo* chairs);

#endif // BARBERSHOP_INFO_H