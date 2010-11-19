#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/**
 * getIPv4()
 *
 * This function takes a network identifier such as "eth0" or "eth0:0" and
 * a pointer to a buffer of at least 16 bytes and then stores the IP of that
 * device gets stored in that buffer.
 *
 * it return 0 on success or -1 on failure.
 *
 * Author:  Jaco Kroon <jaco@kroon.co.za>
 */
int getIPv4(const char * dev, char * ipv4) {
  struct ifreq ifc;
  int res;
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sockfd < 0)
    return -1;
  strcpy(ifc.ifr_name, dev);
  res = ioctl(sockfd, SIOCGIFADDR, &ifc);
  close(sockfd);
  if (res < 0)
    return -1;
  strcpy(ipv4, inet_ntoa(((struct sockaddr_in*) &ifc.ifr_addr)->sin_addr));
  return 0;
}

int main() {
  char ip[16];
  if (getIPv4("wlan0", ip) == 0)
    printf("IPv4: %s\n", ip);
  else
    printf("No IP\n");
  return 0;
}
