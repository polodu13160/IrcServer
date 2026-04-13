/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MSG.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:47:50 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/13 17:49:04 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



void Channel::msg(User &user, std::string &text) {
    if (checkUser(user) == true) {
	for (int i = 0; this->_users.size() > i; i++) {
	    // TODO: faire le message a envoyer a tous les utilisateurs du
	    // channel
	}

    } else {
	// ne rien faire
    }
}





	void Channel::join(User & user, std::string _password) 
	{
		if (this->_usersInvite)
	}