/*******************************************************************************
 * Copyright (c) 2010, Alex Ivasyuv                                            *
 * All rights reserved.                                                        *
 *                                                                             *
 * Redistribution and use in source and binary forms, with or without          *
 * modification, are permitted provided that the following conditions are met: *
 *                                                                             *
 * 1. Redistributions of source code must retain the above copyright           *
 *    notice, this list of conditions and the following disclaimer.            *
 * 2. Redistributions in binary form must reproduce the above copyright        *
 *    notice, this list of conditions and the following disclaimer in the      *
 *    documentation and/or other materials provided with the distribution.     *
 *                                                                             *
 * THIS SOFTWARE IS PROVIDED BY Alex Ivasyuv ''AS IS'' AND ANY                 *
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED   *
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE      *
 * DISCLAIMED. IN NO EVENT SHALL Alex Ivasyuv BE LIABLE FOR ANY DIRECT,        *
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES          *
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;*
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND *
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT  *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF    *
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.           *
 ******************************************************************************/

#include "Port.hpp"

namespace Nexuz {
  namespace Network {
    Port::Port() {
    }

    Port::~Port() {
    }

    bool Port::openOut() {
//      char message[] = "Hello there!\n";
//      char buf[sizeof(message)];

      struct sockaddr_in addr;

      this -> sock = socket(AF_INET, SOCK_STREAM, 0);
      if (this -> sock < 0) {
        perror("socket");
        exit(1);
      }

      addr.sin_family = AF_INET;
      addr.sin_port = htons(3425); // или любой другой порт...
      addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
      if (connect(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
      }

      //      send(sock, message, sizeof(message), 0);
      //      recv(sock, buf, sizeof(message), 0);
      //
      //      printf(buf);
    }

    bool Port::writeOut(void * data, int size) {
      send(sock, data, size, 0);
//      recv(sock, buf, sizeof(message), 0);

//      printf(buf);
    }

  }
}

