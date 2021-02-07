#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  MIDI_DEVICE  "/dev/midi3"


int main(void)
{
  unsigned char data[3]={0x90,60,127};

  // first open the midi device for writing.
  int fd=open(MIDI_DEVICE,O_WRONLY,0);
  if (fd<0)
  {
    printf("Error: cannot open %s\n", MIDI_DEVICE);
    exit(1);
  }

  // write midi bytes
  write(fd,data,sizeof(data));
  close(fd);

  return 0;
}

