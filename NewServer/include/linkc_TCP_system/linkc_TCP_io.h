#ifndef LINKC_TCP_IO_H
#define LINKC_TCP_IO_H

#include <stdint.h>

int16_t TCP_Send(int sockfd, void *buf, int buf_size, int flag);
int16_t TCP_Recv(int sockfd, void *out, int out_size, int flag);
int16_t TCP_recv(int Sockfd, void *Out, int Out_Size, int Flag);

#endif
