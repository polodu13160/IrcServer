#include "Bot.hpp"

const char *Bot::errorBadFile::what() const throw() {
	return "Error\nBad file provided.";
}

const char *Bot::errorConnect::what() const throw() {
	return "Error\nConnect function crash.";
}

const char *Bot::errorSend::what() const throw() {
	return "Error\nSend function crash.";
}

const char *Bot::errorSocket::what() const throw() {
	return "Error\nSocket function crash.";
}
