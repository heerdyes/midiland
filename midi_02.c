#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  MIDI_DEVICE  "/dev/midi3"

void busywait(int kn)
{
  int n=kn*100000;
  printf("[busywait] %d",n);
  for(int i=0;i<n;i++);
  printf("\n");
}

int main(void)
{
  unsigned char data[3]={0x90,55,127};

  // first open the midi device for writing.
  int fd=open(MIDI_DEVICE,O_WRONLY,0);
  if (fd<0)
  {
    printf("Error: cannot open %s\n", MIDI_DEVICE);
    exit(1);
  }

  // write midi bytes
  for(int i=0;i<10;i++)
  {
    data[0]=0x90;
    data[1]=55+i*2;
    write(fd,data,sizeof(data));
    busywait(200);
    data[0]=0x80;
    write(fd,data,sizeof(data));
    busywait(100);
  }
  close(fd);

  return 0;
}

