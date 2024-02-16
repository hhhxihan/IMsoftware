#include "MYSQL_DB.hpp"

MYSQL_DB::MYSQL_DB(){
    conn=mysql_init(NULL);
}

bool MYSQL_DB::connect(const char* host,const char* user,const char* password,const char* database,unsigned int port=0){
    if(mysql_real_connect(conn,host,user,password,database,port,NULL,0)==NULL){
        return false;
    }
    return  true;
}