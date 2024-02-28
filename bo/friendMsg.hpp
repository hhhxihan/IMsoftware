#ifndef FRIENDMSG_HPP
#define FRIENDMSG_HPP
class friendMsg{

    public:
    int getID() const{ return id;}
    void setID(int _id){ id=_id;};
        // Getter for userID
    int getUserID() const {
        return userID;
    }

    // Setter for userID
    void setUserID(int newUserID) {
        userID = newUserID;
    }

    // Getter for friendID
    int getFriendID() const {
        return friendID;
    }

    // Setter for friendID
    void setFriendID(int newFriendID) {
        friendID = newFriendID;
    }

    // Getter for state
    int getState() const {
        return state;
    }

    // Setter for state
    void setState(int newState) {
        state = newState;
    }

    private:
        int id;
        int userID;
        int friendID;
        int state; 
};
#endif