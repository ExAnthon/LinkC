// 此文件废掉，现在留作参考，到时候删掉
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "readline.c"
#include "../../server/include/def.h"
#include "../../server/include/linkc_utilities.h"       // For ReadLine()

typedef t_r char  re[100];
#define prompt_lenth 300
extern int re_cfg( char * addr , int N, t_re *re_opt ) // N is the number of the line
{
FILE * fp;
t_r
char prompt[ prompt_lenth ], * input;
fp = fopen(addr , "r");

if(fp == NULL)return LINKC_FAILURE;

// if the file isn't existed, return the failure signal.
int i=0;
while(1)
    {
  //  snprintf(prompt,sizeof(prompt),"%s%s");
  //  puzzle!
    if(!input)
          break;

    cfg_opt = (char *) ReadLine( fp );
    }
 while(cfg_opt[i])i++;
 fclose(fp);
return i+1;
}
