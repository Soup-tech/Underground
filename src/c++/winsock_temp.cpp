#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // Winsock library

int main(int argc, char *argv[]) {
	SOCKET s;
	WSADATA wsa;
	struct sockaddr_in server;
	char *message;

	puts("Initilizing Winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) { // WSAStartup initializes the winsock library. Takes 2 parameters. Version and WSADATA which holds additional information
		printf("Failed. Error Code : %d\n", WSAGetLastError());
		exit(1);
	}

	puts("Creating Socket...");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == INVALID_SOCKET) {
		printf("Error: Could not create socket %d\n", WSAGetLastError());
		exit(1);
	}
	puts("Socket Created");

	memset(&server, 0, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(8080);
	inet_aton("127.0.0.1", &(server.sin_addr));

	puts("Connecting...");
	if (connect(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
		puts("Error: Could not connect");
		exit(1);
	}

	message = "GET / HTTP/1.1\r\n\r\n";
	if (send(s, message, strlen(message), 0) < 0) {
		puts("Error: Could not send message");
		exit(1);
	}

	return 0;
}