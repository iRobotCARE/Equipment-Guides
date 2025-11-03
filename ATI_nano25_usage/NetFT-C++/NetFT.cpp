#include "NetFT.h"
#include <stdexcept>
#include <cstring>

#ifdef _WIN32
WSADATA wsaData;
#define close closesocket
#endif

NetFT::NetFT(const std::string& ip_address) : ip_address(ip_address), addrInfo(nullptr) {
#ifdef _WIN32
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		throw std::runtime_error("WSAStartup failed");
	}
#endif
	initSocket();
}

NetFT::~NetFT() {
	closeSocket();
#ifdef _WIN32
	WSACleanup();
#endif
}

void NetFT::initSocket() {
	socketHandle = socket(AF_INET, SOCK_DGRAM, 0);
	if (socketHandle == -1) {
		throw std::runtime_error("Failed to create socket");
	}

	struct addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;

	int result = getaddrinfo(ip_address.c_str(), nullptr, &hints, &addrInfo);
	if (result != 0 || addrInfo == nullptr) {
		close(socketHandle);
		throw std::runtime_error("Failed to get address info");
	}

	struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)addrInfo->ai_addr;
	std::memcpy(&addr.sin_addr, &sockaddr_ipv4->sin_addr, sizeof(sockaddr_ipv4->sin_addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);

	int err = connect(socketHandle, (struct sockaddr*)&addr, sizeof(addr));
	if (err == -1) {
		close(socketHandle);
		throw std::runtime_error("Failed to connect to the socket");
	}
}

void NetFT::closeSocket() {
	if (addrInfo != nullptr) {
		freeaddrinfo(addrInfo);
		addrInfo = nullptr;
	}
	close(socketHandle);
}

int NetFT::communicate(RESPONSE& resp) {
	byte request[8];
	byte response[36];
	int i;

	*(uint16*)&request[0] = htons(0x1234); /* standard header. */
	*(uint16*)&request[2] = htons(COMMAND); /* per table 9.1 in Net F/T user manual. */
	*(uint32*)&request[4] = htonl(NUM_SAMPLES); /* see section 9.1 in Net F/T user manual. */

	send(socketHandle, reinterpret_cast<const char*>(request), 8, 0);

	recv(socketHandle, reinterpret_cast<char*>(response), 36, 0);
	resp.rdt_sequence = ntohl(*(uint32*)&response[0]);
	resp.ft_sequence = ntohl(*(uint32*)&response[4]);
	resp.status = ntohl(*(uint32*)&response[8]);
	for (i = 0; i < 6; i++) {
		resp.FTData[i] = ntohl(*(int32*)&response[12 + i * 4]);
	}

	return 0;
}
