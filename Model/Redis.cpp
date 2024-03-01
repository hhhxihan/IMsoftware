#include "Redis.h"


Redis::~Redis(){

}

void Redis::init(char ip[],int port){
    context=redisConnect(ip, port);
    if(context==nullptr||context->err){
        //错误处理

        return ;
    }
    cout<<"Redis initalization success"<<endl;
}

void Redis::subscribe(int channel){
    redisReply* reply=redisCommand(context,"subsribe %d",channel);
    if(reply==nullptr){
        
    }
}
void Redis::publish(int channel,string msg){
    redisReply* reply=redisCommand(context,"publis %d %s",channel,msg.c_str());
    if(reply==nullptr){
        
    }
}
void Redis::unsubscrite(int channel){
    redisReply* reply=redisCommand(context,"unsubsribe %d",channel);
    if(reply==nullptr){
        
    }
}