#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <unistd.h>
using namespace std;

#define PORT 5050

int main(){

	int fd;
	fd = socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
		perror("socket");


	struct sockaddr_in addr_srv;
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(PORT);

	int ret=0;
	ret = inet_pton(AF_INET,"127.0.0.1",&addr_srv.sin_addr);
	if(ret<0)
		perror("inet_pton");


	ret = connect(fd,(struct sockaddr*)&addr_srv,sizeof(addr_srv));
	if(ret<0)
		perror("connect");

	string data = "Hello from Client" ;
	
	while(true){
	cout  << "Enter data to send to client" << endl;
	cin >> data;
	ret = send(fd,data.c_str(),data.size(),0);
	if(ret<0)
		perror("send");

	size_t end = data.find("exit");
	if(end != string::npos)
		break;
	}

	close(fd);

	return 0;
}
