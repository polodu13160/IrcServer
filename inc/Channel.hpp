/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/13 17:22:20 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHANNEL_H
#define _CHANNEL_H

#include "User.hpp"
#include "map"
#include "set"
#include "string"
#include "map"
#include "User.hpp"

class User;

class Channel
{
public:
    Channel(std::string &name);
    ~Channel();
    void kick(User &user, User &userKick);
    void invite(User &user, User &userInvite);
    void topic(User &user, std::string topic);
    void mode(char type, User &user);
    void join(User &user, std::string password = "");

	const std::string	&getName(void)const;
	const std::string	&getPassword(void)const;

	void				setName(std::string name);
	void				setPassword(std::string name);

    std::map<User*, bool> _users;

	private:
	std::string _name;
    Channel();
    Channel(const Channel& other);
    Channel& operator=(const Channel& other);
    bool _inviteOnly;
    bool _topicRestrictions;
    std::string _password;
    size_t _userLimit;
    static const std::string TYPEMODE;
};

#endif // _CHANNEL_H
