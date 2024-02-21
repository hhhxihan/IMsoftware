#include "IMThread.hpp"



void IMThread::addTask(){
    shared_ptr<char> buf=make_shared<char>(20);
    char* bufptr=buf.get();
    int len=read(pipefd[0],bufptr,20);
    int* fdPtr=reinterpret_cast<int*>(bufptr);

    struct bufferevent* bev=bufferevent_socket_new(base,*fdPtr,BEV_OPT_CLOSE_ON_FREE);
    if(!bev){
        cout<<"bufferevent create failed!"<<endl;
        return ;
    }
    bufferevent_setcb(bev,IMServer::HandlerMsg,NULL,NULL,NULL);
    bufferevnet_enable(bev,EV_READ);
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
    thread th(Main,this);
    th.detach();
}

void IMThread::Main(){
    event_base_dispatch(base);
    event_base_free(base);
}