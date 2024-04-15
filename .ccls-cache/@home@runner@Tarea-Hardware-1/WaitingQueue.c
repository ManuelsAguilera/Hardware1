#include "WaitingQueue.h"

WaitingQueue *constructWaitingQueue(int max) {
  WaitingQueue *result;
  result->max_queue = max;
  result->queue = malloc(max * sizeof(pthread_t));
  result->count_queue = 0;
  return result;
}

void addToWaitingQueue(WaitingQueue *WQueue, pthread_t InputWQueue) {
  if (WQueue->count_queue >= WQueue->max_queue)
    return;

  checkWaitingQueue(WQueue);
  // adds to the end.
  WQueue->queue[WQueue->count_queue] = InputWQueue;
  WQueue->count_queue++;
}

void shiftElements(WaitingQueue *WQueue,int shiftCount) { // Shifts elements in the queue to the left.
  for (int i = 0; i < shiftCount; i++)
    for (int j = WQueue->max_queue; j >1 ; j--)
      WQueue->queue[j] = WQueue->queue[j - 1];
}

void checkWaitingQueue(WaitingQueue *WQueue) {
  int nullsFound = 0;
  for (int i = 0; i < WQueue->count_queue; i++) {
    if (WQueue->queue[i])
      nullsFound++;
  	}
	shiftElements(WQueue, nullsFound);
}

void removeInWaitingQueue(WaitingQueue *WQueue,int index)
{
	pthread_join(WQueue->queue[0], NULL); 
	pthread_exit(NULL);
	WQueue->count_queue--;
	shiftElements(WQueue,1);
}
// Thread funtions:
