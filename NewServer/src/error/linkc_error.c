#include "../../include/linkc_error.h"
#include <stdio.h>
#include <stdint.h>

void LinkC_Debug(const char *Target,int Status){
#if _DEBUG_MOD_
	if(Status == LINKC_SUCCESS)
#ifdef linux
	   printf("[\033[32mSUCCESS\033[0m]\t%s\n",Target);
#else
	printf("[SUCCESS]\t%s\n",Target);
#endif
	else if(Status == LINKC_EXITED)
#ifdef linux
	   printf("[\033[33mEXITED \033[0m]\t%s\n",Target);
#else
	printf("[EXITED ]\t%s\n",Target);
#endif
	else if(Status == LINKC_WARNING)
#ifdef linux
	   printf("[\033[34mWARNING\033[0m]\t%s\n",Target);
#else
	printf("[WARNING]\t%s\n",Target);
#endif
	else if(Status == LINKC_DONE)
#ifdef linux
	   printf("[\033[32mDONE \033[0m]\t%s\n",Target);
#else
	printf("[DONE ]\t%s\n",Target);
#endif
	else if(Status == LINKC_STARTED)
#ifdef linux
	   printf("[\033[32mSTARTED\033[0m]\t%s\n",Target);
#else
	printf("[STARTED]\t%s\n",Target);
#endif
	else if(Status == LINKC_DEBUG)
#ifdef linux
	    printf("[\033[34mDEBUG\033[0m]\t%s\n",Target);
#else
	printf("[DEBUG ]\t%s\n",Target);
#endif
#endif

	if(Status == LINKC_FAILURE)
#ifdef linux
	   printf("[\033[31mFAILURE\033[0m]\t%s\n",Target);
#else
	printf("[FAILURE]\t%s\n",Target);
#endif
}


void MemoryPrint(void *Memory,size_t size){
    uint8_t *p = (uint8_t*)Memory;
    size_t i;
    printf("---------Memory Print---------\n");
    for(i=0;i<size;i++){
        printf("Addr = [0x%X]\t\t[0x%X]\n",p,*p);
        p++;
    }
    printf("--------------End-------------\n");
    return;
}
