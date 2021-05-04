#include <iostream>
#include <fstream>

#include <dirent.h>
#include <string.h>
#include <sys/types.h>


int main() {
	DIR *dr;
	struct dirent* dent;
	dr = opendir("/");
	char *buffer[1024];

	//std::fstream myfile;
	//myfile.open("example.txt");

	if (dr) {
		while ((dent = readdir(dr)) != NULL) {
			//myfile << dent->d_name << "\n";
		}
		closedir(dr);
	}
	
	//myfile.close();

	return 0;
}