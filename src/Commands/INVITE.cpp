/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:47:08 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/13 17:47:30 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void User::invite(User &user, User &userInvite) {
    if (this->checkUser(user) == true) {
	// utilsMessage::messageToClient(user.getUserFd(),NULL,user.getNickname(),&(this->_name),"KICK",NULL);
	// TODO: faire le message a envoyer au client pour confirmer linvit;
	// TODO: faire le message a envoyer au client inviter pour lui dire
	// qu'il a ete invite;
		this->_usersInvite.insert(&userInvite);
    } else {
	// ne rien faire
    }
}
