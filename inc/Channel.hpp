/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/15 18:07:57 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "string"
#include "map"
#include "User.hpp"
#include <set>

class User;

class Channel
{
public:
    Channel(std::string name, std::string password);
    Channel(const Channel &other);
    ~Channel();
    // void kick(User &user, User &userKick);
    // void invite(User &user,User &userInvite );
    // void topic(User &user, std::string topic);
    // void mode(char type, User &user);
    // void join(User &user, std::string password = "");

    const std::string &getName(void) const;
    const std::string &getPassword(void) const;
    const std::string &getTopic(void) const;
    bool getInviteOnly(void) const;
    bool getTopicRestrictions(void) const;
    unsigned int getUserLimit() const;
    bool checkPassword(std::string &password) const;
    bool checkUser(User &user) const;
    bool checkUserAdmin(User &user) const;
    const std::map<User *, bool> &getUsers() const;

    void setInviteOnly(bool val);
    void setName(std::string name);
    void setPassword(std::string name);
    void setUserLimit(unsigned int val);
    void addUser(User &user, bool admin);
    void addUserInvite(User &user);
    
    


private:
    std::string _name;
    Channel();
    Channel &operator=(const Channel &other);
    bool _inviteOnly;
    bool _topicRestrictions;
    std::string _password;
    unsigned int _userLimit;
    std::string _topic;
    std::map<User *, bool> _users;
    std::set<User *> _usersInvite;
};

#endif // _CHANNEL_H
