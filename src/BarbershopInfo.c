#include "BarbershopInfo.h"

#define MAX_LINE_LENGTH 100
#define MAX_READINGS 100

// Lectura de datos de la barberia
BarbershopInfo* ReadBarbershopData(const char* filename)
{
  char line[MAX_LINE_LENGTH];
  BarbershopInfo* data = malloc(sizeof(BarbershopInfo));

  // Abrir el archivo
  FILE* file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Error leer datos de la barberia: No se pudo abrir %s.\n", filename);
    return NULL;
  }
  
  // Leer los datos del archivo
  if (fgets(line, sizeof(line), file) != NULL)
  {
    sscanf(line, "%i %i %i", &data->clientChairs,
                             &data->numBarbers,
                             &data->barberChairs);
  }
  
  // Cerrar el archivo
  fclose(file);

  return data;
}

// Lectura de datos de los clientes
ClientInfo* ReadClientsData(const char* filename, int* size)
{
  char line[MAX_LINE_LENGTH];
  ClientInfo* data = malloc(MAX_READINGS * sizeof(ClientInfo));
  *size = 0;

  // Abrir el archivo
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    printf("Error leer datos de los clientes: No se pudo abrir %s.\n", filename);
    return NULL;
  }

  int fix = 0;
  
  // Leer los datos del archivo
  while (*size < MAX_READINGS && fgets(line, sizeof(line), file) != NULL)
  {
    if (fix < 2)
    {
      fix++;
      continue;
    }
    
    sscanf(line, "%i %i %i", &data[*size].arrivalTime, 
                             &data[*size].waitingTime, 
                             &data[*size].cuttingTime);
    
    data[*size].id = *size;
    (*size)++;
  }

  // Cierra el archivo
  fclose(file);

  return data;
}

ChairInfo* CreateChairsInfo(int numClientChairs, int numBarberChairs) {
  ChairInfo* chairs = (ChairInfo*)malloc(sizeof(ChairInfo));
  if (chairs == NULL) {
    return NULL;
  }

  chairs->clientChairs = (ClientChairs*)malloc(numClientChairs * sizeof(ClientChairs));
  if (chairs->clientChairs == NULL) {
    free(chairs);  
    return NULL;
  }

  chairs->barberChairs = (BarberChairs*)malloc(numBarberChairs * sizeof(BarberChairs));
  if (chairs->barberChairs == NULL) {
    free(chairs->clientChairs);
    free(chairs);
    return NULL;
  }

  // Inicializar clientChairs
  for (int i = 0; i < numClientChairs; i++) {
    chairs->clientChairs[i].chairId = i;
    chairs->clientChairs[i].isFree = true;
  }

  // Inicializar barberChairs
  for (int i = 0; i < numBarberChairs; i++) {
    chairs->barberChairs[i].chairId = i;
    chairs->barberChairs[i].isFree = true;
  }

  // Inicializar ChairInfo
  chairs->client = NULL;      

  return chairs;  // Devolver el puntero a ChairInfo
}

void PrintBarbershopInfo(BarbershopInfo* info)
{
  if (info == NULL)
    return;

printf("Datos de la barberia:\n\tSillas de espera:   %i\n\tNumero de barberos: %i\n\tSillas de barbero:  %i\n",
  info->clientChairs,
  info->numBarbers,
  info->barberChairs);
}

void PrintClientsInfo(ClientInfo* clients, int size)
{
  if (clients == NULL)
    return;

  printf("---Datos de los clientes---\n");
  printf("llegada | espera | corte\n");
  for (int i = 0; i < size; i++)
  {
    printf("%i, %i, %i\n", clients[i].arrivalTime, clients[i].waitingTime, clients[i].cuttingTime);    
  }
  printf("-----------------\n");
}

// WARNING: deberiamos de llamar size de otra manera mas descriptiva
void PrintChairsInfo(ChairInfo* info, BarbershopInfo* size) {
  if (info == NULL)
    return;
  int clientChairs = size->clientChairs;
  int barberChairs = size->barberChairs;
  
  printf("---Datos de las sillas espera---\n");
  for (int i = 0; i < clientChairs; i++) {
    printf("silla_espera[%i]\n", info->clientChairs[i].chairId); 
  }
  printf("---Datos de las sillas barbero---\n");
  for (int i = 0; i < barberChairs; i++) {
    printf("silla_barbero[%i]\n", info->barberChairs[i].chairId);
  }
  printf("-----------------\n");
}

void DestroyBarbershopInfo(BarbershopInfo* info)
{
  if (info == NULL)
    return;

  free(info);
}

void DestroyClientsInfo(ClientInfo* clients)
{
  if (clients == NULL)
    return;

  free(clients);
}

void DestroyChairsInfo(ChairInfo* chairs) {
  if (chairs == NULL)
    return;

  free(chairs->clientChairs);
  free(chairs->barberChairs);
  free(chairs->client);
}