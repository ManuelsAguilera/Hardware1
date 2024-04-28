#include "Barbershop.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void* clientsRoutine(void* args);
void* barbersRoutine(void* args);

int main(int argc, char *args[])
{
  Barbershop barberShop = CreateBarbershopFromFile("data/file1.txt");
  if (!IsBarbershopValid(barberShop))
    return 1;

  int i; // Iterador
  PrintBarbershop(barberShop);

  // Crear thread cliente
  // WARNING: todos lo clients se crean al mismo tiempo
  pthread_t clientsThread[barberShop.numClients];

  for (i = 0; i < barberShop.numClients; i++)
  {
    ClientInfo* client = malloc(sizeof(ClientInfo)); // Es liberado en clientsRoutine()
    *client = barberShop.clients[i];
                                     
    if (pthread_create(&clientsThread[i], NULL, &clientsRoutine, (void*)client) != 0)
    {
      printf("Error al crear los threads clientes");
      return 2;
    }
  }

  // Crear thread barbero
  pthread_t barbersThread[barberShop.shopInfo->numBarbers];

  for (i = 0; i < barberShop.shopInfo->numBarbers; i++)
  {
    int* id = malloc(sizeof(int)); // Se libera en barbersRoutine()
    *id = i;
    
    if (pthread_create(&barbersThread[i], NULL, &barbersRoutine, id) != 0)
    {
      printf("Error al crear los threads barberos");
      return 3;
    }
  }

  // Esperar a que los threads terminen
  for (i = 0; i < barberShop.numClients; i++)
  {
    if (pthread_join(clientsThread[i], NULL) != 0) {
      printf("Error al esperar a los threads clientes");
    }
  }
  
  for (i = 0; i < barberShop.shopInfo->numBarbers; i++)
  {
    if (pthread_join(barbersThread[i], NULL) != 0) {
      printf("Error al esperar a los threads barberos");
    }
  }

  printf("Los clientes han sido atendido\n");

  DestroyBarbershop(barberShop);
  return 0;
}

void* clientsRoutine(void* args) {
  ClientInfo* client = (ClientInfo*)args;
  // printf("Cliente %i PRESENTE\n", client->id);
  // mientras (tiempo)
  //   Cliente i entra a la barberia
  //   
  //   Hay sillas de espera?
  //     si: clientesEsperando++
  //          - Cliente i se sienta en silla de espera j
  //          - Empieza a bajar el tiempo de espera del cliente
  //     no:
  //          - Cliente i se va a casa, no habian sillas de espera

  //   Hay sillas de barbero?
  //      si: -> clientesEsperando--
  //          - Cliente i se sienta en silla barbero j
  //          
  //          Hay barbero desocupado?
  //             si:
  //                 - Espera a barbero (cond signal)
  //                 - Empieza corte de pelo
  //             no:
  //                 - Espera a que un barbero se desocupe
  //
  //      no:
  //          - Cliente i esepero mucho, se va a casa
  free(args);
}

void* barbersRoutine(void* args) {
  int* id = (int*)args;
  // printf("Barbero %i PRESENTE\n", *id);
  // mientras (tiempo)
  //   mientras (sillasBarbero tienen cliente)
  //       - cond wait (mutexBarberia)
  //       - Barbero k atiende a cliente i
  //       - Simular tienpo de corte 
  //       - Barbero k se va a silla de espera j

  free(args);
}

