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

void respondMsg(struct bufferevent* bev,int success,std::string _msg){ //回复消息
    _respondMsg rsp;
    rsp.code=success;
    memcpy(rsp.msg,_msg.c_str(),_msg.size());
    rsp.msg[_msg.size()+1]='\0';

    char* buf=new char[sizeof(rsp)];
    memset(buf,0,sizeof(rsp));
    std::cout << "rsp.code: " << rsp.code << " rsp.msg: " << rsp.msg <<" rsp.size:"<<sizeof(rsp)<<std::endl;

    memcpy(buf,&rsp,sizeof(rsp));
    bufferevent_write(bev,buf,sizeof(rsp));
    delete[] buf;
}