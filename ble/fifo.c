#include "ble/fifo.h"

uint8_t FIFO_IsEmpty(FIFO_type *fifo)
{
  if(fifo->HeadIndex==fifo->TailIndex)
    return 1;
  else
    return 0;
}

void FIFO_Put(FIFO_type *fifo, uint8_t data)
{
  fifo->HeadIndex=(fifo->HeadIndex+1)%BUF_SIZE;
  fifo->Buf[fifo->HeadIndex]=data;
}

uint8_t FIFO_Pop(FIFO_type *fifo)
{
  fifo->TailIndex=(fifo->TailIndex+1)%BUF_SIZE;
  return fifo->Buf[fifo->TailIndex];
}

