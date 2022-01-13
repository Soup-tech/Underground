/*
	Maximillian Campbell
	May 3rd, 2021
	Computer Science 350 Section 001
	Homework #3: Random Numbers Problem
	Compiler: GCC v9.3.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>

// Client struct which would hold the random number and the process id
struct client_struct {
	int c_random_num;
	int c_pid;
};

// Server struct which would hold the random number and process id sent by the child
struct r_data {
	int r_number;
	int r_pid;
};

char ip_address[] = "127.0.0.1";
unsigned short server_port = 1867;

void server();
void client();

int main() {
	int i;

	pid_t client_1 = fork();
	pid_t client_2 = fork();

	if (client_1 > 0 && client_2 > 0) { // Parent
		server();
	} else { // Children
		client();
	}

	return 0;
}

/*
	Client sends 10 random integers to the server along with their process id
*/
void client() {
	sleep(5);

	int sockfd, i;
	struct sockaddr_in host_addr;
	srand(time(NULL));
	
	// Creating Socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		puts("Client Error: Could not get socketfd");
		exit(1);
	} else {
		puts("Client: Created Socket");
	}

	// Setting up sockaddr_in structure for client
	memset(&host_addr, 0, sizeof(host_addr));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(server_port);
	inet_aton(ip_address, &(host_addr.sin_addr));

	// Connecting client to host
	if ((connect(sockfd, (struct sockaddr *) & host_addr, sizeof(host_addr))) == -1) {
		puts("Client Error: Could not connect to host");
		exit(1);
	} else {
		puts("Client: Connected to Host");
	}

	// Writing to host
	for (i = 0 ; i < 10 ; i++) {
		// Creating struct and filling with info
		struct client_struct *myClient = malloc(sizeof(struct client_struct));
		myClient->c_pid = getpid();
		myClient->c_random_num = rand();
		sleep(1);
		if (write(sockfd, myClient, sizeof(struct client_struct)) == -1) {
			puts("Client Error: Could not Write to Host");
			exit(1);
		} else {
			//printf("Client: Wrote random number %d and pid %d\n", myClient->c_random_num, myClient->c_pid); Used this line for debugging purposes
		}
	}

	close(sockfd);
}


/*
	Server accepts connections from clients and prints out received information.
	Everytime the server accepts a new connection, it will fork the process to handle 
*/
void server() {
	int sockfd, new_sockfd, recv_length;
	struct sockaddr_in host_addr, client_addr;
	socklen_t sin_size;


	// Creating socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		puts("Server Error: Could not get sockfd");
		exit(1);
	} else {
		puts("Server: Created Socket");
	}

	// Setting up sockaddr_in information for host
	memset(&host_addr, 0, sizeof(host_addr));
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(server_port);
	inet_aton(ip_address, &(host_addr.sin_addr));

	// Binding Socket to port
	if (bind(sockfd, (struct sockaddr *) &host_addr, sizeof(host_addr)) == -1) {
		puts("Server Error: Could not bind socket");
		exit(1);
	} else {
		puts("Server: Bound Socket");
	}

	// Set socket to listen for incoming traffic
	if (listen(sockfd, 3) == -1) {
		puts("Server Error: Socket could not listen");
		exit(1);
	} else {
		puts("Server: Listening...");
	}

	// Socket is actively listening
	while (1) { // Listening loop

		sin_size = sizeof(struct sockaddr_in);
		new_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &sin_size); // Socket accepted a connection. Creating sockaddr_in struct for sclient

		if (new_sockfd == -1) {
			puts("Server Error: Could not accept connection");
			exit(1);
		} else {
			pid_t pid = fork();

			if (pid == 0) { // Servicing the connection through the child
				printf("Server: Connected from %s port %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
				struct r_data *received_data = malloc(sizeof(struct r_data));

				// Receiving and printing transmitted message
				recv_length = recv(new_sockfd, received_data, sizeof(struct r_data), 0);
				if ( recv_length > 0) {
					while (recv_length > 0) {
						printf("Server: PID %d received value %d from Client PID %d\n", getpid(), received_data->r_number, received_data->r_pid);
						recv_length = recv(new_sockfd, received_data, sizeof(struct r_data), 0);
					}		
					puts("Server: End of Transmission");
				} else {
					puts("Server: Contents of Message were Empty");
				}

			}
		}
	}
	puts("Sever: Closed Connection");
	close(new_sockfd);
}

