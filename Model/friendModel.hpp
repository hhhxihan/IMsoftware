#ifndef FRIENDMODEL_HPP
#define FRIENDMODEL_HPP
#include "../bo/friendMsg.hpp"
#include <string>
#include "../bo/user.hpp"
#include <vector>

#ifndef MAXSIZE
#define MAXSIZE
const int maxsize=1024;
#endif

using namespace std;
class friendModel{
    public:
    bool insert(friendMsg& _friendMsg);
    bool update(friendMsg& _friendMsg);
    vector<user> query(int _id);
};

#endif

