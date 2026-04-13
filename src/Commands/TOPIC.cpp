/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pololinux <pololinux@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 17:47:34 by pololinux         #+#    #+#             */
/*   Updated: 2026/04/13 17:47:47 by pololinux        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void Channel::topic(User &user, std::string topic) {
    if (this->checkUser(user) == true) {
	if (this->checkUserAdmin(user) == true) {
	    // TODO: faire le message a envoyer au channel pour modifier le
	    // channel;
	    // TODO: faire le message a envoyer au client pour confirmer que le
	    // channel a ete modifie
	} else {
	    if (this->_topicRestrictions == true) {
		for (int i = 0; this->_users.size() > i; i++) {
		    // TODO: faire le message a envoyer au channel pour modifier
		    // le channel;
		}
	    } else {
		// TODO: faire le message pour dire a l'utilisateur qu'il ne
		// peut pas modifier le topic
	    }
	}
    } else {
	// ne rien faire
    }
}