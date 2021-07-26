#include <iostream>
#include <Windows.h>
#include <winsock.h>

using namespace std;

int main() {

	// socket is an existing but non-physical virtual interface.
	// The WSAStartup function initiates use of the Winsock DLL by a process.

	WSADATA WinSocketData;
	int iWsaStartup;
	int iWsaCleanup;

	SOCKET UDPServerSideSocket;
	struct sockaddr_in UDPatClientSide;

	char Buffer[512];
	int iBufferLength = strlen(Buffer) + 1;
	
	int iBindWithClient;
	int iReceiveFromClient;

	int iUDPatClientSideLength = sizeof(UDPatClientSide);
	int iCloseServerSideSocket;

	cout << "----------------------Server side-----------------------" << endl;

	// 1 WSAStartup initialization
	iWsaStartup = WSAStartup(MAKEWORD(2, 2), &WinSocketData); //version 2.2;

	if (iWsaStartup != 0) {
		cout << "WSA Startup Failed" << endl;
	}
	cout << "WSA Startup Succeeded" << endl;

	//2 UDP Client (socket address) structure filling


	// Def: AF_INET is an address FAMILY that is used to designate the type of addresses
	//that your socket can communicate with (in this case, Internet Protocol v4 addresses).

	UDPatClientSide.sin_family = AF_INET;
	UDPatClientSide.sin_addr.s_addr = inet_addr("127.0.0.1");
	UDPatClientSide.sin_port = 8000;
	
	// htons converts little endian to big endian format, and all the protocols run in big endian format
	// Little and big endian are two ways of storing multibyte data-types ( int, float, etc)


	//3 socket creation
	 
	UDPServerSideSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); // UDP (User Datagram Protocol) is a type of Datagram socket. 

	if (UDPServerSideSocket == INVALID_SOCKET) {

		cout << "Server side socket creation failed with : "<< WSAGetLastError() << endl;

	}

	cout << "Server side socket created successfully" << endl;

	//4 Binding Server with the Client address

	iBindWithClient = bind(UDPServerSideSocket, (SOCKADDR*)&UDPatClientSide, sizeof(UDPatClientSide));

	if (iBindWithClient == SOCKET_ERROR) {
		cout << "Server binding failed with : " << WSAGetLastError() << endl;
	}

	cout << "Server binding successful" << endl;


	//5 receive data from client

	iReceiveFromClient = recvfrom(UDPServerSideSocket, Buffer, iBufferLength, MSG_PEEK, (SOCKADDR*)&UDPatClientSide, &iUDPatClientSideLength);
	
	//MSG_PEEK => peeks into / sees data from the incoming side

	if (iReceiveFromClient == SOCKET_ERROR) {

		cout << "Receive data from client failed with : " << WSAGetLastError() << endl;

	}
	
	cout << "Data received from client is : " << Buffer << endl;


	// 6 close server side socket

	iCloseServerSideSocket = closesocket(UDPServerSideSocket);

	if (iCloseServerSideSocket == SOCKET_ERROR) {
		cout << "closing socket failed" << WSAGetLastError() << endl;
	}
	cout << "Closed socket successfully" << endl;

	//7 WSA Cleanup function for terminating dll
	iWsaCleanup = WSACleanup();
	
	if (iWsaCleanup == SOCKET_ERROR) {
		cout << "closing socket failed" << WSAGetLastError() << endl;
	}
	cout << "WSA cleanedup successfully" << endl;

	return 0;
}