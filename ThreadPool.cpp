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
    return true;
}

bool ThreadPool::addTask(evutil_socket_t fd){
    curNum=(curNum+1)%maxNum;
    //向Thread发送信息，激活线程回调事件，线程自己调用addTask;
    int pipefd=threadPool[curNum]->pipefd[1];
    threadPool[curNum]->fdStack.push(fd);
    string ts=std::to_string(fd);
    write(pipefd,ts.c_str(),ts.size());

    return true;
}

