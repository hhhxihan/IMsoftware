#include "userModel.hpp"
#include <cstdio>
#define MAXSIZW 1024

bool userModel::insert(user& _user){
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    char sql[MAXSIZE]={0};
    sprintf(sql,"insert into user(name,password,state) values('%s','%s','%s')",_user.getName().c_str(),_user.getPassword().c_str(),_user.getState().c_str());
    int _state=conn->update(sql);
    if(!_state){
        cout<<"insert failed!"<<endl;
    }
    DBconnPool::instance()->giveBack(conn);
}

bool userModel::insert(user& _user){
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    DBconnPool::instance()->giveBack(conn);
}