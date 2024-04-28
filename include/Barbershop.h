#ifndef BARBERSHOP_H
#define BARBERSHOP_H

#include "BarbershopInfo.h"
#include <stdbool.h>

struct Barbershop
{
  BarbershopInfo* shopInfo;
  ClientInfo* clients;
  ChairInfo* chairsInfo;
  const int numClients; 
  const char* filepath;
};

typedef struct Barbershop Barbershop;

Barbershop CreateBarbershopFromFile(const char* filename);
void PrintBarbershop(Barbershop barberShop);
bool IsBarbershopValid(Barbershop barberShop);
void DestroyBarbershop(Barbershop barberShop);

#endif // BARBERSHOP_H