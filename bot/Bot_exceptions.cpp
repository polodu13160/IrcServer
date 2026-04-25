#include "Bot.hpp"

const char *Bot::errorBadFile::what() const throw() {
	return "Error\nOpen Error.";
}

const char *Bot::errorConnect::what() const throw() {
	return "Error\nConnect function error.";
}

const char *Bot::errorSend::what() const throw() {
	return "Error\nSend function error.";
}

const char *Bot::errorSocket::what() const throw() {
	return "Error\nSocket function error.";
}
