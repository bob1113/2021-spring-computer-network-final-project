#include<iostream>
#include<Winsock2.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<errno.h>
// #define ServerPortnumber 5555

int ServerPortnumber;

int main(int argc, char *argv[]){
    if(argc == 2) ServerPortnumber = atoi(argv[1]);
    else ServerPortnumber = 5555;

    /* initialize winsock */
    WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	struct sockaddr_in serverAddress, clientAddress;
	int server_addr_length = sizeof(serverAddress);
    int client_addr_length = sizeof(clientAddress);
    int serverSocket, clientSocket;
    char maximum[1024], minimum[1024];
    char buf[1024], msg[1024];

	int guess_number;

	serverSocket = socket(PF_INET, SOCK_STREAM, 0);  // protocol family, TCP/UDP, 0: let system decide
    if(serverSocket < 0){
		fprintf(stderr, "Error creating socket : %s\n", strerror(errno));
		exit(0);
	}

    serverAddress.sin_family = AF_INET;
  	serverAddress.sin_port = htons(ServerPortnumber);
	serverAddress.sin_addr.s_addr = INADDR_ANY;

    if(bind(serverSocket,(struct sockaddr *) &serverAddress, server_addr_length) == -1){
		fprintf(stderr, "Error binding : %s\n", strerror(errno));
		closesocket(serverSocket);
		exit(1);
	}

	if(listen(serverSocket, 3) == -1){
		fprintf(stderr, "Error listening : %s\n", strerror(errno));
		closesocket(serverSocket);
		exit(2);
	}

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &client_addr_length);
    if(clientSocket == -1){
        fprintf(stderr, "Error creating socket : %s\n", strerror(errno));
        closesocket(clientSocket);
        exit(3);
    }

    while(1){
        /* send game start page */
        memset(msg, '\0', sizeof(msg));
        strcpy(msg, "--------------\nGame Start\n--------------\nGuess number:\n");
        send(clientSocket, msg, sizeof(msg)-1, 0);

        while(1){
            srand((unsigned int)(time(NULL)));
            int number = rand() % 1000;

            /* initialize max and min */
            strcpy(maximum, "999");
            strcpy(minimum, "0");

            /* start to guess */
            while(1){
                memset(buf, '\0', sizeof(buf));
                recv(clientSocket, buf, sizeof(buf)-1, 0);
                guess_number = atoi(buf);
                if(guess_number > number){
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "less than ");
                    strcat(msg, buf);
                    strcat(msg, "\nhigher than ");
                    strcat(msg, minimum);
                    strcat(msg, "\nGuess number:\n");
                    send(clientSocket, msg, sizeof(msg)-1, 0);
                    strcpy(maximum, buf);
                }else if(guess_number < number){
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "less than ");
                    strcat(msg, maximum);
                    strcat(msg, "\nhigher than ");
                    strcat(msg, buf);
                    strcat(msg, "\n");
                    strcat(msg, "Guess number:\n");
                    send(clientSocket, msg, sizeof(msg)-1, 0);
                    strcpy(minimum, buf);
                }else{
                    memset(msg, '\0', sizeof(msg));
                    strcpy(msg, "Answer Correct\n\n--------------\nnext round\n--------------\nGuess number:\n");
                    send(clientSocket, msg, sizeof(msg)-1, 0);
                    break;
                }
            }
        }
    }
	return 0;
}
