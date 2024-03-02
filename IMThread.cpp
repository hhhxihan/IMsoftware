#include "IMThread.hpp"
#include "IMServer.h"



void IMThread::addTask(evutil_socket_t fd,short events,void* arg){
    
    IMThread* t=reinterpret_cast<IMThread*>(arg);

    int sockfd=t->fdStack.top(); //线程安全
    t->fdStack.pop();
    if(sockfd==0){
        cout<<"sockfd is null"<<endl;
    }

    struct bufferevent* bev=bufferevent_socket_new(t->base,sockfd,BEV_OPT_CLOSE_ON_FREE);
    if(!bev){
        cout<<"bufferevent create failed!"<<endl;
        return ;
    }
    bufferevent_setcb(bev,IMServer::HandlerMsg,NULL,NULL,arg);
    bufferevent_enable(bev,EV_READ);
}

void IMThread::Main(){
    event_base_dispatch(base);
    event_base_free(base);
}

bool IMThread::init(){
    fdStack=stack<int>();
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
void IMThread::addRedisEvent(redisContext* context,string _cmd){
    redisLibeventAttach(context, base);
    context->ev.data = base;

    redisAsyncCommand(context, IMServer::messageCallback, nullptr, _cmd.c_str());
    cout<<"Add redis event success!"<<endl;
}

