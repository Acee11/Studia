// Wojciech Balik
// 280254

#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <fstream>  
#include <exception>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include "HttpMsg.h"
#include "utils.h"

#define _DEBUG_MESSAGES_ 1

class ClientHandler
{
private:
	int sockfd;
	int inactiveTimeout;
	std::string catalog;

	void closeConnection();
	HttpMsg getHttpRequest();
	HttpMsg getHttpResponse(const HttpMsg& httpRequest);
	void sendMsg(const HttpMsg& msg);

	HttpMsg getErrorHtml(int errNumber) const;

public:
	ClientHandler(int sockfd, int inactiveTimeout, const std::string& catalog) :
	sockfd(sockfd),
	inactiveTimeout(inactiveTimeout),
	catalog(catalog)
	{ }
	
	void run();
};

#endif