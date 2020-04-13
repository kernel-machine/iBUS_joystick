#include "fs_decoder.h"

int frame_validation(uint8_t *buffer) {
    uint8_t i;
    uint16_t checksum = 0xFFFF;
    uint16_t rxChecksum = 0x0000;

    for (i=0; i<30; i++) {
        checksum -= buffer[i];
    }

    rxChecksum = buffer[30] + (buffer[31] << 8);

    if (rxChecksum == checksum) {
        return 1;
    } else {
        return 0;
    }
}

void get_data(fs_decoder * decoder, uint8_t *buffer) {
    for (int i=1; i<CHANNEL_SIZE+1; i++) {
        decoder->data[i-1] = buffer[i * 2] + (buffer[i * 2 + 1] << 8);
    }
}

uint16_t get_channel(fs_decoder * decoder,uint8_t channel) {
    return decoder->data[channel];
}

void print_channels(fs_decoder * decoder) {
  for (int i=0; i<CHANNEL_SIZE; i++) {
      printf("CHANNEL %d - %d\n",i,get_channel(decoder,i));
  }
}
