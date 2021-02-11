#include <winsock2.h>
#include <windows.h>
#include <sstream>
#include <iostream>
// -lws2_32 || -lwsock32
// ld is the dumbest linker ive ever seen in my life
// i would use vs studio instead of mingw but its weird and im used to unix systems
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "ws2_32.lib")

using namespace std;
#define BUFFER 1024

int main() {
    // data
    WSAData data;
    // version
    WORD version = MAKEWORD(2, 2);
    // checking if all is ok
    int wsOK = WSAStartup(version, &data);
    if (wsOK != 0) { return -1; }
    SOCKET lsock = socket(AF_INET, SOCK_STREAM, 0);
    if (lsock==INVALID_SOCKET) { return -1; }
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    // maybe error
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(55555);
    // cast the type of addr to socketaddr*, i have no idea why this wasnt used to init struct but whatever
    bind(lsock, (sockaddr*)&addr, sizeof(addr));


    // begin the multiprocesses without threads or asyncronous concepts, we will use maaggiiicc....
    // listen on our binded socket, allow maximum of 1024 connections, obviously thats a lot but we plan to make this multi client
    listen(lsock, 1024);

    /* --------------------------------------------------------------------------------

    sockaddr_in client;
    int clientSize = sizeof(client);
    SOCKET clientSocket = accept(lsock, (sockaddr*)&client, &clientSize);
    if (clientSocket==INVALID_SOCKET) { return; }

    // clients remote name
    char host[NI_MAXHOST];
    // port the client is connected on && NI_MAXHOST just means 0xFFFFFF... something i forgot but its a very large number
    char service[NI_MAXHOST];
    // clear out each buffer and fill with 0
    // NI_MAXHOST i guess is also to maintain a static buffer size throughout the script
    ZeroMemory(host, NI_MAXHOST);
    ZeroMemory(service, NI_MAXHOST);

    getnameinfo( (sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0 );
    cout<<host<<" connected on port "<<service<<endl;

    closesocket(lsock);
    char buff[4096];
    while(1) {
        ZeroMemory(buff, sizeof(buff));
        // recv error
        int bytesRecieved = recv(clientSocket, buff, sizeof(buff), 0);
        if (bytesRecieved==SOCKET_ERROR) {
            return;
            break;
        }
        // client disconnected
        if(bytesRecieved==0) {
            return;
            break;
        }
        // +1 because when we recv a message, we dont get the /0 or \n
        send(clientSocket, buff, bytesRecieved + 1, 0);
    }
    closesocket(clientSocket);
---------------------------------------------------------------------------------------*/
    // apparently winsock has file descriptors as well???
    // master set
    fd_set master;
    // zero the set, nothing exists in the set
    FD_ZERO(&master);
    // specify our socket
    FD_SET(lsock, &master);

    while(1) {
        // make a copy of master file descriptor set, because each time we call select will destroy it
        fd_set copy = master;
        // big boyzzz only: https://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-select
        int socketCount = select(0, &copy, NULL, NULL, NULL);

        for (int i=0;i<socketCount;i++) {
            // iterate through file descriptor array for copy fd set
            SOCKET sock = copy.fd_array[i];
            if (sock==lsock) {
                // accept
                SOCKET client = accept(lsock, NULL, NULL);
                
                // add new connection to master file set || SUPER DUPER IMPORTANT PART
                FD_SET(client, &master);

                // send welcome message to connected client
                char welcomeMessage[]="Welcome to our chat server!\r\n";
                // welcomeMessage.c_str() turns it into a const char*, which in this case is needed since were sending bytes only
                // not fancy schmancy strings
                send(client, welcomeMessage, sizeof(welcomeMessage), 0);

            } else {
                // declare buffer for data and fill with null
                char buff[BUFFER];
                ZeroMemory(buff, BUFFER);
                // accept message
                // incoming socket
                int bytesRecv = recv(sock, buff, BUFFER, 0);
                // if 0, client disconnected and drop client
                if(bytesRecv <= 0) {
                    closesocket(sock);
                    // clear this connection from master file set
                    FD_CLR(sock, &master);
                // else send message to other clients and NOT to listening socket
                } else {
                    // for each element in array || connection on our server
                    for (int i=0; i<master.fd_count; i++) {
                        // outSock is the first client connected on our server on the first iteration
                        SOCKET outSock = master.fd_array[i];
                        if (outSock != lsock && outSock != sock) {
                            ostringstream ss;
                            ss<<"SOCKET #"<<sock<<": \t"<<buff<<"\r\n";
                            // convert string stream to string?
                            string strOut=ss.str();
                            // then convert to chars??
                            // strOut.size() + 1 probably for \n
                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                        }
                    }
                }
            }
        }
    }
    WSACleanup();
}
