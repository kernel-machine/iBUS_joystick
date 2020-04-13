#include "joystick.h"

const u_int16_t CMD[] = {ABS_TILT_Y,ABS_TILT_X,ABS_THROTTLE,ABS_RUDDER};

void setup_abs(int fd, unsigned chan, int min, int max)
{
    if (ioctl(fd, UI_SET_ABSBIT, chan))
        perror("UI_SET_ABSBIT");

    struct uinput_abs_setup s =
        {
            .code = chan,
            .absinfo = {.minimum = min, .maximum = max},
        };

    if (ioctl(fd, UI_ABS_SETUP, &s))
        perror("UI_ABS_SETUP");
}

int create_joystick()
{
    int fd = open("/dev/uinput", O_WRONLY | O_NONBLOCK);

    if (fd < 0)
    {
        fprintf(stderr,"Error when open /dev/uinput");
        return -1;
    }

    ioctl(fd, UI_SET_EVBIT, EV_ABS); // enable analog absolute position handling

    for (int i = 0; i < AXES_NUMBER; i++)
    {
        setup_abs(fd, CMD[i], 1000, 2000);
    }

    struct uinput_setup setup =
        {
            .name = "Userspace Joystick",
            .id =
                {
                    .bustype = BUS_USB,
                    .vendor = 0x3,
                    .product = 0x4,
                    .version = 2,
                }};

    if (ioctl(fd, UI_DEV_SETUP, &setup))
    {
        perror("UI_DEV_SETUP");
        return -1;
    }

    if (ioctl(fd, UI_DEV_CREATE))
    {
        perror("UI_DEV_CREATE");
        return -1;
    }
    return fd;
}

int flush_data(joystick_data *data, int fd)
{
    struct input_event ev[AXES_NUMBER + 1];
    memset(&ev, 0, sizeof ev);
    u_int8_t i;
    for (i = 0; i < AXES_NUMBER; i++)
    {
        ev[i].type = EV_ABS;
        ev[i].code = CMD[i];
        ev[i].value = data->data_value[i];
    }

    ev[i].type = EV_SYN;
    ev[i].code = SYN_REPORT;
    ev[i].value = 0;

    if (write(fd, &ev, sizeof ev) < 0)
    {
        perror("write");
        return -1;
    }
    return 0;
}

void set_channel_value(joystick_data *data, u_int8_t channel, int value)
{
    if (channel < AXES_NUMBER)
        data->data_value[channel] = value;
}