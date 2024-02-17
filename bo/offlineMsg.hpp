#ifndef OFFLINEMSG_HPP
#define OFFLINEMSG_HPP
#include <string>

class offlineMsg{
    public:
    int toID;
    int formID;
    int type;
    std::string Msg;

    int getToID() const { return toID; }
    void setToID(int _toID) { toID = _toID; }

    int getFromID() const { return fromID; }
    void setFromID(int _fromID) { fromID = _fromID; }

    int getType() const { return type; }
    void setType(int _type) { type = _type; }

    const char* getMsg()  { return Msg.c_str(); }
    void setMsg(const std::string& _Msg) { Msg = _Msg; }
};

#endif