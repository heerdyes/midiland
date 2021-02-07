#include <sys/soundcard.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define  MIDI_DEVICE_INST  "/dev/midi2"

void busywait(int kn)
{
  int n=kn*100000;
  for(int i=0;i<n;i++);
}

int main(void)
{
  unsigned char data[3]={0x90,55,127};
  int rest=1000;

  // first open the midi device for writing.
  int fdw=open(MIDI_DEVICE_INST,O_WRONLY,0);
  if (fdw<0)
  {
    printf("[fdw] Error: cannot open %s\n", MIDI_DEVICE_INST);
    exit(1);
  }
  
  // note read loop
  while(1)
  {
    char c=getchar();
    if(c=='0'){ break; }
    if(c=='\n'){ continue; }
    int ic=(int)c;
    ic=48+ic-97;
    data[0]=0x90;
    data[1]=ic;
    if(c==' ')
    {
      printf("rest\n");
      busywait(rest);
    }
    else
    {
      printf("note: %d\n",data[1]);
      write(fdw,data,sizeof(data));
    }
    busywait(rest);
    data[0]=0x80;
    write(fdw,data,sizeof(data));
  }

  return 0;
}

