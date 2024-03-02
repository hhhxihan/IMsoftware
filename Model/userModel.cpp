#include "userModel.hpp"
#include <cstdio>


bool userModel::insert(user& _user){
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    char sql[maxsize]={0};
    _user.setState(1);
    sprintf(sql,"insert into user(_username,_password,_state) values('%s','%s',%d);",_user.getName().c_str(),_user.getPassword().c_str(),_user.getState());
    cout<<sql<<endl;
    int _state=conn->update(sql);
    if(_state){
        cout<<"insert failed!"<<endl;
        DBconnPool::instance()->giveBack(conn);
        return false;
    }
    query(_user);
    DBconnPool::instance()->giveBack(conn);
    
    return true;
}

bool userModel::query(user& _user){ 
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    char sql[maxsize]={0};
    _user.setState(1);
    sprintf(sql,"select * from user where _username='%s' and _password='%s';",_user.getName().c_str(),_user.getPassword().c_str());
    cout<<sql<<endl;
    MYSQL_RES* _res=conn->query(sql);
    if(_res){
        MYSQL_ROW row=mysql_fetch_row(_res);
        _user.setId(std::stoi(row[0]));
        _user.setState(std::stoi(row[3]));
        cout<<"userID is:"<<_user.getId()<<endl;   
    }
    DBconnPool::instance()->giveBack(conn);
    if(!_res){

        cout<<"user not found"<<endl;
        return false;
    }
    
    return true;
 }
 bool userModelqueryIfLogged(int id){
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    char sql[maxsize]={0};
    sprintf(sql,"select _state from user where _id=%d;",id);
    cout<<sql<<endl;
    MYSQL_RES* _res=conn->query(sql);
    if(_res){
        MYSQL_ROW row=mysql_fetch_row(_res);
        if(std::stoi(row[0])==ISLOGGEDIN){
            DBconnPool::instance()->giveBack(conn);
            return true;
        }  
    }
    DBconnPool::instance()->giveBack(conn);
    return false;
 }