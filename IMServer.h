#ifndef IMSERVER_H
#define IMSERVER_H

#include <unordered_map>
#include <functional>
#include "./Model/userModel.hpp"
#include "./Model/offlineMsgModel.hpp"
#include "./Model/friendModel.hpp"
#include "msgFormat.h"
#include <iostream>
#include <memory>
#include "./bo/user.hpp"
#include "./bo/offlineMsg.hpp"
#include "./bo/friendMsg.hpp"
#include "utils.cpp"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include "json.hpp"
using json=nlohmann::json;
using namespace std::placeholders;
using namespace std;
#ifndef MAXSIZE
#define MAXSIZE
const int maxsize=1024;
#endif

using HandleFunc=function<void(struct bufferevent* bev,MSGHEAD* msgHeadPtr)>;

class IMServer{
    public:
        static IMServer* instance(){ //单例模式
            if(singleInstance==nullptr){
                singleInstance=new IMServer();
            }
            return singleInstance;
        }
        static void HandlerMsg(struct bufferevent* bev,void* arg);
        void LoginHandler(struct bufferevnet* bev,MSGHEAD* msgHeadPtr);
        void SignupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void addFriendHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void addGroupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void sendMsgToFrdHdl(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void sendMsgToGrp(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void createGrpHdl(struct buffervent* bev,MSGHEAD* msgHeadPtr);
        void getFriendMSg(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        IMServer();
    private:
        static IMServer* singleInstance;
        static unordered_map<int,HandleFunc> handlerMap; 
        unordered_map<int,struct bufferevent*> userMap; //用户登录表

        //数据库操作对象
        userModel _userModel;  //用户信息数据库
        offlineMsgModel _offlineMsgModel; //离线消息数据库
        friendModel _friendModel;


};

#endif


