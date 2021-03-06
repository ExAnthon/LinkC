#include "../../include/linkc_client.h"
#include "../../include/linkc_TCP_system/linkc_TCP_io.h"
#include "../../include/linkc_curses_error.h"
#include "../../include/linkc_def.h"
#include "../../include/linkc_package.h"
#include "../../include/linkc_package_ctl.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <arpa/inet.h>
#include <string.h>
#include <curses.h>

int wLogin(WINDOW* Console,int Sockfd,LoginData Data){
    void *Buffer    = malloc(STD_PACKAGE_SIZE);
    void *Package   = malloc(STD_PACKAGE_SIZE);
    ((MessageHeader*)Buffer)->ActionType = USER_LOGIN;
    memcpy((void*)((char*)Buffer+4),(void*)&Data,sizeof(LoginData));
    int Length = _Package(Buffer,sizeof(MessageHeader)+sizeof(LoginData),NORMAL_MESSAGE,Package);
    send(Sockfd,Package,Length,0);
    wTCP_Recv(Console,Sockfd,Buffer,STD_PACKAGE_SIZE,0);
    if(_UnPackage(Buffer,STD_PACKAGE_SIZE,Package) == LINKC_FAILURE)
        return LINKC_FAILURE;
    if(ntohs(((MessageHeader*)Package)->StatusCode) == LOGIN_FAILURE)
        return LINKC_FAILURE;
    wLinkC_Debug(Console,"Check User Password",LINKC_SUCCESS);

    wTCP_Recv(Console,Sockfd,Buffer,STD_PACKAGE_SIZE,0);
    if(_UnPackage(Buffer,STD_PACKAGE_SIZE,Package) == LINKC_FAILURE)
        return LINKC_FAILURE;
    if(ntohs(((MessageHeader*)Package)->StatusCode) == SET_STATUS_FAILURE)
        return LINKC_FAILURE;
    wLinkC_Debug(Console,"Set Status",LINKC_SUCCESS);

    free(Buffer);
    free(Package);
    Buffer = NULL;
    Package= NULL;
    return LINKC_SUCCESS;
}

int wGetSelfData(WINDOW* Console,int Sockfd,UserData* Data){
    void *Buffer = malloc(STD_PACKAGE_SIZE);
    void *Package= malloc(STD_PACKAGE_SIZE);
    bzero(Buffer, STD_PACKAGE_SIZE);
    bzero(Package,STD_PACKAGE_SIZE);
    ((MessageHeader*)Buffer)->ActionType = (RQUEST_DATA|SELF_DATA);
    int Length = _Package(Buffer,sizeof(MessageHeader),NORMAL_MESSAGE,Package);
    send(Sockfd,Package,Length,0);
    wLinkC_Debug(Console,"Requesting to Send Personal Data",LINKC_DONE);
    wLinkC_Debug(Console,"Waiting for Server Respond",LINKC_STARTED);
    if(wTCP_Recv(Console,Sockfd,Buffer,STD_PACKAGE_SIZE,0) == LINKC_FAILURE){
        wLinkC_Debug(Console,"Accepted Data",LINKC_FAILURE);
        free(Buffer);
        free(Package);
        Buffer = NULL;
        Package= NULL;
        return LINKC_FAILURE;
    }
    _UnPackage(Buffer,STD_PACKAGE_SIZE,Package);
    if(((MessageHeader*)Package)->ActionType != (RETURN_DATA|SELF_DATA)){
        wLinkC_Debug(Console,"Server Returned Data Exception",LINKC_WARNING);
        free(Buffer);
        free(Package);
        Buffer = NULL;
        Package= NULL;
        return LINKC_FAILURE;
    }
    if(((MessageHeader*)Package)->StatusCode == htons(GET_DATA_FAILURE)){
        wLinkC_Debug(Console,"Server Fetched Data",LINKC_FAILURE);
        free(Buffer);
        free(Package);
        Buffer = NULL;
        Package= NULL;
        return LINKC_FAILURE;
    }
    wLinkC_Debug(Console,"Accepted Personal Data",LINKC_DONE);
    memcpy(Data,((char*)Package)+sizeof(MessageHeader),sizeof(UserData));
    free(Buffer);
    free(Package);
    Buffer = NULL;
    Package= NULL;
    return LINKC_SUCCESS;
}
