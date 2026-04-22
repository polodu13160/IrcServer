/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pde-petr <pde-petr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/22 17:31:44 by pde-petr         ###   ########.fr       */
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
	Channel(std::string name);
    Channel(const Channel &other);
    ~Channel();
    const std::string &getName(void) const;
    const std::string &getPassword(void) const;
    const std::string &getTopic(void) const;
    bool getInviteOnly(void) const;
    bool getTopicRestrictions(void) const;
    unsigned int getUserLimit() const;
    bool checkPassword(std::string &password) const;
    bool checkUser(User &user) const;
    bool checkUserAdmin(User &user) const;
	void	changeUserOp(User &user, bool sign);
    const std::map<User *, bool> &getUsers() const;
    void addInviteUser(std::string user);
    bool getInInviteUsers(std::string user);

    void setInviteOnly(bool val);
    void setName(std::string name);
    void setPassword(std::string name);
    void setUserLimit(unsigned int val);
    void setTopic(const char *val);
    void addUser(User &user, bool admin);
    void deletedUser(User &user);
    const std::vector<User *> allUsersInVector() const;
    void sendMsgUserForOthersUsersChannel(User &user, std::string &msg) const;
    const std::string getNickNameModifTopicLast() const;
    void setNickNameModifTopicLast(std::string &lastNickName);
    const std::string getTimeUnixModifTopicLast() const;
    void setTimeUnixModifTopicLast(const std::string &time_val) ;
	void	printChannelOperator();

	User *getUserByNickname(const std::string &nickname);

	unsigned int _modeStock	;


private:
	std::string _name;

	Channel();

	Channel &operator=(const Channel &other);

	unsigned int _userLimit;
	std::string _password;
	std::string _topic;
    std::string _nickNameLastModifTopic;
    std::string _lastTimeUnixModifTopic;
	std::map<User *, bool> _users;
	std::set<std::string> _usersInvite;

	//mode
	bool _inviteOnly;
	bool _topicRestrictions;
};

#endif // _CHANNEL_H
