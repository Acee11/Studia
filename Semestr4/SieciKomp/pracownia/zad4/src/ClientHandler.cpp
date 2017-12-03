// Wojciech Balik
// 280254

#include "ClientHandler.h"

void ClientHandler::closeConnection()
{
	if(close(sockfd) < 0)
	{
		std::cerr << "Error: " << strerror(errno);
		throw new std::runtime_error("Closing connection exception");
	}
}

HttpMsg ClientHandler::getHttpRequest()
{

	constexpr size_t bufferSize = 4096;
	std::unique_ptr<char[]> buffer(new char[bufferSize]);
	size_t readBytesOverall = 0;
	while(readBytesOverall < bufferSize)
	{

		struct timeval tv;
		tv.tv_sec = inactiveTimeout; 
		tv.tv_usec = 0;
		fd_set descriptors;
		FD_ZERO(&descriptors);
		FD_SET(sockfd, &descriptors);

		int ready = select(sockfd+1, &descriptors, NULL, NULL, &tv);
		if(ready < 0)
		{
			std::cerr << "Error: " << strerror(errno);
			throw new std::runtime_error("Select exception");
		}
		else if(ready == 0)
			return HttpMsg();

		
		ssize_t readBytes = recv(
			sockfd, 
			&buffer.get()[readBytesOverall], 
			1, 
			0
		);
		if(readBytes < 0)
		{
			std::cerr << "Error: " << strerror(errno);
			throw new std::runtime_error("recv exception");
		}
		if(readBytes == 0)
		{
			return HttpMsg();
		}

		readBytesOverall += (size_t)readBytes;
		if(utils::endOfHttpMsg(buffer, readBytesOverall))
			return HttpMsg(buffer, readBytesOverall);
	}
	return HttpMsg();
}

HttpMsg ClientHandler::getHttpResponse(const HttpMsg& request)
{
	#if _DEBUG_MESSAGES_
	std::cout << "RECEIVED MESSAGE:\n" << request << '\n';
	#endif

	std::string response = "";
	const std::map<std::string, std::string>& header = request.getHeader();
	if(request.getHttpMethod() != HttpMsg::HttpMethod::GET)
		return getErrorHtml(501);
	else
	{
		bool redirectedToIndex = false;
		std::string hostName = header.at("Host");
		size_t portBegin = hostName.find_last_of(":");
		hostName = hostName.substr(0, portBegin);
		std::string path = catalog + "/" + hostName + header.at("what");
		
		if(utils::isCatalog(path))
		{
			redirectedToIndex = true;
			if(path.back() != '/')
				path += "/";
			path += "index.html";
		}
		if(!utils::isSafe(path))
		{
			std::cerr << "Path not safe\n";
			return getErrorHtml(403);
		}
		std::ifstream reqFile(path, std::ifstream::binary);
		if(!reqFile.is_open())
		{
			#if _DEBUG_MESSAGES_
			std::cerr << "File not found: " << path << "\n";
			#endif
			return getErrorHtml(404);
		}
		reqFile.seekg(0, reqFile.end);
		size_t fileLen = reqFile.tellg();
		reqFile.seekg(0, reqFile.beg);
		
		if(redirectedToIndex)
			response += "HTTP/1.1 301 MOVED PERMANENTLY\r\n";
		else
			response += "HTTP/1.1 200 OK\r\n";
		response += "Content-Type: " + utils::getMime(path) + "\r\n";
		response += "Content-Length: " + std::to_string(fileLen) + "\r\n";
		response += "Connection: keep-alive\r\n\r\n";

		size_t bufferSize = response.length() + fileLen;
		std::unique_ptr<char[]> buffer(new char[bufferSize]);
		std::memcpy(buffer.get(), response.c_str(), response.length());
		reqFile.read(&buffer.get()[response.length()], fileLen);
		reqFile.close();
		HttpMsg httpResponse(buffer, bufferSize);

		return httpResponse;

	}
}

void ClientHandler::sendMsg(const HttpMsg& msg)
{
	const std::map<std::string, std::string>& header = msg.getHeader();

	#if _DEBUG_MESSAGES_
	std::cout << "SENDING MESSAGE:\n" << msg << "\n";
	#endif

	if(header.at("method") != "RESPONSE")
	{
		std::cerr << "Msg is not an response\n";
		throw std::runtime_error("Response exception");
	}

	std::string res = "HTTP/1.1 " + 
		header.at("response-code") + 
		" " + 
		header.at("response-phrase") +
		"\r\n";

	for(const auto& it : header)
	{
		if(it.first == "method" || it.first == "response-code" || it.first == "response-phrase")
			continue;
		res += it.first + ": " + it.second + "\r\n";
	}


	res += "\r\n";
	size_t bufferSize = res.length();
	res += std::string(msg.getData().get(), msg.getDataSize());
	bufferSize += msg.getDataSize();
	size_t bytesSentOverall = 0;
	while(bytesSentOverall < bufferSize)
	{
		ssize_t bytesSent = send(
			sockfd, 
			res.c_str() + bytesSentOverall, 
			bufferSize - bytesSentOverall, 
			0
		);
		if(bytesSent < 0)
		{
			std::cerr << "Error: " << strerror(errno);
			throw std::runtime_error("Send exception");
		}
		bytesSentOverall += (size_t)bytesSent;
	}
}

void ClientHandler::run()
{
	while(true)
	{
		HttpMsg request = getHttpRequest();


		if(request.empty())
		{
			closeConnection();
			return;
		}
		HttpMsg response = getHttpResponse(request);
		sendMsg(response);

		std::string reqConnection;
		try
		{
			reqConnection = request.getHeader().at("connection");
		}
		catch(const std::out_of_range& e)
		{
			reqConnection = "keep-alive";
		}
		if(reqConnection == "close")
		{
			closeConnection();
			return;
		}
	}
}



HttpMsg ClientHandler::getErrorHtml(int errNumber) const
{
	std::string errString = std::to_string(errNumber);
	std::ifstream reqFile(
		catalog + "/_PRIVATE__/" + errString + ".html", 
		std::ifstream::binary
	);

	if(!reqFile.is_open())
	{
		std::cerr << "Error while opening \n" << errString << "\n";
		throw new std::runtime_error("opening " + errString + " exception");
	}
	reqFile.seekg(0, reqFile.end);
	size_t fileSize = reqFile.tellg();
	reqFile.seekg(0, reqFile.beg);

	std::string response = "";
	response += "HTTP/1.1 " + errString + " " + utils::getErrorPhrase(errNumber) + "\r\n";
	response += "Content-Type: text/html\r\n";
	response += "Content-Length: " + std::to_string(fileSize) + "\r\n";
	response += "Connection: keep-alive\r\n\r\n";
	size_t bufferSize = fileSize + response.length();
	std::unique_ptr<char[]> buffer(new char[bufferSize]);
	std::memcpy(buffer.get(), response.c_str(), response.length());
	reqFile.read(&buffer.get()[response.length()], fileSize);
	reqFile.close();
	HttpMsg httpResponse(buffer, bufferSize);
	return httpResponse;
}