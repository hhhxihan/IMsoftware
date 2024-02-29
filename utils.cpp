#include "utils.h"



bool readMsgPkg(struct bufferevent* bev,char* buf,MSGHEAD* msgHeadPtr){
    int pkglen=0;
    int len=msgHeadPtr->len;
    
    while(pkglen!=len){
        int t=bufferevent_read(bev,buf,len-pkglen);
        pkglen+=t;
        buf[t]='\0';
    }
    return true;
}

void respondMsg(struct bufferevent* bev,bool success,std::string _msg){ //回复消息
    _respondMsg rsp;
    rsp.code=success;
    memcpy(rsp.msg,_msg.c_str(),sizeof(rsp.msg));

    char buf[sizeof(rsp)];
    bufferevent_write(bev,buf,sizeof(buf));
}