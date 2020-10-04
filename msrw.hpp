#ifndef My_Ser
#define My_Ser

#include <fcntl.h>
#include <iostream>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
namespace mswr {
class myser {
public:
  myser();
  ~myser();
  int init(char *port, int rate);
  void read();
  void write(char *buffer);
  void devclose();

private:
  const char *msg = "serial port open...";
  unsigned char buf_receive[1] = {0};
  int fd;
  struct termios tio;
  int baudRate;
  int i;
  int len_send;
  int len_receive;
  int ret;
  int size;
};
} // namespace mswr
#endif // My_Ser
