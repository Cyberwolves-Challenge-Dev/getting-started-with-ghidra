#include <stdio.h>
#include <string.h>

int main() {
	char user_input[15];
	printf("Password: ");
	fgets(user_input, sizeof(user_input), stdin);
	if (strcmp(user_input, "CSU-INTR-9032\n") == 0) printf("Correct password!\n");
	else printf("Incorrect password\n");
	return 0;
}