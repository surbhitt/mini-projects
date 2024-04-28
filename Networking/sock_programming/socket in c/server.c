// server side
#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

// contains the htons function
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char** argv) {

	// create scoket info structure
	struct sockaddr_in server_info = {0};
	server_info.sin_family = AF_INET;
	server_info.sin_port = htons(1337);  // the htons function is used to convert the decimal value of port to a suitable format
	socklen_t server_info_len = sizeof(server_info);

	struct sockaddr client_info = {0};
	socklen_t client_info_len = sizeof(client_info);

	// create socket
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > sfd) {
		perror("socket error");
		return -1;
	}

	// bind
	// we have to type case server_info from sockadd_in to sockaddr structure	
	if (0 > bind(sfd, (struct sockaddr*)&server_info, server_info_len)) {
		perror("bind error");
		return -1;
	}
	// listen
	if (0 > listen(sfd, 0)) {
		perror("listen error");
		return -1;
	}

	// accept
	int cfd = accept(sfd, &client_info, &client_info_len);
	if (0 > cfd) {
		perror("accept error");
		return -1;
	}

	char* hello = "test message";
	ssize_t sent = send(cfd, (void*)hello, strlen(hello), 0);
	close(cfd);
	
}
