#include "userModel.hpp"
#include <cstdio>


bool userModel::insert(user& _user){
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    char sql[maxsize]={0};
    _user.setState(1);
    sprintf(sql,"insert into user(name,password,state) values('%s','%s',%d)",_user.getName().c_str(),_user.getPassword().c_str(),_user.getState());
    cout<<sql<<endl;
    int _state=conn->update(sql);
    if(!_state){
        cout<<"insert failed!"<<endl;
        DBconnPool::instance()->giveBack(conn);
        return false;
    }
    return true;
}

// bool userModel::insert(user& _user){
//     MYSQL_DB* conn=DBconnPool::instance()->getConn();
//     DBconnPool::instance()->giveBack(conn);
// }