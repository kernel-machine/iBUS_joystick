#ifndef SERIAL
#define SERIAL

#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions 	   */
#include <errno.h>   /* ERROR Number Definitions           */
#include <stdint.h>
#include "fs_decoder.h"
#include <stdint.h>
#include <string.h>

#define BAUDRATE B115200

/*
int serial_connect(char * device_name);
int serial_read(int fd, fs_decoder * decoder);
*/
int serial_set_interface_attribs(int fd, int speed, int parity);
void serial_set_blocking(int fd, int should_block);
void serial_read(int fd, uint8_t * buf, size_t size);
int serial_open(const char* name);
#endif