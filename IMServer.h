#ifndef IMSERVER_H
#define IMSERVER_H

#include <unordered_map>
#include <functional>
using namespace std;
using HandleFunc=function<void(struct bufferevnet* &bev,json &js)>;

class IMServer{
    public:
        static IMServer* instance(){ //单例模式
            if(singleInstance==nullptr){
                singleInstance=new IMServer();
            }
            return singleInstance;
        }
        void LoginHandler(struct bufferevnet* &bev,json &js);
        void SignupHandler(struct bufferevnet* &bev,json &js);
    private:
        static IMServer* singleInstance;
        unordered_map<int,HandleFunc> handlerMap; 
        unordered_map<int,struct bufferevnet*> userMap; //用户登录表






};

#endif