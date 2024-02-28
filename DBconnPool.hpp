#ifndef DBCONNPOOL_HPP
#define DBCONNPOOL_HPP
#include "MYSQL_DB.hpp"
#include <stack>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

#ifndef MAXSIZE
#define MAXSIZE
const int maxsize=1024;
#endif
class DBconnPool{ //数据库连接池

    public:
    std::mutex mux;
    std::condition_variable cv;
    
    static DBconnPool* instance(); //单例模式
    bool init(int num=8);  //创建的数据库连接个数
    void setServer(string serverIP,string username,string password,unsigned int port);
    MYSQL_DB* getConn(); //获得一个连接
    void giveBack(MYSQL_DB* db); //归还一个连接
    void close();
    
    protected:
    std::stack<MYSQL_DB*> connPool; //存储数据库的连接
    int _connNum; //连接的数量
    bool is_shutdown; //

    //连接的端口信息
    std::string _serverIP;
    std::string _username;
    std::string _password;
    unsigned int _port;
};

#endif
