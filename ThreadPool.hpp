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

    private:
    std::vector<IMThread*> threadPool;
    int curNum;
    int maxNum;
};

#endif