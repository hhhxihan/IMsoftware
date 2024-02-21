#include "friendModel.hpp"
#include "../DBconnPool.hpp"
bool friendModel::insert(friendMsg& _friendMsg){
    char sql[MAXSIZE];
    sprintf(sql,"insert into friend(userID,friendID,state) values(%d,%d,%d)",_friendMsg.getUserID(),_friendMsg.getFriendID(),_friendMsg.getState());
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    bool state=conn->update(sql);
    if(!state){
        cout<<"insert failed"<<endl;
    }

    sprintf(sql,"insert into friend(userID,friendID,state) values(%d,%d,%d)",_friendMsg.getFriendID(),_friendMsg.getUserID(),_friendMsg.getState());
    bool conn->update(sql);
    if(!state){
        cout<<"insert failed"<<endl;
    }
    DBconnPool::instance()->giveBack(conn);
}

vector<user> friendModel::query(user& _user){
    char sql[MAXSIZE];
    sprintf(sql,"select B.id,B.name,B.state from friend A inner join user B ON A.friendID=B.id where A.userID=%d",_user.getId());
    vector<user> v;
    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    MYSQL_RES* res=conn->query(sql);
    MYSQL_ROW row;
    user _user;
    while((row=mysql_fetch_row(res))){
        _user.setId(std::stoi(row[0]));
        _user.setName(row[1]);
        _user.setPassword(NULL);
        _user.setState(std::stoi(row[2]));

        v.push_back(_user);
    }
    return v;

}