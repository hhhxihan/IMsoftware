#include "IMThread.hpp"
#include "IMServer.h"



void IMThread::addTask(evutil_socket_t fd,short events,void* arg){
    IMThread* t=reinterpret_cast<IMThread*>(arg);

    shared_ptr<char> buf=make_shared<char>(20);
    char* bufptr=buf.get();
    int len=read(t->pipefd[0],bufptr,20);
    int* fdPtr=reinterpret_cast<int*>(bufptr);

    struct bufferevent* bev=bufferevent_socket_new(t->base,*fdPtr,BEV_OPT_CLOSE_ON_FREE);
    if(!bev){
        cout<<"bufferevent create failed!"<<endl;
        return ;
    }
    // IMServer* t=IMServer::instance();
    bufferevent_setcb(bev,IMServer::HandlerMsg,NULL,NULL,NULL);
    bufferevent_enable(bev,EV_READ);
}

void IMThread::Main(){
    event_base_dispatch(base);
    event_base_free(base);
}

bool IMThread::init(){
    if(-1==pipe(pipefd)){
        cout<<"pipe initalization failed!"<<endl;
    }
    base=event_base_new();
    if(!base){
        cout<<"event_base create failed!"<<endl;
        return false;
    }
    
    struct event* bev=event_new(base,pipefd[0],EV_READ,addTask,this);
    event_add(bev,0);
    thread th(&IMThread::Main,this);
    th.detach();

    return true;
}

