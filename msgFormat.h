#ifndef MSGFORMAT_H
#define MSGFORMAT_H

enum CMD{
    LOGIN=1000,
    SIGNUP,
    ADDFRIEND,
    DELFRIEND,
    CREATEGROUP,
    DISSOLVEGROUP,
    ADDGROUP,
    QUITGROUP,
    SENDMSGTOF,
    SENDMSGTOG
};

struct MSGHEAD{
    char version;
    enum CMD command;
    int len;
};

struct SIGNUPmsg{
    char username[32];
    char pwd[32];

}; //8

struct LOGINmsg{
    int userID;
    char pwd[32];
};

struct SENDMSG{
    int toID;
    int fromID;
    int type; 
    char msg[128];
};

struct ADDFreindmsg{

};



#endif