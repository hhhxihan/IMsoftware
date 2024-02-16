#include "IMServer.h"
#include "ThreadPool.hpp"
void callback(struct evconnlistener* evlistener,evutil_socket_t fd,struct sockaddr* address,int socklen,void* arg){
   ThreadPool::instance()->addTask(fd);
}

int main()
{
    struct event_base* base=event_base_new();
    if(!base){
        cout<<"event_base create failed!"<<endl;
        return -1;
    }

    ThreadPool::instance()->init(10);
     //设置服务器的地址信息
    struct sockaddr_in server_addr;
    server_addr.sin_addr.s_addr=INADDR_ANY;
    server_addr.sin_port=htons(21);
    server_addr.sin_family=AF_INET;

    struct evconnlistener* ev=evconnlistener_new_bind(base,callback,NULL, LEV_OPT_REUSEABLE,100,
                                            (struct sockaddr*)&server_addr,sizeof(server_addr));
    if (!ev) { 
        cout << "evconnlistener create failed: " << evutil_socket_error_to_string( evutil_socket_geterror()) << endl;
    }

    cout<<"start listen..."<<endl;
    event_base_dispatch(base);
    
    evconnlistener_free(ev);
    event_base_free(base);
}