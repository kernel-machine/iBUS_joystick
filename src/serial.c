#include "serial.h"

int serial_set_interface_attribs(int fd, int speed, int parity) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
    return -1;
  }
  switch (speed){
  case 9600:
    speed=B9600;
  break;
  case 19200:
    speed=B19200;
    break;
  case 57600:
    speed=B57600;
    break;
  case 115200:
    speed=B115200;
    break;
  default:
    printf("cannot sed baudrate %d\n", speed);
    return -1;
  }
  cfsetospeed (&tty, speed);
  cfsetispeed (&tty, speed);
  cfmakeraw(&tty);
  // enable reading
  tty.c_cflag &= ~(PARENB | PARODD);               // shut off parity
  tty.c_cflag |= parity;
  tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;      // 8-bit chars

  if (tcsetattr (fd, TCSANOW, &tty) != 0) {
    fprintf (stderr,"error %d from tcsetattr\n", errno);
    return -1;
  }
  return 0;
}

void serial_set_blocking(int fd, int should_block) {
  struct termios tty;
  memset (&tty, 0, sizeof tty);
  if (tcgetattr (fd, &tty) != 0) {
      fprintf (stderr,"error %d from tggetattr\n", errno);
      return;
  }

  tty.c_cc[VMIN]  = should_block ? 1 : 0;
  tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

  if (tcsetattr (fd, TCSANOW, &tty) != 0)
    fprintf (stderr,"error %d setting term attributes\n", errno);
}

int serial_open(const char* name) {
  int fd = open (name, O_RDWR | O_NOCTTY | O_SYNC );
  if (fd < 0) {
    fprintf (stderr,"error %d opening serial, fd %d\n", errno, fd);
  }
  return fd;
}


void serial_read(int fd, uint8_t * buf, size_t size){
  uint8_t b;

  for(int i = 0 ;i<size;i++){
    if(read(fd,&b,sizeof(uint8_t))<=0) {
      perror("Read Error!");
      exit(1);
      break;
    }
    *(buf+i)=b;
  }
}

/*
int serial_read(int fd, fs_decoder *decoder)
{
  tcflush(fd, TCIFLUSH);    // Discards old data in the rx buffer

  uint8_t read_buffer[32];  // Buffer to store the data received
  int bytes_read = 0;       // Number of bytes read by the read() system call
  printf("CALLED 2 %d\n", fd);

  do {
  bytes_read += read(fd, read_buffer+bytes_read , 32-bytes_read); // Read the data
  } while(bytes_read<=32);

  printf("READED %d BYTEs\n", bytes_read);

  if (bytes_read == 32 && frame_validation(read_buffer))
  {
    printf("OK\n");
    return 1;
  }
  else
  {
    printf("ERROR \n");
    return 0;
  }
}
*/
