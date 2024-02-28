#include "DBconnPool.hpp"



DBconnPool* DBconnPool::instance(){
    static DBconnPool p;
    return &p;
}

void DBconnPool::setServer(string serverIP,string username,string password,unsigned int port){
    _serverIP=serverIP;
    _username=username;
    _password=password;
    _port=port;
}

bool DBconnPool::init(int num){
    is_shutdown=false;
    connPool=stack<MYSQL_DB*>();
    _connNum=num;
    for(int i=0;i<_connNum;i++){
        MYSQL_DB* db=new MYSQL_DB();
        if(!db) {//创建失败
            cout<<"MYSQL_DB create  failed!"<<endl;
            return false;
        } 
        if(!db->connect(_serverIP.c_str(),_username.c_str(),_password.c_str(),NULL,_port)) {//连接失败
            cout<<"connect failed!"<<endl;
            return false;
        } 
        connPool.push(db);
    }
    return true;
}

void DBconnPool::close(){
    is_shutdown=true;
    std::unique_lock<std::mutex> lock(mux);
    if(connPool.size()!=_connNum){
        cv.wait(lock);
    }
    while(!connPool.empty()){
        MYSQL_DB* db=connPool.top();
        connPool.pop();
        //close
        delete db;
    }
}

MYSQL_DB* DBconnPool::getConn(){
    if(is_shutdown) return nullptr; //已关闭

    std::unique_lock<std::mutex> lock(mux);
    if(connPool.empty()){
        cv.wait(lock);
    }
    MYSQL_DB* dbconn=connPool.top();
    connPool.pop();
    return dbconn;
}

void DBconnPool::giveBack(MYSQL_DB* db){
    std::lock_guard<std::mutex> lock(mux);
    connPool.push(db);
    cv.notify_one();
    return ;
}