#include <stdio.h>

#include "readingData.h"

int main() {
  int size;
  ClientInfo *cli = readClientsData("../data/file0.txt", &size);

  for (int i = 0; i < size; i++) {
    printf("Client%i: %i %i %i\n", i, cli->arrivalTime, cli->cuttingTime,
           cli->waitingTime);
  }
}