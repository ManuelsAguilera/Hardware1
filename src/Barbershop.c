#include "Barbershop.h"

#include <stdio.h>
#include <stdlib.h>

Barbershop CreateBarbershopFromFile(const char* filename)
{
  // Datos barberia
  BarbershopInfo* shopInfo = ReadBarbershopData(filename);
  if (shopInfo == NULL)
  {
    printf("Error al leer los datos de la barberia.\n");
  }

  // Datos clientes
  int size;
  ClientInfo* clientsInfo = ReadClientsData(filename, &size);
  if (clientsInfo == NULL)
  {
    printf("Error al leer los datos de lo clientes.\n");
  }

  // Datos sillas
  ChairInfo* chairsInfo = CreateChairsInfo(shopInfo->clientChairs, shopInfo->barberChairs);
  if (chairsInfo == NULL) 
  {
    printf("Error al crear las sillas.\n");
  }
  
  Barbershop result =
  {
    .shopInfo   = shopInfo,
    .clients    = clientsInfo,
    .numClients = size,
    .chairsInfo = chairsInfo,
    .filepath   = filename
  };

  return result;
}

void PrintBarbershop(Barbershop barberShop)
{
  printf("=========%s=========\n", barberShop.filepath);
  PrintBarbershopInfo(barberShop.shopInfo);
  PrintClientsInfo(barberShop.clients, barberShop.numClients);
  PrintChairsInfo(barberShop.chairsInfo, barberShop.shopInfo);
  printf("================================\n");
}

bool IsBarbershopValid(Barbershop barberShop)
{
  if (barberShop.shopInfo == NULL || barberShop.clients == NULL)
    return false;

  return true;
}

void DestroyBarbershop(Barbershop barberShop)
{
  DestroyBarbershopInfo(barberShop.shopInfo);
  DestroyClientsInfo(barberShop.clients);
  DestroyChairsInfo(barberShop.chairsInfo); 
}