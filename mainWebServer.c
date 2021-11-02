

/**********************************************************************************/
/*****************************INCLUDES*********************************************/
/**********************************************************************************/

#include "socket.h"
#include <stdio.h>
#include <string.h>



/**********************************************************************************/
/*****************************Global Data Buffers**********************************/
/**********************************************************************************/



/*Character array to hold the response to the client (Index file)*/
char responseIndexPage[100];

/*Character array to hold the response and the http header application protocol version 1.1 with (200 OK) status*/
char httpHeader[100]="HTTP/1.1 200 OK\r\n\n";



/**********************************************************************************/
/*****************************Main Function*******************************************/
/**********************************************************************************/


/*Main entry*/
int main(void)
{
	/*Declare a file handle*/
	FILE* indexPageReference;

	/*Define a socket configuration structure*/
	SocketConfig_s socketConfigInitStruct =
	{
		.localSocketAddr=
		{
			.ipAddr = ipV4Int(INADDR_ANY),	/*Receive from any IP address*/
			.domainFamily = IP_V4,			/*IP version 4 internet protocols family*/
			.portNumber = (8080U)			/*Set the port number to any chosen value*/
		},
		.tpType = TCP,						/*TCP socket*/
		.socketType = SERVER 				/*Server socket*/

	};

	/*Declare an error status*/
	errorReturn errorStatus;

	/*Open the index file*/
	indexPageReference = fopen("index.html","r");

	/*Load the index file into the response character array*/
	fgets(responseIndexPage,sizeof(responseIndexPage),indexPageReference);	
	/*Concatenate the http header to the index file data to form the complete server response*/
	strcat(httpHeader,responseIndexPage);

	/*Create a new web local socket*/
	errorStatus = createSocket(&socketConfigInitStruct);
	
	/*Send the response to the remote web client*/
	errorStatus = sendData_tcp(socketConfigInitStruct.connectedTcpSocketId,httpHeader,(SocketBufferLen_t)(sizeof(httpHeader)));
	
	/*Close the connected pre-opened socket*/
	errorStatus = closeSocket(socketConfigInitStruct.connectedTcpSocketId);
	
	/*Close the main listening socket*/
	errorStatus = closeSocket(socketConfigInitStruct.socketId);
	

	return 0;
}


