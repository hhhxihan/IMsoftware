#include "IMServer.h"



IMServer* IMServer::singleInstance=new IMServer();

IMServer::IMServer(){ //将函数添加到哈希表中
    handlerMap.emplace(LOGIN,bind(&IMServer::LoginHandler,this,_1,_2));
    handlerMap.emplace(SIGNUP,bind(&IMServer::SignupHandler,this,_1,_2));
    handlerMap.emplace(SIGNUP,bind(&IMServer::sendMsgToFrdHdl,this,_1,_2));
    handlerMap.emplace(ADDFRIEND,bind(&IMServer::addFriendHandler,this,_1,_2));
    handlerMap.emplace(SENDMSGTOF,bind(&IMServer::getFriendMSg,this,_1,_2));
}


void IMServer::HandlerMsg(struct bufferevent* bev,void* arg){

    shared_ptr<char> headData=make_shared<char>(sizeof(struct MSGHEAD)+1);
    char* charPtr = headData.get();
    int headlen=bufferevent_read(bev,charPtr,sizeof(struct MSGHEAD));
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

void IMServer::sendMsgToFrdHdl(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
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

void IMServer::addFriendHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    shared_ptr<char> bufPtr=make_shared<char>(MAXSIZE);
    char* buf=bufPtr.get();
    readMsgPkg(bev,buf,msgHeadPtr);

    ADDFreindmsg* frdMsgPtr=reinterpret_cast<ADDFreindmsg*>(buf);

    friendMsg _friendMsg;
    _friendMsg.setUserID(frdMsgPtr->userID);
    _friendMsg.setFriendID(frdMsgPtr->friendID);
    _friendMsg.setState(frdMsgPtr->state);

    int _state=_friendModel.insert(_friendMsg);
    if(!_state){
        cout<<"insert newfriend failed!"<<endl;
    }

}

void IMServer::getFriendMSg(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    shared_ptr<char> bufPtr=make_shared<char>(MAXSIZE);
    char* buf=bufPtr.get();
    readMsgPkg(bev,buf,msgHeadPtr);

    GetFriendMsg* getFrdPtr=reinterpret_cast<GetFriendMsg*>(buf);
    int id=getFrdPtr->userID;

    vector<user> v=_friendModel.query(id);
    json js,js2;
    
    js["vector"]=json::array();
    for(user &_user:v){
        js2["userID"]=_user.getId();
        js2["name"]=_user.getName().c_str();
        js2["state"]=_user.getState();

        js["vector"].push_back(js2.dump());
    }
    string s=js.dump();
    
    
    char* rspbuf=reinterpret_cast<char*>(msgHeadPtr);
    string respondMsg=string(rspbuf);
    msgHeadPtr->len=respondMsg.size();
    respondMsg+=s;
    bufferevent_write(bev,respondMsg.c_str(),respondMsg.size());

}
