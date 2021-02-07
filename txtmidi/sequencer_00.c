#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "sequencer.h"

#define  MIDI_DEVICE  "/dev/midi2"

// globals
char debugging='y';

// functions
void d(char* msg)
{
  if(debugging=='y')
  {
    printf("%s\n",msg);
  }
}

// flow
int main(int argc,char *argv[])
{
  struct noteseq *seq00;
  int iters=1;
  int fd;
  
  if(argc!=3)
  {
    printf("usage: ./sequencer_00 <tune.seq> <niter>\n");
    exit(0);
  }
  sscanf(argv[2],"%d",&iters);
  
  // open the midi device for writing.
  fd=open(MIDI_DEVICE,O_WRONLY,0);
  if(fd<0)
  {
    printf("Error: cannot open %s\n", MIDI_DEVICE);
    exit(1);
  }
  
  // load sequence
  seq00=loadseq(argv[1]);
  
  // run sequence
  playseq(iters,seq00,fd);

  close(fd);
  return 0;
}

