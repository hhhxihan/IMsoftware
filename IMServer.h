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
#include "utils.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include "Redis.h"
#include "IMThread.hpp"
#include "json.hpp"
using json=nlohmann::json;
using namespace std;
#ifndef MAXSIZE
#define MAXSIZE
const int maxsize=1024;
#endif
const int size2=100;
class IMServer;
using HandleFunc=std::function<void(struct bufferevent*,MSGHEAD*)>;

class IMServer{
    public:
        static IMServer* instance(){ //单例模式
            if(singleInstance==nullptr){
                singleInstance=new IMServer();
            }
            return singleInstance;
        }
        static void HandlerMsg(struct bufferevent* bev,void* arg);
        void LoginHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr,void* arg);
        void SignupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void addFriendHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void addGroupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void sendMsgToFrdHdl(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void sendMsgToGrp(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void createGrpHdl(struct buffervent* bev,MSGHEAD* msgHeadPtr);
        void getFriendMSg(struct bufferevent* bev,MSGHEAD* msgHeadPtr);
        void messageCallback(redisAsyncContext *c, void *reply, void *privdata); //redis订阅触发的事件
        IMServer();

        
    private:
        static IMServer* singleInstance;
        unordered_map<CMD,HandleFunc> handlerMap; 
        unordered_map<int,struct bufferevent*> userMap; //用户登录表

        //数据库操作对象
        userModel _userModel;  //用户信息数据库
        offlineMsgModel _offlineMsgModel; //离线消息数据库
        friendModel _friendModel;
        Redis _redis;
        
};

#endif


