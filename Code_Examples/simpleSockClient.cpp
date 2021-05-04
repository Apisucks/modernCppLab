#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[]){
	if (argc < 3){
		cout << "inputs not provided..\nPlease provide ip and host to connect to\n";
		return -1;
	}

	int port = atoi(argv[2]);
	int cliSock;
	cliSock = socket(AF_INET, SOCK_STREAM, 0);
	if (cliSock < 0){
		cout << "Failed to create socket for the client\n";
		return -1;
	}

	struct sockaddr_in servAddr;
	servAddr.sin_port = htons(port);
	servAddr.sin_family = AF_INET;
	//servAddr.sin_addr.s_addr = INADDR_ANY;

	if (inet_pton(AF_INET, argv[1], &servAddr.sin_addr) <= 0){
		cout << "Invalid address provided as input\n";
		return -1;
	}

	if (connect(cliSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0){
		cout << "Failed to connect to the server\n";
		return -1;
	}

	while(1){
		char buff[256];
		memset(buff, '\0', 256);
		fgets(buff, 256, stdin);
		int n = write(cliSock, buff, 256);
		if (n <= 0){
			cout << "Failed to write to the socket\n";
			return -1;
		}
		if (strncmp(buff, "bye", 3) == 0 || strncmp(buff, "BYE", 3) == 0 || strncmp(buff, "Bye", 3) == 0){
			break;
		}
	}
	close(cliSock);

	return 0;
}
