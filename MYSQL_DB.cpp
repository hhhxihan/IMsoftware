#include "MYSQL_DB.hpp"

MYSQL_DB::MYSQL_DB(){
    conn=mysql_init(NULL);
}

bool MYSQL_DB::connect(const char* host,const char* user,const char* password,const char* database,unsigned int port=0){
    if(mysql_real_connect(conn,host,user,password,database,port,NULL,0)==NULL){
        cout<<"MYSQL_DB.cpp:connect failed"<<endl;
        return false;
    }
    return  true;
}

MYSQL_RES* MYSQL_DB::query(string sql){

}

int MYSQL_DB::update(string sql){
    int _state=mysql_query(conn,sql.c_str());
    return _state;
}