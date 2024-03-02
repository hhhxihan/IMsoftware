#ifndef USERMODEL_HPP
#define USERMODEL_HPP
#include "../bo/user.hpp"
#include "msgFormat.h"
#include <string>
#include "../DBconnPool.hpp"
#ifndef MAXSIZE
#define MAXSIZE 
const int maxsize=1024;
#endif

class userModel{
    public:
        bool insert(user& _user);
        bool queryIfLogged(int id);
        user query(string name);
        bool query(user& _user);
        bool update(user& _user);

};
#endif