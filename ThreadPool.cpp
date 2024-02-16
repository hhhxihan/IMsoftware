#include "ThreadPool.hpp"

bool ThreadPool::init(int num){
    maxNum=num;
    threadPool=vector<IMThread*>(num);
    for(IMThread* &ptr:threadPool){
        ptr=new IMThread();
        if(!ptr){
            cout<<"IMThread create false!"<<endl;
            return false;
        }
        ptr->init();
    }
}

bool ThreadPool::addTask(evutil_socket_t fd){
    curNum=(curNum+1)%maxNum;
    threadPool[curNum]->addTask(fd);
}

