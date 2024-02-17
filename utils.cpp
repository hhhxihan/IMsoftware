
#include "msgFormat.h"


bool readMsgPkg(struct bufferevent* bev,char* buf,MSGHEAD* msgHeadPtr){
    int pkglen=0;
    int len=msgHeadPtr->len;
    while(pkglen!=len){
        pkglen+=bufferevent_read(bev,buf,len-pkglen);
    }
    return true;
}