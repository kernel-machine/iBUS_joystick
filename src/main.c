#include "fs_decoder.h"
#include "serial.h"
#include "stdio.h"
#include "joystick.h"
#include "string.h"

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp("--help", argv[1]) == 0)
    {
        printf("./iBUS_joystick [option]\n\n");
        printf("--help\t\tprint this message\n\n");
        printf("--input [serial device]\t\tset serial adapter \n\n");
        printf("Example:\n\n");
        printf("./iBUS_joystick --input /dev/ttyUSB1\n");
        printf("to connect to /dev/ttyUSB1 serial device\n\n");
        printf("default (without paramter) is /dev/ttyUSB0\n");
        return 0;
    }
    const char *serial_device;
    if (argc > 2 && strcmp("--input", argv[1]) == 0)
    {
        serial_device = argv[2];
    }
    else
        serial_device = "/dev/ttyUSB0";

    printf("Connecting to %s\n", serial_device);
    int fd = serial_open(serial_device);
    serial_set_interface_attribs(fd, 115200, 0);
    serial_set_blocking(fd, 1);
    if (fd > 0)
        printf("Serial opened\n");
    else
    {
        printf("Error when opening serial\n");
        return 0;
    }

    int js_fd = create_joystick();

    if (js_fd > 0)
        printf("Virtual joystick created\n");
    else
        printf("Error when create virtual joystick\n");
    joystick_data js_data;

    fs_decoder decoder;
    uint8_t buff[32];
    printf("The software is running...\n");
    printf("Press Ctrl+C to quit\n");
    int channel_values[4];
    while (1)
    {
        serial_read(fd, buff, 32);
        if (frame_validation(buff))
        {
            get_data(&decoder, buff);

            for (int i = 0; i < 4; i++)
            {
                channel_values[i] = get_channel(&decoder, i);
                set_channel_value(&js_data, i, channel_values[i]);
            }
            flush_data(&js_data, js_fd);
            printf("CHANNEL 1 - %d | CHANNEL 2 - %d | CHANNEL 3 - %d | CHANNEL 4 - %d\r",
                   channel_values[0], channel_values[1], channel_values[2], channel_values[3]);
        }
    }

    return 0;
}