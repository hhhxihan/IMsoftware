#include "IMServer.h"

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
    shared_ptr<char> bufPtr=make_shared<char>(MAXSIZE);
    char* buf=bufPtr.get();
    readMsgPkg(bev,buf,msgHeadPtr);
    SIGNUPmsg* signupPtr=reinterpret_cast<SIGNUPmsg*>(buf);
    user _user;
    _user.setName(signupPtr->username);
    _user.setPassword(signupPtr->pwd);

    int _state=_userModel.insert(_user);
}

void IMServer::sendMsgToFrdHdl(struct bufferevent* &bev,MSGHEAD* msgHeadPtr){
    shared_ptr<char> bufPtr=make_shared<char>(MAXSIZE);
    char* buf=bufPtr.get();
    readMsgPkg(bev,buf,msgHeadPtr);

    struct SENDMSG* _sendMsgPtr=reinterpret_cast<SENDMSG*>(buf);

    auto toUserBev=userMap.find(_sendMsgPtr->toID);
    if(toUserBev!=userMap.end()){ //如果用户已登录，直接发送
        //组装消息
        bufferevent_write(toUserBev->second,buf,sizeof(buf));

        return ;
    }

    //否则要存储到数据库
    offlineMsg _offlineMsg;
    _offlineMsg.toID=_sendMsgPtr->toID;
    _offlineMsg.fromID=_sendMsgPtr->fromID;
    _offlineMsg.type=_sendMsgPtr->type;
    _offlineMsg.Msg=_sendMsgPtr->msg;

    _offlineMsgModel.insert(_offlineMsg);
}

void IMServer::addFriendHandler(struct bufferevnet* &bev,MSGHEAD* msgHeadPtr){
    shared_ptr<char> bufPtr=make_shared<char>(MAXSIZE);
    char* buf=bufPtr.get();
    readMsgPkg(bev,buf,msgHeadPtr);

    ADDFreindmsg* frdMsgPtr=reinterpret_cast<ADDFreindmsg*>(buf);

    friendMsg _friendMsg;
    _friendMsg.setUserID(frdMsgPtr->userID);
    _friendMsg.setFriendID(frdMsgPtr->friendID);
    _friendMsg.setState(frdMsgPtr->state);


}
