#include <event.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define SERVER_PORT 8888

int main() {

	int socklisten;
	struct sockaddr_in addresslisten;
	int reuse;

	socklisten = socket(AF_INET, SOCK_STREAM, 0);

	if(socklisten < 0) {
		fprintf(stderr, "Failed to create listen socket\n");
		return 1;
	}

	memset(&addresslisten, 0, sizeof(addresslisten));

	addresslisten.sin_family = AF_INET;
	addresslisten.sin_addr.s_addr = INADDR_ANY;
	addresslisten.sin_port = htons(SERVER_PORT);

	if(bind(socklisten, (struct sockaddr *) &addresslisten, sizeof(addresslisten)) < 0) {
		fprintf(stderr, "Failed to bind\n");
		return 2;
	}

	if(listen(socklisten, 100) < 0) {
		fprintf(stderr, "Failed to listen to socket\n");
		return 3;
	}

	event_init();

	setsockopt(
		socklisten,
		SOL_SOCKET,
		SO_REUSEADDR,
		&reuse,
		sizeof(reuse));

	return 0;
}
