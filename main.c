#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>

#include <net/if.h>       // ifreq
#include <linux/if_tun.h> // IFF_TUN, IFF_NO_PI
#include <linux/if_arp.h>

#include <sys/ioctl.h>

#include "util.c"



int main(int argc, char **argv)
{
  if (argc != 2)
    return 1;
  const char *device_name = argv[1];
  if (strlen(device_name) + 1 > IFNAMSIZ)
    return 1;

  // Request a TAP device:
  int fd = open("/dev/net/tun", O_RDWR);
  if (fd == -1)
    return 1;
  struct ifreq ifr;
  memset(&ifr, 0, sizeof(ifr));
  ifr.ifr_flags = IFF_TAP | IFF_NO_PI;
  strncpy(ifr.ifr_name, device_name, IFNAMSIZ);
  int res = ioctl(fd, TUNSETIFF, &ifr);
  if (res == -1)
    return 1;

  char buffer[BUFFLEN];
  char buffer2[2 * BUFFLEN + 1];
  while (1)
  {

    // Read a frame:
    ssize_t count = read(fd, buffer, BUFFLEN);
    if (count < 0)
      return 1;

    // Dump frame:
    hex(buffer, buffer2, count);
    fprintf(stderr, "%s\n", buffer2);
  }

  return 0;
}
