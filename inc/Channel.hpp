/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/04 19:24:05 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "User.hpp"
#include "map"
#include "set"
#include "string"

class Channel {
  public:
    Channel(std::string &name);
    ~Channel();
    void kick(User &user, User &userKick);
    void invite(User &user, User &userInvite);
    void topic(User &user, std::string topic);
    void msg(User &user, std::string &text);
    void join(User &user, std::string password = "");
    bool checkUser(User &user);
    bool checkUserAdmin(User &user);

    //mode :
    void setInviteOnly(char Sign); //i
    void setTopicRestictions(char Sign); //t
    void setChannelPassword(char Sign, std::string *password); //k
    void setOperator(char Sign, User &user); //o
    void setUserLimit(char Sign, size_t limits); //l

  protected:
  private:
    Channel(const Channel &other);
    Channel();
    Channel &operator=(const Channel &other);
    std::string _name;
    std::map<User *, bool> _users;
    std::set<User *> _usersInvite;
    bool _inviteOnly;
    bool _topicRestrictions;
    std::string _password;
    size_t _userLimit;
    static const std::string TYPEMODE;
};

#endif // _CHANNEL_H