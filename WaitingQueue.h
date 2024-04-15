#ifndef WAITING_QUEUE_H
#define WAITING_QUEUE_H

#include <pthread.h>
#include <stdlib.h>

struct WaitingQueue //chair implementation
{
  int max_queue;
  int count_queue;
  Client *queue;
  boolean* buzon;
};

typedef struct Client
{
  pthread_t *process;
  int id;
}Client;

typedef struct WaitingQueue WaitingQueue;

WaitingQueue *constructWaitingQueue(int max);

void addToWaitingQueue(WaitingQueue *WQueue, pthread_t InputWQueue);

void checkWaitingQueue(WaitingQueue *WQueue);

void shiftElements(WaitingQueue *WQueue,int shiftCount);

#endif // WAITING_QUEUE_H