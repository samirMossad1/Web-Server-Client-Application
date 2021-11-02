
/**********************************************************************************/
/*****************************INCLUDES*********************************************/
/**********************************************************************************/

#include "socket.h"
#include <stdio.h>



/**********************************************************************************/
/*****************************Functions Prototypes*********************************/
/**********************************************************************************/


/*Function which converts string number to integer number*/
int numStrToNumInt(char* string);


/**********************************************************************************/
/*****************************Global Data Buffers**********************************/
/**********************************************************************************/


/*Character array to hold the response (Data received)*/
char response[4096];
/*Character array to hole the GET request over the HTTP version 1.1 used application protocol*/
char request[]="GET / HTTP/1.1\r\n\n";



/**********************************************************************************/
/*****************************Main Function****************************************/
/**********************************************************************************/


/*Main entry*/
int main(int argc, char* argv[])
{	

	/*Define a socket configuration structure*/
	SocketConfig_s socketConfigInitStruct =
	{
		.localSocketAddr=
		{
			.domainFamily = IP_V4,	/*IP version 4 internet protocols family*/
		},
		.remoteSocketAddr=
		{
			.domainFamily = IP_V4,						/*IP version 4 internet protocols family*/
			.ipAddr = ipV4Str(argv[1]),					/*Set the IP of the web server from the second main function CLI string value*/
			.portNumber = (numStrToNumInt(argv[2]))		/*Set the port number of the web server from the third main function CLI string value*/
		},
		.tpType = TCP,			/*TCP socket*/
		.socketType = CLIENT	/*Client socket*/

	};


	/*Declare an error status*/
	errorReturn errorStatus;

	/*Create a new web local socket*/
	errorStatus = createSocket(&socketConfigInitStruct);

	/*Send the request to the remote web server*/
	errorStatus = sendData_tcp(socketConfigInitStruct.socketId,request,(SocketBufferLen_t)(sizeof(request)));

	/*Receive the response from the remote web server*/
	errorStatus = readData_tcp(socketConfigInitStruct.socketId,response,(SocketBufferLen_t)(sizeof(response)));

	/*Display the response*/
	printf("\nFrom Server:%s\n",response);

	/*Close the pre-opened socket*/
    closeSocket(socketConfigInitStruct.socketId);

	return 0;
}



/**********************************************************************************/
/*****************************Function Defs****************************************/
/**********************************************************************************/


/*Function which converts string number to integer number*/
int numStrToNumInt(char* string)
{	
	/*Define character pointer references the first element of the string*/
	char* tempPtr = string;
	int equivalentNumber=0 , numberBase=1;

	/*Normalize the asci chars and calculate the base number*/
	while( (*tempPtr) != '\0')
	{	
		numberBase *= 10;
		(*tempPtr) = (*tempPtr) - 48;
		tempPtr++;
	}

	numberBase /= 10;
	
	/*Converts the string number value to the integer number value*/
	while( (*string) != '\0')
	{

		equivalentNumber += (*string) * numberBase;
		numberBase /= 10;
		string++;
	}

	/*Return the equivalent integer number*/
	return equivalentNumber;


}

