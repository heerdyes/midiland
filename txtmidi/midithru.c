#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  MIDI_DEVICE_INST  "/dev/midi4"
#define  MIDI_DEVICE_CTRL  "/dev/midi3"

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
  unsigned char inpacket[4];

  // first open the midi device for writing.
  int fdw=open(MIDI_DEVICE_INST,O_WRONLY,0);
  if (fdw<0)
  {
    printf("[fdw] Error: cannot open %s\n", MIDI_DEVICE_INST);
    exit(1);
  }
  
  // first open the controller device for reading.
  int fdr=open(MIDI_DEVICE_CTRL, O_RDONLY);
  if (fdr==-1)
  {
    printf("[fdr] Error: cannot open %s\n", MIDI_DEVICE_CTRL);
    exit(1);
  }
  
  // midi read loop
  while(1)
  {
    read(fdr,&inpacket,sizeof(inpacket));
    printf("[midi_thru] %#04x %#04x %#04x %#04x\n",inpacket[0],inpacket[1],inpacket[2],inpacket[3]);
    write(fdw,inpacket,sizeof(inpacket));
  }

  return 0;
}

