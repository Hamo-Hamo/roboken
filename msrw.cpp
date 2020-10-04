#include "msrw.hpp"
namespace mswr {

int myser::init(char *port, int rate) {
  baudRate = rate;
  fd = open(port, O_RDWR);
  if (fd < 0) {
    std::cout << "apen error" << std::flush;
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
  len_receive = ::read(fd, buf_receive, sizeof(buf_receive));
  if (0 < len_receive) {
    for (i = 0; i < len_receive; i++) {
      std::cout << buf_receive[i];
    }
    std::cout << std::endl;
  }
}

void myser::write(char *buffer) {
  len_send = sizeof(buffer);
  std::cout << len_send << " " << buffer << std::endl;
  ::write(fd, buffer, len_send);
}

myser::myser() {}
myser::~myser() {}

void myser::devclose() { close(fd); }
} // namespace mswr
