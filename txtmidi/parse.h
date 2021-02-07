// parsing utility functions

void scanline(int lim,char dst[])
{
  printf(">> ");
  int i;
  for(i=0;i<lim-1;i++)
  {
    char c=getchar();
    if(c=='\n')
      {break;}
    else
      {dst[i]=c;}
  }
  dst[i]='\0';
}

void dumpcarr(int n,char s[])
{
  printf("[dump] ");
  for(int i=0;i<n;i++)
  {
    printf("%c",s[i]);
  }
  printf("\n");
}

int findchar(char c,char s[],int beg,int lim)
{
  int idx;
  for(int i=0;i<lim;i++)
  {
    idx=beg+i;
    if(s[idx]==c)
    {
      return idx;
    }
  }
  return -1;
}

int substring(int beg,char s[],char d[],int lim)
{
  int i;
  for(i=0;i<lim;i++)
  {
    if(s[beg+i]=='\0'){break;}
    d[i]=s[beg+i];
  }
  d[i]='\0';
}

int eattilldelim(char delim,int beg,char src[],char dst[],int lim)
{
  int dloc;
  int si,di;
  dloc=findchar(delim,src,beg,lim);
  if(dloc==-1)
  {
    return -1;
  }
  for(si=beg,di=0;si<dloc;si++,di++)
  {
    dst[di]=src[si];
  }
  dst[di]='\0';
  return si;
}

int eattillspace(int beg,char src[],char dst[],int lim)
{
  return eattilldelim(' ',beg,src,dst,lim);
}

