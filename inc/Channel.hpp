/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/14 17:22:18 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "string"
#include "map"
#include "User.hpp"

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
    const bool getInviteOnly(void) const;
    const bool getTopicRestrictions(void) const;
    const unsigned int getUserLimit() const;
    const bool checkPassword(std::string &password) const;

    void setInviteOnly(bool val);
    void setName(std::string name);
    void setPassword(std::string name);
    void setUserLimit(unsigned int val);
    

    std::map<User *, bool> _users;

private:
    std::string _name;
    Channel();
    Channel &operator=(const Channel &other);
    bool _inviteOnly;
    bool _topicRestrictions;
    std::string _password;
    unsigned int _userLimit;
};

#endif // _CHANNEL_H
