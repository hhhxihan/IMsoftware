#ifndef FRIENDMODEL_HPP
#define FRIENDMODEL_HPP
#include "../bo/friendMsg.hpp"
#include <string>
#define MAXSIZE 1024
#include "../bo/user.hpp"
#include <vector>
using namespace std;
class friendModel{
    public:
    bool insert(friendMsg& _friendMsg);
    bool update(friendMsg& _friendMsg);
    vector<user> query(int _id);
};

#endif