#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include<stdio.h>
#include<winsock2.h>
#include<cstring>
using namespace std;



//#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512  //Max length of buffer
#define PORT 8888   //The port on which to listen for incoming data

int main()
{
    SOCKET s;
    struct sockaddr_in server, si_other;
    int slen , recv_len;
    char buf[BUFLEN];
    WSADATA wsa;


    slen = sizeof(si_other) ;

    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( PORT );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);


        /* license code starts*/

    	//cout<<"inside main"<<endl;
    	system("D:\\WindRiver69\\maintenance\\wrInstaller\\x86-win32\\lmutil lmstat -a > lic.txt");



    	char ch;
    stringstream sx;
    string s1,s2;

    ifstream in("lic.txt");

    //cout<<"reading the file"<<endl<<endl;
    while(in)
    {
    in.get(ch);
    sx<<ch;
   // cout<<ch;
    }

   // cout<<"reading string counter part:"<<endl<<endl;
    s1 = sx.str();
   // cout<<s1<<endl;

   // cout<<"reading sub string version"<<endl<<endl;
    s2 = s1.substr(631,10);
    cout<<s2<<endl;

        /*license code ends*/

    	strcpy(buf,s2.c_str());

        //now reply the client with the same data
        if (sendto(s, buf, 20, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
        {
            printf("sendto() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        memset(buf,'\0', BUFLEN);
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
