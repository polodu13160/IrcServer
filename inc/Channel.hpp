/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 17:58:59 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/03 17:07:02 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _CHANNEL_H
# define _CHANNEL_H

#include "string"
#include "map"

class Channel
{
public:
    Channel(std::string &name, std::string password = "");
    ~Channel();
    void kick(User &user, User &userKick);
    void invite(User &user,User &userInvite );
    void topic(User &user, std::string topic);
    void mode(char type, User &user);
    void join(User &user, std::string password = "");  
    
protected:
private:
    Channel(const Channel& other);
    Channel();
    Channel& operator=(const Channel& other);
    std::string _name;
    std::map<User*, bool isOperateur> _users;
    bool _inviteOnly;
    bool _topicRestrictions;
    std::string _password;
    unsigned int _userLimit;
};



#endif // _CHANNEL_H