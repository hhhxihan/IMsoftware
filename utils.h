#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include "msgFormat.h"
#include <string>
#include <cstring>

#include <event2/bufferevent.h>
bool readMsgPkg(struct bufferevent* bev,char* buf,MSGHEAD* msgHeadPtr);
void respondMsg(struct bufferevent* bev,int success,std::string _msg);
#endif


