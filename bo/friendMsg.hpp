
class friendMsg{
    public:
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
        int userID;
        int friendID;
        int state; 
};