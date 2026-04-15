/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpaysant <lpaysant@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/12 18:07:11 by lpaysant         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHANNEL_H
# define _CHANNEL_H

#include "string"
#include "map"
#include "User.hpp"

class User;

class Channel
{
public:
    Channel(std::string name, std::string password);
	Channel(const Channel& other);
    ~Channel();
    void kick(User &user, User &userKick);
    void invite(User &user,User &userInvite );
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
    Channel& operator=(const Channel& other);
    bool _inviteOnly;
    bool _topicRestrictions;
    std::string _password;
    unsigned int _userLimit;
	unsigned int _channelMode;
};



#endif // _CHANNEL_H
