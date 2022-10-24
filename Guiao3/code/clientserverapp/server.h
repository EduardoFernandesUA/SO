#include  <stdio.h>
#include  <stdlib.h>
#include  <libgen.h>
#include  <unistd.h>
#include  <sys/wait.h>
#include  <sys/types.h>
#include  <math.h>
#include <stdint.h>

uint32_t getPendingRequest(); /* take a buffer out of fifo of pending requests */
int getRequestData(uint32_t id); /* take the request */ // probably not returning a int TODO
int produceResponseData(int req); /* produce a response */ // not using ints
void putResponseData(int resp, uint32_t id); /* put response data on buffer */
void signalResponseIsAvailable(uint32_t id); /* so client is waked up */
