#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <cstdio>
#include <cstdlib>

#include <iostream>

#include "../NexuzProtocol.hpp"

using namespace std;

int main() {
  int sock, listener;
  struct sockaddr_in addr;
  NexuzProtocol * p = new NexuzProtocol();

  listener = socket(AF_INET, SOCK_STREAM, 0);
  if (listener < 0) {
    perror("socket");
    exit(1);
  }

  addr.sin_family = AF_INET;
  addr.sin_port = htons(3425);
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  if (bind(listener, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
    perror("bind");
    exit(2);
  }

  listen(listener, 1);

  while (true) {
    sock = accept(listener, NULL, NULL);
    if (sock < 0) {
      perror("accept");
      exit(3);
    }

    while (true) {

//      cout << sizeof(NexuzProtocol) << endl;
      //      try {
      int bytes_read = recv(sock, p, sizeof(NexuzProtocol), 0);
      if (bytes_read <= 0) {
        break;
      }

//      cout << p -> protocolName << endl;
      cout << p -> data << endl;

      //      write(1, p -> protocolName, 6);
      //            send(sock, buf, bytes_read, 0);
      //      } catch (char * e) {
      //        cout << "SHIT happend" << endl;
      //        cerr << e << endl;
      //      }
    }

    close(sock);
  }

  close(sock);
  return 0;
}
