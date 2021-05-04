#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <cstdlib>
#include <unistd.h>

using namespace std;

int main(){

	int port = 8080;
	int servSock, cliSock;

	servSock = socket(AF_INET, SOCK_STREAM, 0);

	if (servSock < 0){
		cout << "Failed to create server socket\n";
		return -1;
	}

	struct sockaddr_in servAddr, cliAddr;
	servAddr.sin_port = htons(port);
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) < 0){
		cout << "Failed to bind the socket to the host address\n";
		return -1;	
	}
	
	listen(servSock, 3);

	socklen_t cliAddrLen;

	cliSock = accept(servSock, (struct sockaddr *) &cliAddr, &cliAddrLen);
	if (cliSock < 0){
		cout << "Failed to create socket for the incomming connection\n";
		return -1;
	}

	while(1){
		char buff[256];
		memset(buff, '\0', 256);
		int n = read(cliSock, buff, 256);
		if (n <= 0){
			cout << "Failed to read from the client\n";
			return -1;
		}

		if (strncmp(buff, "Bye", 3) == 0 || strncmp(buff, "BYE", 3) == 0 || strncmp(buff, "bye", 3) == 0){
			break;
		}

		cout << buff << endl;
	}

	close(cliSock);
	close(servSock);
	return 0;
}

