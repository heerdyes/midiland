#include "parse.h"

#define LINE_LIMIT  100
#define CHAR_LIMIT  20
#define TOKEN_LIMIT 10

// structures
struct sequnit
{
  char inst;
  int data0;
  int data1;
};

struct noteseq
{
  int seqlen;
  struct sequnit sequence[LINE_LIMIT];
};

// functions
void busywait(int kn)
{
  int n=kn*100000;
  for(int i=0;i<n;i++);
}

void chkfile(FILE *fptr)
{
  if(!fptr)
  {
    printf("could not open file!");
    exit(1);
  }
}

void parseline(char line[],int lnctr,struct noteseq *sq)
{
  char cmd[TOKEN_LIMIT];
  char arg0[TOKEN_LIMIT];
  char arg1[TOKEN_LIMIT];
  int a0,a1;
  
  int cmdend=eattillspace(0,line,cmd,TOKEN_LIMIT);
  sq->sequence[lnctr].inst=cmd[0];
  
  if(cmd[0]=='d')
  {
    int pitchend=eattillspace(cmdend+1,line,arg0,TOKEN_LIMIT);
    sscanf(arg0,"%d",&a0);
    substring(pitchend+1,line,arg1,TOKEN_LIMIT);
    sscanf(arg1,"%d",&a1);
    sq->sequence[lnctr].data0=a0;
    sq->sequence[lnctr].data1=a1;
  }
  else if(cmd[0]=='w' || cmd[0]=='u')
  {
    substring(cmdend+1,line,arg0,TOKEN_LIMIT);
    sscanf(arg0,"%d",&a0);
    sq->sequence[lnctr].data0=a0;
    sq->sequence[lnctr].data1=-1;
  }
  else
  {
    printf("[error] unknown cmd: %c\n",cmd[0]);
    exit(0);
  }
}

struct noteseq *loadseq(char *seqfnm)
{
  char line[CHAR_LIMIT];
  int param;
  int lnctr=0;
  FILE *fp;
  struct noteseq *sq;
  
  fp=fopen(seqfnm,"r");
  chkfile(fp);
  sq=malloc(sizeof(struct noteseq));
  printf("reading .seq lines into memory\n");
  
  while(fgets(line,CHAR_LIMIT,fp)!=NULL)
  {
    if(lnctr>=LINE_LIMIT)
    {
      printf("line limit reached. stopping reading.");
      break;
    }
    parseline(line,lnctr,sq);
    lnctr+=1;
  }
  sq->seqlen=lnctr;
  fclose(fp);
  return sq;
}

void dumpseq(struct noteseq *s0)
{
  printf("[midi_noteseq]\n");
  for(int i=0;i<s0->seqlen;i++)
  {
    printf("%d -> %c %d %d\n",i,s0->sequence[i].inst,s0->sequence[i].data0,s0->sequence[i].data1);
  }
  printf("[end]\n");
}

void playseq(int ntimes,struct noteseq *s0,int fd)
{
  unsigned char data[3];
  printf("# going to run %d iterations.\n",ntimes);
  for(int z=0;z<ntimes;z++)
  {
    printf("[%d]\n",z);
    for(int i=0;i<s0->seqlen;i++)
    {
      if(s0->sequence[i].inst=='w')
      {
        busywait(s0->sequence[i].data0);
      }
      else if(s0->sequence[i].inst=='d')
      {
        data[0]=0x90;
        data[1]=s0->sequence[i].data0;
        data[2]=s0->sequence[i].data1;
        write(fd,data,sizeof(data));
      }
      else if(s0->sequence[i].inst=='u')
      {
        data[0]=0x80;
        data[1]=s0->sequence[i].data0;
        data[2]=0;
        write(fd,data,sizeof(data));
      }
    }
  }
}

