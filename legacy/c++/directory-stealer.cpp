
using namespace std;

#include <iostream>
#include <fstream>

#include <dirent.h>
#include <string.h>
#include <sys/types.h>


int main() {
	DIR *dr;
	struct dirent* dent;
	dr = opendir("/");
	char buffer[1024];

	if (dr) {
		while ((dent = readdir(dr)) != NULL) {
			strcpy(buffer, dent->d_name);
			printf("%s\n", dent->d_name);
		}
		closedir(dr);
	}

	printf("%s\n", buffer);

	return 0;
}



