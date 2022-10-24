#include  <stdio.h>
#include  <stdlib.h>
#include  <libgen.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <sys/types.h>
#include  <math.h>
#include <stdint.h>

uint32_t getFreeBuffer(); /* take a buffer out of fifo of free buffers */
void putRequestData(char *data, uint32_t id); /* put request data on buffer */ // data not a string TODO
void addNewPendingRequest(uint32_t id); /* add buffer to fifo of pending requests */
void waitForResponse(uint32_t id); /* wait (blocked) until a response is available */
int getResponseData(uint32_t id); /* take response out of buffer */ // does not return a int
void releaseBuffer(uint32_t id); /* buffer is free, so add it to fifo of free buffers */