#ifndef FS_DECODER
#define FS_DECODER

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#define CHANNEL_SIZE 10

typedef struct fs_decoder
{
  uint16_t data[CHANNEL_SIZE];
} fs_decoder;

int frame_validation(uint8_t *buffer);

void get_data(fs_decoder *decoder, uint8_t *buffer);
uint16_t get_channel(fs_decoder *decoder, uint8_t channel);
void print_channels(fs_decoder *decoder);

#endif