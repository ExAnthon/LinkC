#ifndef MESSAGERECVER_H
#define MESSAGERECVER_H

#include <qt4/QtCore/QThread>
#include <qt4/QtCore/QVariant>
#include "linkc_types.h"
#include "Csocket.h"
#include "linkc_network_protocol.h"

//-------TCP-------//
class TCP_MessageRecver : public QThread
{
    Q_OBJECT
public:
    explicit TCP_MessageRecver(TCP_csocket *sk, QThread *parent = 0);
    ~TCP_MessageRecver();
    void run();

signals:
    void MessageRecved  (const void *data);
    void UserMessage    (LinkC_User_Message);
    void SysActionStatus(LinkC_Sys_Status);
    void SysFriendData  (LinkC_Friend_Data);
    void RecvError      ();

protected:
    TCP_csocket Dest;
    void *buffer;
    void *package;
};

//-------UDP-------//
class UDP_MessageRecver : public QThread{
    Q_OBJECT
public:
    explicit UDP_MessageRecver(UDP_csocket *sk, QThread *parent);
    void run();

signals:
    void UserChatMessage(QString);
    void RecvError();

protected:
    UDP_csocket Dest;
    void *buffer;
    void *package;
};

#endif // MESSAGERECVER_H