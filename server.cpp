#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <cstring> //bzero
#include <netinet/in.h>//INADDR_ANY
#include <arpa/inet.h>//htons
#include <unistd.h>
using namespace std;

#define ENABLE 1
#define DISABLE 0
#define LISTEN_BACKLOG 10
#define PORT 5050


void Handle_Error(string str){
	perror(str.c_str());
	exit(0);
}


int main(){

	int fd;
	fd  = socket(AF_INET,SOCK_STREAM,0);
	if(fd <0)
		Handle_Error("socket():");

	int ret = 0;
	int option = ENABLE;
	ret = setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&option,sizeof(option));
	if(ret<0)
		Handle_Error("setsockopt():");

	struct sockaddr_in addr_srv;
	bzero((char*)&addr_srv,sizeof(addr_srv));
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_srv.sin_port = htons(PORT);
	
	ret = bind(fd,(struct sockaddr*)&addr_srv,sizeof(addr_srv));
	if(ret<0)
		Handle_Error("bind():");

	ret = listen(fd,LISTEN_BACKLOG);	
	if(ret<0)
		Handle_Error("listen():");
	
	struct sockaddr_in addr_cli;
	bzero((char*)&addr_cli,sizeof(addr_cli));
	int addr_cli_size = sizeof(addr_cli);

	int connection=0;
	
	char buffer[100] = {0};
	int read_bytes;
	size_t exit_msg;
	while(true){
		cout << "Waiting for connection " << endl;
		bzero(buffer,sizeof(buffer));
		read_bytes = 0;
	connection = accept(fd,(struct sockaddr*)&addr_cli,(socklen_t*)&addr_cli_size);
	if(connection<0)
		Handle_Error("accept():");	
	else{
	cout << "Connection Received" << endl;
	//get client details
	}

	while(true){	
	read_bytes = read(connection,buffer,sizeof(buffer));
	if(read_bytes<0)
		Handle_Error("read():");

	cout << "Data Received:" << buffer << endl;
	
	
	if(strstr(buffer,"exit") != nullptr)
		break;
	}
	//wait for new connection now
	}

	close(fd);
	return 0;
}
