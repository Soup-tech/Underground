#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") // winsock library

int main(int argc, char *argv[]) {
	
	WSADATA wsa;
	puts("Initialising Winsock...");
	if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
		puts("Failed to initialize Winsock. Error Code : %d\n", WSAGetLastError());
		exit(1);
	}
	puts("Socket initialized");


	return 0;
}
