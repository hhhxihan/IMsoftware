#ifndef REDIS_H
#define REDIS_H

#include <hiredis.h>
#include <string>
using namespace std;

class Redis{
    public:
    void subscribe(int channel);
    void publish(int channel,string msg);
    void unsubscrite(int channel);
    void init(char ip[]="127.0.0.1",int port=6379);
    ~Redis();

    private:
    redisContext* context;
}

#endif