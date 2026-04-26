#ifndef CHANNEL_HPP
#define CHANNEL_HPP

#include <map>
#include <set>
#include <string>
#include <vector>
#include "User.hpp"

class User;

class Channel
{
public:
    Channel(const std::string& name);
    Channel(const Channel &other);
    ~Channel();

    bool                          getInviteOnly() const;
    bool                          getTopicRestrictions() const;
    bool                          checkPassword(const std::string &password) const;
    bool                          checkUser(User &user) const;
    bool                          getInInviteUsers(const std::string& user);
    bool                          checkUserAdmin(User &user) const;
    const std::map<User *, bool> &getUsers() const;
    const std::string            &getName() const;
    const std::string            &getPassword() const;
    const std::string            &getTopic() const;
    std::string             getNickNameModifTopicLast() const;
    std::string             getTimeUnixModifTopicLast() const;
    unsigned int                  getUserLimit() const;

    void         setInviteOnly(bool val);
    void         setName(const std::string& name);
    void         setNickNameModifTopicLast(std::string &lastNickName);
    void         setPassword(const std::string& name);
    void         setTimeUnixModifTopicLast(const std::string &time_val);
    void         setTopic(const char *val);
    void         setUserLimit(unsigned int val);
    void         addInviteUser(const std::string& user);
    void         addUser(User &user, bool admin);
    void         changeUserOp(User &user, bool sign);
    void         deletedUser(User &user);
    void         printChannelOperator();
    void         sendMsgUserForOthersUsersChannel(User &user, std::string &msg) const;
    std::vector<User *> allUsersInVector() const;
    User        *getUserByNickname(const std::string &nickname);

    unsigned int _modeStock;

private:
    Channel();
    Channel &operator=(const Channel &other);

    bool         _inviteOnly;
    bool         _topicRestrictions;
    unsigned int _userLimit;
    std::string  _name;
    std::string  _password;
    std::string  _topic;
    std::string  _nickNameLastModifTopic;
    std::string  _lastTimeUnixModifTopic;

    std::map<User *, bool> _users;
    std::set<std::string>  _usersInvite;
};

#endif