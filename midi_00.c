#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  MIDI_DEVICE  "/dev/midi"


int main(void) {
  unsigned char inpacket[4];

  // first open the controller device for reading.
  int seqfd = open(MIDI_DEVICE, O_RDONLY);
  if (seqfd == -1) {
    printf("Error: cannot open %s\n", MIDI_DEVICE);
    exit(1);
  }

  // now just wait around for MIDI bytes to arrive and print them to screen.
  while (1) {
    read(seqfd, &inpacket, sizeof(inpacket));
    printf("[midi] %d %d %d %d\n",inpacket[0],inpacket[1],inpacket[2],inpacket[3]);
  }

  return 0;
}

