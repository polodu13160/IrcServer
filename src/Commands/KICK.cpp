/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:45:26 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/13 17:47:05 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "User.hpp"

void User::kick(User &user, User &userKick) {
    if (this->checkUser(user) == true) {
	if (this->checkUserAdmin(user) == true) {
	    if (this->checkUser(userKick) == true) {
		// TODO: faire le message a envoyer a luser kick
		for (int i = 0; this->_users.size() > i; i++) {
		    // TODO: faire le message a envoyer a tout les utilisateurs
		    // qu'il a ete kick par user;
		}
	    } else {
		// TODO: faire le message a envoyer a l'utilisateur qu'il ne
		// peut pas kick car utilisateur n'est pas trouvé;
	    }
	} else {
	    // TODO faire un message a envoyer a l'utilisateur pour dire qu'il
	    // n'a pas les droits
	}
    } else {
	// Ne rien faire
    }
}
