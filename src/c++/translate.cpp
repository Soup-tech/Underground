#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {

	int sockfd, new_sockfd, recv_length = 1;
	struct sockaddr_in serv_addr, client_addr;
	char buffer[1024];

	puts("Creating socket...");
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		puts("Error: Could not create socket");
		exit(1);
	}
	puts("Socket Created");

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(8080);
	inet_aton("127.0.0.1", &(serv_addr.sin_addr));

	puts("Binding Socket...");
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
		puts("Error: Could not bind socket");
		exit(1);
	}
	puts("Binded Socket");

	puts("Listening....");
	listen(sockfd, 3);

	while (1) {

		sin_size = sizeof(struct sockaddr_in);
		new_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size);
		if (new_sockfd == -1) {
			puts("Error: Could not accept connection");
			exit(1);
		}
		
		while (recv_length > 0) {
			printf("RECV: %D bytes\n", recv_length);
			dump(buffer, recv_length);
			recv_length = recv(new_sockfd, &buffer, 1024, 0);
		}
		close(new_sockfd);
	}

	return 0;
}

void dump(const unsigned char *data_buffer, const unsigned int length) {

	unsigned char byte;
	unsigned int i, j;
	for (i = 0 ; i < length ; i++) {
		byte = data_buffer
	}








}


