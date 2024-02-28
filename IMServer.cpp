#include "IMServer.h"



IMServer* IMServer::singleInstance=new IMServer();

IMServer::IMServer(){ //将函数添加到哈希表中
    handlerMap.insert(make_pair(LOGIN,std::bind(&IMServer::LoginHandler,this,std::placeholders::_1,std::placeholders::_2)));
    handlerMap.emplace(make_pair(SIGNUP,bind(&IMServer::SignupHandler,this,std::placeholders::_1,std::placeholders::_2)));
    handlerMap.emplace(make_pair(SENDMSGTOF,bind(&IMServer::sendMsgToFrdHdl,this,std::placeholders::_1,std::placeholders::_2)));
    handlerMap.emplace(make_pair(ADDFRIEND,bind(&IMServer::addFriendHandler,this,std::placeholders::_1,std::placeholders::_2)));
    handlerMap.emplace(make_pair(SENDMSGTOF,bind(&IMServer::getFriendMSg,this,std::placeholders::_1,std::placeholders::_2)));
}


void IMServer::HandlerMsg(struct bufferevent* bev,void* arg){
    int len=sizeof(struct MSGHEAD)+1;
    // auto headData=make_shared<char[]>(len); g++20
    char* charPtr = new char[maxsize];
    int headlen=bufferevent_read(bev,charPtr,sizeof(struct MSGHEAD));
    charPtr[headlen]='\0';
    cout<<charPtr<<endl;

    if(headlen!=sizeof(struct MSGHEAD)){
        std::cout<<"head data recieve failed!";
    }
    IMServer* t=IMServer::instance();
    MSGHEAD* msgHeadPtr = reinterpret_cast<MSGHEAD*>(charPtr);
    if(t->handlerMap.find((msgHeadPtr->command))!=t->handlerMap.end()){
        auto handler=t->handlerMap[(msgHeadPtr->command)];
        handler(bev,msgHeadPtr);
    }
    else{
        cout<<"command errno"<<endl;
    }
    delete[] charPtr;
}
void IMServer::LoginHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
  cout<<"handler Login msg"<<endl;
}


void IMServer::SignupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    cout<<"handler signup msg"<<endl;
    try {
        // auto bufPtr = std::shared_ptr<char[size2]>(); //C++20 以上支持
        char* buf = new char[100];
        if(buf==nullptr){
            cout<<"IMServer.cpp 47:create buf failed"<<endl;
        }
        cout<<"buf ???"<<endl;
        readMsgPkg(bev,buf,msgHeadPtr);

        SIGNUPmsg* signupPtr=reinterpret_cast<SIGNUPmsg*>(buf);
        user _user;
        _user.setName(signupPtr->username);
        _user.setPassword(signupPtr->pwd);

        int _state=_userModel.insert(_user);
        if(_state){
            cout<<"Signup success : username:"<<_user.getName()<<endl;
        }
        delete[] buf;
    }
    catch (const std::bad_alloc& e) {
        cout << "IMServer.cpp: create buf failed: " << e.what() << endl;
    }
    
}

void IMServer::sendMsgToFrdHdl(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    // auto bufPtr=make_shared<char[]>(maxsize); g++20
    char* buf=new char[maxsize];
    readMsgPkg(bev,buf,msgHeadPtr);

    struct SENDMSG* _sendMsgPtr=reinterpret_cast<SENDMSG*>(buf);

    auto toUserBev=userMap.find(_sendMsgPtr->toID);
    if(toUserBev!=userMap.end()){ //如果用户已登录，直接发送
        //组装消息
        bufferevent_write(toUserBev->second,buf,sizeof(buf));

        return ;
    }
    delete[] buf;
    //否则要存储到数据库
    offlineMsg _offlineMsg;
    _offlineMsg.toID=_sendMsgPtr->toID;
    _offlineMsg.fromID=_sendMsgPtr->fromID;
    _offlineMsg.type=_sendMsgPtr->type;
    _offlineMsg.Msg=_sendMsgPtr->msg;

    _offlineMsgModel.insert(_offlineMsg);
}

void IMServer::addFriendHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    // auto bufPtr=make_shared<char[]>(maxsize);
    char* buf=new char[maxsize];
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
    delete[] buf;
}

void IMServer::getFriendMSg(struct bufferevent* bev,MSGHEAD* msgHeadPtr){
    // auto bufPtr=make_shared<char[]>(maxsize);
    char* buf=new char[maxsize];
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
    delete[] buf;
}


void IMServer::addGroupHandler(struct bufferevent* bev,MSGHEAD* msgHeadPtr){

}

void IMServer::sendMsgToGrp(struct bufferevent* bev,MSGHEAD* msgHeadPtr){

}
void IMServer::createGrpHdl(struct buffervent* bev,MSGHEAD* msgHeadPtr){

}
