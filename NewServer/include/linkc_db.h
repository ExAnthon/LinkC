#ifndef _LINKC_DB_H_
#define _LINKC_DB_H_

#include <sqlite3.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include "linkc_def.h"

//##########用户数据库结构#############
#define USER_UID        0
#define USER_USERNAME   1
#define USER_PASSWORD   2
#define USER_NAME       3
#define USER_TEL        4
#define USER_COMPANY    5
#define USER_ADDRESS    6
#define USER_JOIN_TIME  7
#define USER_LAST_LOGIN 8
#define USER_LAST_IP    9
#define USER_STATUS     10
#define USER_SOCKFD     11
//#########好友数据库结构#############
#define FRIEND_UID      0
#define FRIEND_NICKNAME 1
//#########完毕          #############
int     InitSqliteDb    (void);
/* 打开数据库，并且设置全局变量 */

int     CheckPassword   (LoginData *Data,uint32_t *UID);
/*
 *  TODO:检验用户密码是否正确，并且返回 UserData 中的 UID 键值
 *  ARGS:   [LoginData*]            LoginData 结构类型指针
            [uint32_t* ]            uint32_t 指针，用于返回UID
 *  RETN:   [成功]                  用户的UID                   [恒大于0]
 *          [失败]                  LINKC_FAILURE
 *  
 */

int     GetFriendsData  (int UID,UserData ** ffb);
/*
 * 构建好友的资料，返回值为执行状态，［>0］为成功，［－1］为失败，正常返回值为好友个数
 * 参数：1    int UID        谁的好友，这里的UID为用户唯一的标识
 * 参数：2    struct friend_data * 的地址    运行完成后构建一个指针数组
 */

int     GetUserData     (int UID, int DestUID,UserData *User);
/*
 * 获得单个好友的资料，返回值为得到的资料
 * 参数：1    int UID        UID为用户唯一标识
 * 参数：2    int &STATE    作为返回的状态
 */

int     SetStatus       (UserData *User,struct sockaddr_in Addr, int _Flag);
/*
 * 设置用户的状态
 * 参数：1      UserData*       UserData指针
 * 参数：2      sockaddr_in     用户现在的网络地址
 * 参数：3      int _Flag       操作参数
 */

/*舍弃*/
//extern int get_info (int UID,int _Flag);
/*
 * 获得目标UID用户在线状态    返回[0]表示不在线，[1]表示隐身，[2]表示在线
 * 获得目标UID用户SOCKFD    返回[0]表示没有连接，[-1]表示失败，其余为sockfd
 * 参数：1    int UID        用户的UID
 * 参数：2    int _Flag    操作方式
 */
#define STATUS_GET    1
#define SOCKFD_GET    2

int AddFriend(int UID, int _who_ID,int _Flag);

//extern int get_user_info(int UID, struct user_info **info);
/*
 * 获得目标UID用户的资料    返回[LINKC_SUCCESS / LINKC_FAILURE]
 * 参数：1    int UID        用户的UID
 * 参数：2    user_info结构体指针
 */

#define LINKC_FRIEND_ADD                    1
#define LINKC_FRIEND_ADD_WITH_NICKNAME      2
#define LINKC_FRIEND_DELETE                 3

#define USER_DB_PATH        "../data/user.db"
#define FRIEND_DB_PATH      "../data/friend.db"

#endif
