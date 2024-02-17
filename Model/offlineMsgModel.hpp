#ifndef OFFLINEMSGMODEL_HPP
#define OFFLINEMSGMODEL_HPP
#include "../bo/offlineMsg.hpp"
#include <vector>
class offlineMsgModel{
    public:
    bool insert(offlineMsg& _msg);
    void deleteMsg(int _userID);
    std::vector<offlineMsg> query(int _userID);

};

#endif