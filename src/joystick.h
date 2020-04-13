#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/uinput.h>

#define msleep(ms) usleep((ms)*1000)

#define ABS_PITCH ABS_TILT_Y
#define ABS_ROLL ABS_TILT_X
#define AXES_NUMBER 4

typedef struct joystick_data
{
    int data_value[AXES_NUMBER];
}joystick_data;

void setup_abs(int fd, unsigned chan, int min, int max);
int create_joystick();
void set_channel_value(joystick_data * data,u_int8_t channel, int value );
int flush_data(joystick_data * data,int fd);

#endif