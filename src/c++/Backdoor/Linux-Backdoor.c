#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

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

	s.sin_port = htons(argc == 2 ? argc : 1337), s.sin_addr.s_addr = INADDR_ANY, s.sin_family = AF_INET;
	if (argc = socket(AF_INET,SOCK_DGRAM,0) == -1) error("socket");

	if (bind(argc, (struct sockaddr *) &s,sizeof(s)) == -1) error("bind");

	dup2(argc, 1);
	dup2(argc, 2);

	s.sin_port = sizeof(u);


}
