#include "cmdPars.hpp"

void User::topicCmd(Server& server, std::vector<std::string> channels_string) {
    std::string nameServer = HOST;
    nameServer.insert(0, ":");
    std::string sendMessage;
    if (channels_string.empty())
    {
        sendMessage = nameServer + " 461 "+ this->_nickname +" TOPIC" + " :Pas assez de parametres ptn [#channel] optionnel: :NewTopic";
        send(this->getUserFd(),sendMessage.c_str(), sendMessage.size(), 0); //ERR_NEEDMOREPARAMS 
        return;
    }
    Channel *channel = server.findChannel(channels_string[0]);
    if (channel == NULL)
    {
        sendMessage = nameServer + "403 "+ this->_nickname + " " + channel->getName() + " Moi pas te comprendre pas channel trouvé encule";
        send(this->getUserFd(),sendMessage.c_str(), sendMessage.size(), 0); //ERR_NOSUCHCHANNEL (403)
        return;
    }
    /*
    faire la condition si lutilisatuer ne se trouve pas dans le channel 
        ERR_NOTONCHANNEL (442) 
        "<client> <channel> :You're not on that channel"
            Returned when a client tries to perform a channel-affecting command on a channel which the client isn’t a part of.
    
        verifier si il veut l'afficher ou bien le modifier 
        si afficher alors plus d'autres args 
            RPL_TOPIC (332) 
            "<client> <channel> :<topic>"
            Sent to a client when joining the <channel> to inform them of the current topic of the channel.
            ou bien si topic vide 
            RPL_NOTOPIC (331) 
            "<client> <channel> :No topic is set"
            Sent as a reply to the TOPIC command to inform the client that the channel with the name <channel> does not have any topic set.

        sinon modifier (supprimer le :)
            verifier si il n'y a pas de restrictions sur le channel
                si oui et qu'il nest pas admin du channel
                    ERR_CHANOPRIVSNEEDED (482) 
                      "<client> <channel> :You're not channel operator"
                    Indicates that a command failed because the client does not have the appropriate channel 
                    privileges. This numeric can apply for different prefixes such as halfop, operator, 
                    etc. The text used in the last param of this message may vary.
                SI oui et qu'il est admin du channel 
                    RPL_TOPICWHOTIME (333) 
                    "<client> <channel> <nick> <setat>"
                    
                    Sent to a client to let them know who set the topic (<nick>) and when they set it (<setat> is a unix timestamp). Sent after RPL_TOPIC (332).
                si non pas de restictions pareil que ce qui est juste au dessus

                et pour les autres clients 
                    :<source> TOPIC <channel> :<new_topic>\r\n

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    */












    // if (this->checkUser(user) == true) {
	// if (this->checkUserAdmin(user) == true) {
	//     // TODO: faire le message a envoyer au channel pour modifier le
	//     // channel;
	//     // TODO: faire le message a envoyer au client pour confirmer que le
	//     // channel a ete modifie
	// } else {
	//     if (this->_topicRestrictions == true) {
	// 	for (int i = 0; this->_users.size() > i; i++) {
	// 	    // TODO: faire le message a envoyer au channel pour modifier
	// 	    // le channel;
	// 	}
	//     } else {
	// 	// TODO: faire le message pour dire a l'utilisateur qu'il ne
	// 	// peut pas modifier le topic
	//     }
	// }
    // } else {
	// // ne rien faire
    // }
}