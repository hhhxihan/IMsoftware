#ifndef USERMODEL_HPP
#define USERMODEL_HPP
#include "../bo/user.hpp"
#include "../DBconnPool.hpp"
#ifndef MAXSIZE
#define MAXSIZE 
const int maxsize=1024;
#endif

class userModel{
    public:
        bool insert(user& _user);
        user query(int id);
        user query(string name);
        bool update(user& _user);

};
#endif