#include "IMThread.hpp"



void IMThread::addTask(evutil_socket_t fd){
    struct bufferevent* bev=bufferevent_socket_new(base,fd,BEV_OPT_CLOSE_ON_FREE);
    if(!bev){
        cout<<"bufferevent create failed!"<<endl;
        return ;
    }
    bufferevent_setcb(bev,IMServer::HandlerMsg,NULL,NULL,NULL);
    bufferevnet_enable(bev,EV_READ);
}

bool IMThread::init(){
    base=event_base_new();
    if(!base){
        cout<<"event_base create failed!"<<endl;
        return false;
    }

    thread th(Main,this);
    th.detach();
}

void IMThread::Main(){
    event_base_dispatch(base);
    event_base_free(base);
}