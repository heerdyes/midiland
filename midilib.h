#include <sys/soundcard.h>
#include <fcntl.h>

#define  MIDI_DEVICE  "/dev/midi"

extern unsigned char inpacket[4];
extern int seqfd;

void rdmidipkts()
{
  read(seqfd, &inpacket, sizeof(inpacket));
  //printf("[midi] %d %d %d %d\n",inpacket[0],inpacket[1],inpacket[2],inpacket[3]);
  glutPostRedisplay();
}

void initmidi()
{
  // first open the controller device for reading.
  seqfd=open(MIDI_DEVICE,O_RDONLY);
  if(seqfd==-1)
  {
    printf("[midilib] Error: cannot open %s\n",MIDI_DEVICE);
    exit(1);
  }
}

