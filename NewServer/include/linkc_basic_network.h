#ifndef LINKC_BASIC_NETWORK_H
#define LINKC_BASIC_NETWORK_H

#include "linkc_def.h"

int     InitNetwork(int port);

int     WaitForConnect(void);

void*    MainConnect(void *Arg);

#endif
