#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0); //creates default ipv4 tcp socket
	sockaddr_in serverAddress;
	serverAddress.sin_family = AF_INET; //IPV4
	serverAddress.sin_port = htons(8080); //PORT 8080 TO NETWORK BIG ENDIAN
	serverAddress.sin_addr.s_addr = INADDR_ANY; // listen on all available ips
	bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)); // put this socket on this ip and port
	listen(serverSocket, 5); // listen on the socket, maximum 5 pending requests
	int clientSocket = accept(serverSocket, nullptr, nullptr); // accept incoming connections, ignoring storage of ip and port, but opening a new socket to send to the client that was just recieved (on our same ip and port)
	char buffer[1024] = {0};
	recv(clientSocket, buffer, sizeof(buffer), 0);
	std::cout << "Message from client: " << buffer << std::endl;
	// client sends, we recieve, and print
std::string response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/plain\r\n"
    "Content-Length: 13\r\n"
    "\r\n"
    "Hello, world!";	
	send(clientSocket, response.c_str(), response.size(), 0);
	close(clientSocket);
	//as is, this code blocks at accept until a singular client connects, and same for rcv
	
	return 0;
}
