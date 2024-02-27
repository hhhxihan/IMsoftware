#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include "IMThread.hpp"
#include <vector>
class ThreadPool{
    public:
    static ThreadPool* instance(){
        static ThreadPool pool;
        return &pool;
    }
    bool addTask(evutil_socket_t fd);
    bool init(int num);
    std::vector<IMThread*> threadPool;
    private:
    int curNum;
    int maxNum;
};

#endif