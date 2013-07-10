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

osx_Socket::osx_Socket()
{
    SocketHandle = 0;
}


osx_Socket::~osx_Socket()
{
    if(SocketHandle >= 0) {
        close(SocketHandle);
    }
}


osx_Socket* osx_Socket::Create(int Port)
{
    osx_Socket* Sock = new osx_Socket;

    Sock->SocketHandle = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(Sock->SocketHandle < 0) {
        printf("Unable to attach socket\n");
        delete Sock;
        return Sock;
    }

    printf("Socket %d\n", Sock->SocketHandle);

    memset((void*)&(Sock->SocketIn), 0, sizeof(Sock->SocketIn));
    Sock->SocketIn.sin_family = AF_INET;
    Sock->SocketIn.sin_port = htons(Port);
    Sock->SocketIn.sin_addr.s_addr = INADDR_ANY;

    if(bind(Sock->SocketHandle, (struct sockaddr*)&(Sock->SocketIn),
                                       sizeof(Sock->SocketIn)) < 0) {
        perror("bind()");
        delete Sock;
        return NULL;
    }

    return Sock;
}


Packet* osx_Socket::Receive()
{
    struct sockaddr_in ReceiveSocketIn;
    Byte* Data = new Byte[512];
    int Size = sizeof(ReceiveSocketIn);

    printf("Waiting for packet...\n");
    if(recvfrom(SocketHandle, Data, 512, 0, (struct sockaddr*)&ReceiveSocketIn,
                                                    (socklen_t*)&Size) < 0) {
        printf("Error receiving packet\n");
        return NULL;
    }

    delete[] Data;

    return Packet::Create(NULL);
}


Result osx_Socket::Send(Remote* Destination, Packet* Data)
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
