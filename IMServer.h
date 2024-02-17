#ifndef IMSERVER_H
#define IMSERVER_H

#include <unordered_map>
#include <functional>
#include "./Model/userModel.hpp"
#include "./Model/offlineMsgModel.hpp"
#include "msgFormat.h"
#include <iostream>
#include <memory>
#include "./bo/user.hpp"
#include "./bo/offlineMsg.hpp"
#include "./bo/friendMsg.hpp"
#include "utils.cpp"

#define MAXSIZE 1024
using namespace std;

using HandleFunc=function<void(struct bufferevnet* &bev,json &js)>;

class IMServer{
    public:
        static IMServer* instance(){ //单例模式
            if(singleInstance==nullptr){
                singleInstance=new IMServer();
            }
            return singleInstance;
        }
        void HandlerMsg(struct bufferevent* bev,void* arg);
        void LoginHandler(struct bufferevnet* &bev);
        void SignupHandler(struct bufferevnet* &bev);
        void addFriendHandler(struct bufferevnet* &bev);
        void addGroupHandler(struct bufferevent* &bev);
        void sendMsgToFrdHdl(struct bufferevent* &bev);
        void sendMsgToGrp(struct bufferevent* &bev);
        void createGrpHdl(struct buffervent* &bev);
    private:
        static IMServer* singleInstance;
        unordered_map<int,HandleFunc> handlerMap; 
        unordered_map<int,struct bufferevnet*> userMap; //用户登录表

        //数据库操作对象
        userModel _userModel;  //用户信息数据库
        offlineMsgModel _offlineMsgModel; //离线消息数据库


};

#endif


