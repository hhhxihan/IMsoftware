#ifndef DBCONNPOOL_HPP
#define DBCONNPOOL_HPP
#include "MYSQL_DB.hpp"
#include <stack>
#include <iostream>
#include <mutex>
#include <condition_variable>
using namespace std;

const int MAXSIZE=1024;
class DBconnPool{ //数据库连接池


    public:
    std::mutex mux;
    std::condition_variable cv;
    static DBconnPool* instance();
    bool init(int num=8);

    
    void setServer(string serverIP,string username,string password,unsigned int port);
    MYSQL_DB* getConn();
    void giveBack(MYSQL_DB* db);
    void close();
    
    protected:
    std::stack<MYSQL_DB*> connPool; //存储数据库的连接
    int _connNum; //连接的数量
    bool is_shutdown;

    std::string _serverIP;
    std::string _username;
    std::string _password;
    unsigned int _port;
};

#endif
