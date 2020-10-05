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
  void devclose();

private:
  const char *msg = "serial port open...";
  unsigned char buf[255] = {0};
  int fd;
  struct termios tio;
  int baudRate;
  int i;
  int len;
  int ret;
  int size;
};

int myser::init(char *port, int rate) {
  baudRate = rate;
  fd = open(port, O_RDWR);
  if (fd < 0) {
    std::cout << "open error" << std::endl;
    return -1;
  }

  tio.c_cflag += CREAD;
  tio.c_cflag += CLOCAL;
  tio.c_cflag += CS8;
  tio.c_cflag += 0;
  tio.c_cflag += 0;

  cfsetispeed(&tio, baudRate);
  cfsetospeed(&tio, baudRate);

  cfmakeraw(&tio);

  tcsetattr(fd, TCSANOW, &tio);
  ioctl(fd, TCSETS, &tio);

  return 0;
}

void myser::read() {
  len = ::read(fd, buf, sizeof(buf));
  if (0 < len) {
    for (i = 0; i < len; i++) {
      std::cout << buf[i];
    }
    std::cout << std::endl;
  }
}

myser::myser() {}
myser::~myser() {}

void myser::devclose() { close(fd); }
} // namespace mswr

int main() {
  mswr::myser ms;
  ms.init("/dev/ttyUSB0", B9600);
  while (1) {
    ms.read();
  }
  ms.devclose();
}
