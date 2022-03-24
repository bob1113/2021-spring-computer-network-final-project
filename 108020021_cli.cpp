#include<iostream>
#include<Winsock2.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>
// #define ServerIP "127.0.0.1"
// #define ServerPortNumber 5555

char ServerIP[1024];
int ServerPortNumber;

int main(int argc, char *argv[]){
    if(argc == 3){
        strcpy(ServerIP, argv[1]);
        ServerPortNumber = atoi(argv[2]);
    }else{
        strcpy(ServerIP, "127.0.0.1");
        ServerPortNumber = 5555;
    }

    /* initialize winsock */
    WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	struct sockaddr_in serverAddress;
	int server_addr_length = sizeof(serverAddress);
	int serverSocket;

    serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if(serverSocket < 0){
		fprintf(stderr, "Error creating socket : %s\n", strerror(errno));
		exit(0);
	}

    serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(ServerPortNumber);
	serverAddress.sin_addr.s_addr = inet_addr(ServerIP);

    /* connect to server */
	if(connect(serverSocket, (struct sockaddr *)&serverAddress, server_addr_length) == -1){
		fprintf(stderr, "connect failed : %s\n", strerror(errno));
		closesocket(serverSocket);
		exit(1);
	}

    char sendBuff[1024], recvBuff[1024];

    recv(serverSocket, recvBuff, sizeof(recvBuff) - 1, 0);
    printf("%s",recvBuff);
	while(1){
        memset(sendBuff,'\0',sizeof(sendBuff));
		gets(sendBuff);
        send(serverSocket, sendBuff, sizeof(sendBuff)-1, 0);

        memset(recvBuff,'\0',sizeof(recvBuff));
		recv(serverSocket, recvBuff, sizeof(recvBuff)-1, 0);
		printf("%s", recvBuff);
	}
}
