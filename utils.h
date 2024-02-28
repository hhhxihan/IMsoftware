#ifndef UTILS_H
#define UTILS_H
#include "msgFormat.h"

#include <event2/bufferevent.h>
bool readMsgPkg(struct bufferevent* bev,char* buf,MSGHEAD* msgHeadPtr);
#endif


