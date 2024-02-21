#ifndef IMTHREAD_HPP
#define IMTHREAD_HPP
#include "IMServer.h"
#include <iostream>
#include <thread>
class IMThread{

    public:
    bool init();
    void Main();
    void addTask(evutil_socket_t fd);
    private:
        event_base* base;
        int pipefd[2];

};

#endif