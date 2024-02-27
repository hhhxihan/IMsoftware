#ifndef IMTHREAD_HPP
#define IMTHREAD_HPP
#include "IMServer.h"
#include <event2/event.h>
#include <event2/bufferevent.h>
#include <iostream>
#include <thread>
class IMThread{

    public:
    bool init();
    void Main();
    static void addTask(evutil_socket_t fd,short events,void* arg);
    int pipefd[2];
    private:
        event_base* base;
        

};

#endif