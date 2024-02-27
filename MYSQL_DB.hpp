#ifndef MYSQL_HPP
#define MYSQL_HPP
#include <mysql/mysql.h>
#include <string>
#include "DBconnPool.hpp"
using namespace std;


class MYSQL_DB{ //封装Mysql
    public:
    MYSQL_DB();
    bool connect(const char* host,const char* user,const char* password,const char* database,unsigned int port);
    MYSQL_RES* query(string sql);
    bool update(string sql);

    protected:
    MYSQL* conn;
    DBconnPool* poolPtr;
};

#endif

