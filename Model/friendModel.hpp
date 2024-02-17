#ifndef FRIENDMODEL_HPP
#define FRIENDMODEL_HPP
#include "../bo/friendMsg.hpp"
#include <string>
#include "../bo/user.hpp"
#include <vector>
using namespace std;
class friendModel{
    public:
    bool update(string sql);
    vector<user> query(int _userID);
};

#endif