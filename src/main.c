#include "Barbershop.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

// Mutex / semaforos / conds
static pthread_mutex_t barberChairMutex;
static pthread_mutex_t clientChairMutex;

// Recursos compartidos
static int barberChairsOcupped = 0;
static int clientChairsOcupped = 0;
static int clientChairs = 0;
static int barberChairs = 0;

// Routins
void* clientsRoutine(void* args);
void* barbersRoutine(void* args);

ChairInfo* chairInfo;

int main(int argc, char *args[])
{
	
	
  Barbershop barberShop = CreateBarbershopFromFile("data/file2.txt");
  if (!IsBarbershopValid(barberShop))
    return 1;

  int i; // Iterador

  // Info barberia
  PrintBarbershop(barberShop);

  // Asignar valor a recursos compartidos
  ChairInfo* chairs = barberShop.chairsInfo;
  clientChairs = barberShop.shopInfo->clientChairs;
  barberChairs = barberShop.shopInfo->barberChairs;
  chairInfo = barberShop.chairsInfo;
  
  // Inicializar mutex / cond / sem
  pthread_mutex_init(&barberChairMutex, NULL);
  pthread_mutex_init(&clientChairMutex, NULL);

  // Crear thread barbero
  pthread_t barbersThread[barberShop.shopInfo->numBarbers];

  for (i = 0; i < barberShop.shopInfo->numBarbers; i++)
  {
    int* id = malloc(sizeof(int)); // Se libera en barbersRoutine()
    *id = i;

    if (pthread_create(&barbersThread[i], NULL, &barbersRoutine, id) != 0)
    {
      printf("Error al crear los threads barberos");
      return 1;
    }
  }
  
  // Crear thread cliente
  // ADVERTENCIA: para simular el tiempo de llegada de los clientes, se agrego un sleep(arrivalTime) antes de crear el thread
  // TODO: cambiar de sleep() a usleep()
  pthread_t clientsThread[barberShop.numClients];

  for (i = 0; i < barberShop.numClients; i++)
  {
    ClientInfo* client = malloc(sizeof(ClientInfo)); // Es liberado en clientsRoutine()
    *client = barberShop.clients[i];

    usleep(barberShop.clients[i].arrivalTime);
		if (clientChairsOcupped <= clientChairs)
    {
	    if (pthread_create(&clientsThread[i], NULL, &clientsRoutine, (void*)client) != 0)
	    {
	      printf("Error al crear los threads clientes");
	      return 1;
	    }
			printf("Cliente %d llega a la barberia\n", client->id);
		}
    else
    {
      printf("Cliente[%d] saliendo porque no hay sillas disponibles\n", i);
    }
  }

  for (i = 0; i < barberShop.shopInfo->numBarbers; i++)
  {
    if (pthread_join(barbersThread[i], NULL) != 0) {
      printf("Error al esperar a los threads barberos");
    }
  }

  // Esperar a que los threads terminen
  for (i = 0; i < barberShop.numClients; i++)
  {
    if (pthread_join(clientsThread[i], NULL) != 0) {
      printf("Error al esperar a los threads clientes");
    }
  }
  
  printf("Los clientes han sido atendido\n");

  // Destruccion de barberia / mutex / cond / sem
  DestroyBarbershop(barberShop);
  pthread_mutex_destroy(&clientChairMutex);
  pthread_mutex_destroy(&barberChairMutex);

	
  return 0;
}

int asignarSillaEspera(ClientInfo* client, ChairInfo* chairs)
{
  for (int i = 0; i < clientChairs; i++)
  {
    if (chairs->clientChairs[i].isFree)
    {
      chairs->clientChairs[i].isFree = false;
      clientChairsOcupped++;
      
      return i; // id silla
    }
  } 
  
  return -1;
}

int asignarSillaBarbero(ClientInfo* client, ChairInfo* chairs) {
  
  for (int i = 0; i < clientChairs; i++)
  {
    if (chairs->barberChairs[i].isFree)
    {
      chairs->barberChairs[i].isFree = false;
      barberChairsOcupped++;
      return i; // id silla
    }
  }

  return -1;
}

void liberarSillaEspera(int id_silla, ChairInfo* chairs) {
  chairs->clientChairs[id_silla].isFree = true;
  clientChairsOcupped--;
}


void* clientsRoutine(void* args) {
  ClientInfo* client = (ClientInfo*)args;

  pthread_mutex_lock(&clientChairMutex);
  int silla_espera = asignarSillaEspera(client, chairInfo);
  if (silla_espera == -1)
  {
    printf("Cliente[%d] saliendo porque no hay sillas disponibles\n", client->id);
    return 0;
  }
  
  printf("Cliente[%d] se senta en la silla de espera[%d]\n", client->id, silla_espera);
  pthread_mutex_unlock(&clientChairMutex);


  void liberarSillaBarbero(int id_silla, ChairInfo* chairs) {
    chairs->barberChairs[id_silla].isFree = true;
    clientChairsOcupped--;
  }


	for (client->waitingTime; client->waitingTime > 0; client->waitingTime--)
	{
		//Aqui preguntar si es que puede entrarse en la barberia
		if (barberChairsOcupped < barberChairs)
		{
      pthread_mutex_lock(&barberChairMutex);
      int silla_barbero = asignarSillaBarbero(client, chairInfo);
      printf("Cliente[%d] se senta en la silla de barbero[%d]\n", client->id,silla_barbero);
      pthread_mutex_unlock(&barberChairMutex);
      
      pthread_mutex_lock(&clientChairMutex);
      liberarSillaEspera(silla_espera, chairInfo);
      printf("Cliente[%d] libera la silla de espera[%d]\n", client->id,silla_barbero);
      pthread_mutex_unlock(&clientChairMutex);
			
      pthread_t barber; 
      pthread_create(&barber,NULL, &barbersRoutine,&client);
      
      return 0;
		}
  }
	//esperar siguiente ciclo
	usleep(1);
		
	
  printf("Cliente[%d] se va porque espero mucho tiempo\n", client->id);
	
	
  
  free(args);
  return NULL;
}

void* barbersRoutine(void* args)
{
  ClientInfo* client = (ClientInfo*)args;

	//mutex
	pthread_mutex_lock(&barberChairMutex);
	for (int i=0; i < client->cuttingTime; i++)
	{
		//Aqui preguntar si es que puede entrarse en la barberia
		usleep(1);
			
	}
	pthread_mutex_unlock(&barberChairMutex);
	
	printf("Cliente termina de cortarse el pelo y se va\n");
  
  return NULL;

}
