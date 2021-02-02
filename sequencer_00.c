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
int main(void)
{
  struct noteseq *seq00;

  // open the midi device for writing.
  int fd=open(MIDI_DEVICE,O_WRONLY,0);
  if(fd<0)
  {
    printf("Error: cannot open %s\n", MIDI_DEVICE);
    exit(1);
  }
  
  // load sequence
  seq00=loadseq("tune00.seq");
  
  // run sequence
  playseq(10,seq00,fd);

  close(fd);
  return 0;
}

