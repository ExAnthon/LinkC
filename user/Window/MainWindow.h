/*
 * Author		： Junfeng Zhang <564691478@qq.com>
 * Last-Change		： April 5, 2014
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "Csocket.h"
#include "LinkC_GUI.h"
#include "linkc_types.h"
#include "MessageRecver.h"
#include "Def/LinkC_Error.h"
#include "LinkC_Settings_Dialog.h"
#include "LinkC_UserInfoSettings_Dialog.h"
#include <QToolBox>
#include <QGroupBox>
#include <QLayout>
#include <QVBoxLayout>
#include <QMainWindow>
#include <QInputDialog>
#include <QToolButton>
#include <QLabel>
#include <QWidget>
#include <QListWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QListView>
#include <QMessageBox>
#include <QLineEdit>
#include <QDialog>
#include <QString>

namespace Ui {
class MainWindow;
class LoginWindow;
class ChatDialog;
}

class MainWindow : public QWidget{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);	   //构造函数
	~MainWindow();	  // 析构函数
	int Login();
	int NetworkInit(void);
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    int InitFriendList(void);
    int InitUserInfo(void);
    FriendArea *friendArea;
    void *package;
private slots:
    void ChatWith(LinkC_Friend_Data);
    void FriendLabelClicked(LinkC_Friend_Data);
    void UserMessage(LinkC_User_Message);
    void SendMessageToServer(LinkC_User_Request);
    void SLOT_LoginWindowExit(void);
    void SLOT_SetUserInfo(LinkC_User_Info);
    void SLOT_SysActionStatus(LinkC_Sys_Status);
    void SLOT_Quit(void);
    void SLOT_Refresh_User_Info(void);
    void SLOT_Refresh_Friend_List(void);
    void SLOT_SetFriendToArea(void*,int);
    void SLOT_SettingDialogClicked(void);
    void SLOT_ExitLabelClicked(void);
    void SLOT_AccountCLabelClicked(void);
signals:
private:
    typedef QMap<int,ChatDialog *>  _Map;
    TCP_csocket                     server;
    int                             Connection_state;
    FriendArea                      * area;
    SetupMenu                       * MainSetupMenu;
    QTabWidget                      * tab;
    QGridLayout                     * TopLayout;
    QVBoxLayout                     * MainLayout;
    QGridLayout                     * layout;
    QWidget                         * Top;
    LinkC_Settings_Dialog           *SettingDialog;
    LinkC_UserInfoSettings_Dialog   *UserInfoSettingsDialog;
    _Map                            ChatDialogMap;
    _Map::iterator                  ChatDialogiterator;
    TCP_MessageRecver               *Recver;
    LinkC_User_Info                 *User_Info;

    LinkC_Label                     *NameLabel;
    LinkC_Label                     *StatLabel;
    LinkC_Label                     *SettingsLabel;
    LinkC_Label                     *ExitLabel;
};








class LoginWindow : public QDialog{
	Q_OBJECT

public:
    explicit LoginWindow(QWidget* = 0);	   //构造函数
	~LoginWindow();	  // 析构函数
    void closeEvent(QEvent *);
	int GetLoginData(login_data &s);
	QPushButton* LoginButton;
	QPushButton* CancelButton;
signals:
    void Exit(void);
public slots:		   // 槽函数
	void QuitClick(void);		 // 退出按钮被按下
	void LoginClick(void);		// 登录按钮被按下
private:
	const char* UserName;
	const char* PassWord;
    QLineEdit * UsernameInput;
    QLineEdit * PasswordInput;

    QLabel* usrLabel;
    QLabel* pwdLabel;
    QGridLayout* gridLayout;
    QHBoxLayout* btnLayout;
    QVBoxLayout* dlgLayout;


	struct login_data st;
};


#endif
