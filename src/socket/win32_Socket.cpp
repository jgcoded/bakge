/* *
 * The MIT License (MIT)
 *
 * Copyright (c) 2013 Paul Holden et al. (See AUTHORS)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 * */

#include <bakge/Bakge.h>

namespace bakge
{

win32_Socket::win32_Socket()
{
    SocketHandle = 0;
    memset((void*)&ServerAddress, 0, sizeof(ServerAddress));
}


win32_Socket::~win32_Socket()
{
    closesocket(SocketHandle);
}


win32_Socket* win32_Socket::Create(int Port)
{
    win32_Socket* Sock = new win32_Socket;

    Sock->SocketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    Sock->ServerAddress.sin_family = AF_INET;
    Sock->ServerAddress.sin_addr.s_addr = INADDR_ANY;
    Sock->ServerAddress.sin_port = htons(Port);

    if(bind(Sock->SocketHandle, (struct sockaddr*)&(Sock->ServerAddress),
                        sizeof(Sock->ServerAddress)) == SOCKET_ERROR) {
        perror("bind()");
        delete Sock;
        return NULL;
    }

    return Sock;
}


Packet* win32_Socket::Receive()
{
    struct sockaddr_in Receive;
    char* Data = new char[512];
    int Size = sizeof(Receive);

    printf("Waiting for packet...\n");
    if(recvfrom(SocketHandle, Data, 512, 0, (struct sockaddr*)&Receive,
                                                        &Size) < 0) {
        printf("Error receiving packet\n");
        return NULL;
    }

    delete[] Data;

    return Packet::Create(NULL);
}


Result win32_Socket::Send(Remote* Destination, Packet* Data)
{
    struct sockaddr_in Dest;
    memset((void*)&Dest, 0, sizeof(Dest));

    Dest.sin_addr.s_addr = htonl(Destination->GetAddress());
    Dest.sin_port = htons(Destination->GetPort());
    Dest.sin_family = PF_INET;

    sendto(SocketHandle, NULL, 0, 0, (struct sockaddr*)&Dest,
                                                sizeof(Dest));

    return BGE_SUCCESS;
}

} /* bakge */
