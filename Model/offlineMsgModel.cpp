#include "offlineMsgModel.hpp"
#include "../DBconnPool.hpp"


bool offlineMsgModel::insert(offlineMsg& _msg){
    char sql[maxsize];
    sprintf(sql,"insert into offlineMsg(toID,fromID,type,msg) values(%d,%d,%d,'%s',);",_msg.getToID(),_msg.getFromID(),_msg.getType(),_msg.getMsg());

    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    int _state=conn->update(sql);
    if(!_state){
        cout<<"insert offlineMsg failed!"<<endl;
        return false;
    }
    DBconnPool::instance()->giveBack(conn);

    return true;
}

std::vector<offlineMsg> offlineMsgModel::query(int _id){
    char sql[maxsize];
    sprintf(sql,"select * from offlinMsg where toID=%d",_id);

    MYSQL_DB* conn=DBconnPool::instance()->getConn();
    MYSQL_RES* _res=conn->query(sql);
    
    if(!_res){

    }
    std::vector<offlineMsg> msgVector;
    offlineMsg t;
    std::string s;
    
    MYSQL_ROW row;
    int column;
    while((row=mysql_fetch_row(_res))){ //解析每行数据，并放入到vector中
        t.toID=std::stoi(row[0]);
        t.fromID=std::stoi(row[1]);
        t.type=std::stoi(row[2]);
        t.Msg=row[3];

        msgVector.push_back(t);
    }
    
    DBconnPool::instance()->giveBack(conn);

    return msgVector;
}

