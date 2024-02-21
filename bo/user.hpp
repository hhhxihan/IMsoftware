#ifndef USER_HPP
#define USER_HPP
#include <string>
using namespace std;

class user{
    public:

    void setId(const int &id) {  _userID = id; }
    void setName(const std::string &name) { _name = name; }
    void setPassword(const std::string &paw) { _password = paw; }
    void setState(int state) { _state = state; }

    int getId() { return _userID; }
    string getName() { return _name; } 
    string getPassword() { return _password; } 
    int getState() { return _state; } 
    
    protected:
    int _userID;
    string _password;
    string _name;
    int _state;
};

#endif