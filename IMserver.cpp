#include "msgFormat.h"
#include "IMServer.h"
#include <iostream>
#include <memory>
#include "./bo/user.hpp"
#define MAXSIZE 1024
using namespace std;

IMServer* IMServer::singleInstance=new IMServer();


void IMServer::HandlerMsg(struct bufferevent* bev,void* arg){
    shared_ptr<char> headData=make_shared<char>(sizeof(struct MSGHEAD)+1);
    char* charPtr = headData.get();
    int headlen=bufferevnet_read(bev,headdata,sizeof(struct MSGHEAD));
    if(headlen!=sizeof(struct MSGHEAD)){
        std::cout<<"head data recieve failed!";
    }
    
    MSGHEAD* msgHeadPtr = reinterpret_cast<MSGHEAD*>(charPtr);
    if(handlerMap.find(static_cast<int>(msgHeadPtr->command))!=handlerMap.end()){
        auto handler=handlerMap[static_cast<int>(msgHeadPtr->command)];
        handler(bev,msgHeadPtr);
    }
    else{
        cout<<"command errno"<<endl;
    }
}

void IMServer::SignupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    char buf[MAXSIZE];
    int pkglen=0;
    int len=msgHeadPtr->len;
    while(pkglen!=len){
        pkglen+=bufferevent_read(bev,buf,len-pkglen);
    }
    SIGNUPmsg* signupPtr=reinterpret_cast<SIGNUPmsg*>(buf);
    user _user;
    _user.setName(signupPtr->username);
    _user.setPassword(signupPtr->pwd);

    int _state=_userModel.insert(_user);
}
