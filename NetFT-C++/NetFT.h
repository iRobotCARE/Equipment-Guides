#pragma once
#ifndef NETFT_H
#define NETFT_H

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#endif

#include <string>
#include <stdexcept>

#define PORT 49152 /* Port the Net F/T always uses */
#define COMMAND 2 /* Command code 2 starts streaming */
#define NUM_SAMPLES 1 /* Will send 1 sample before stopping */

typedef unsigned int uint32;
typedef int int32;
typedef unsigned short uint16;
typedef short int16;
typedef unsigned char byte;

typedef struct response_struct {
	uint32 rdt_sequence;
	uint32 ft_sequence;
	uint32 status;
	int32 FTData[6];
} RESPONSE;

class NetFT {
public:
	NetFT(const std::string& ip_address);
	~NetFT();
	int communicate(RESPONSE& resp);

private:
	std::string ip_address;
	int socketHandle;
	struct sockaddr_in addr;
	struct addrinfo* addrInfo;

	void initSocket();
	void closeSocket();
};

#endif // NETFT_H
