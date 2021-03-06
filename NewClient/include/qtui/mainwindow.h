#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMap>
#include <stdint.h>
#include "loginwindow.h"
#include "linkc_client.h"
#include "linkc_socket.h"
#include "linkc_def.h"
#include "friendslist.h"
#include "chatdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit    MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void        LoginStatus(bool);


public slots:
    void        ExitProgram(void);
    void        DoLogin(LoginData);
    void        OpenChatDialog(UserData);
    int         DoGetSelfData(void);
    int         DoGetFriendsData(void);

private:
    Ui::MainWindow *ui;
    FriendsList *FList;
    LoginWindow *LoginW;
    UserData    *User;
    TCP_Socket  *Socket;
    typedef QMap<u_int32_t,ChatDialog *>  ChatDialogMap_M;
    ChatDialogMap_M                 ChatDialogMap;
    ChatDialogMap_M::iterator       ChatDialogiterator;
    void        *Buffer;
    void        *Package;
};

#endif // MAINWINDOW_H
