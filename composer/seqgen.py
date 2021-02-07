import sys

def timefrac(sn):
  nd=sn.split('/')
  n,d=nd[0],nd[1]
  note=n[-2:]
  num=0
  if len(n)==2:
    num=1
  else:
    num=int(n[0:-2])
  dnm=int(d)
  return num/dnm,note

class Note:
  def __init__(self,sn,smap):
    self.tfrac,self.pitch=timefrac(sn)
    self.swaramap=smap
    self.isrest=self.pitch=='_0'
    if not self.isrest:
      self.midipitch=self.midify()
    self.on=False
    self.elapsedtime=0.0
  
  def genplay(self,fo):
    self.elapsedtime=self.tfrac
    self.on=True
    if not self.isrest:
      print('d %d 127'%(self.midipitch),file=fo)
  
  def midify(self):
    octave=int(self.pitch[1])
    swara=self.pitch[0]
    offset=24+12*octave
    return offset+swaramap[swara]
  
  def genelapse(self,dur,fo):
    self.elapsedtime-=dur
    if self.elapsedtime<-0.0001:
      raise Exception('elapsedtime: %f, most likely a timing bug'%self.elapsedtime)
    if abs(self.elapsedtime)<0.0001:
      self.on=False
      self.elapsedtime=0.0
      if not self.isrest:
        print('u %d'%(self.midipitch),file=fo)

  def __str__(self):
    return '[%f, %s, %d]'%(self.tfrac,self.pitch,self.midipitch)


def minnote(n1,n2):
  mn=n1
  if n2.elapsedtime<n1.elapsedtime:
    mn=n2
  return mn

# flow
if len(sys.argv)!=3:
  print('usage: python3 seqgen.py <tune.hook> <out.seq>')
  exit(0)

swaramap={'s':0,'S':1,'r':2,'R':3,'g':4,'m':5,'M':6,'p':7,'P':8,'d':9,'D':10,'n':11}
fn=sys.argv[1]
fout=sys.argv[2]
print('processing file: %s'%fn)

lines=[]
with open(fn) as f:
  lines=f.readlines()

# parse header
headln=lines[0].rstrip()
tokens=headln.split(' ')
polyphony=2
timeunit=500
if tokens[0]=='timeunit':
  timeunit=int(tokens[1])
print('polyphony: %d, timeunit: %d'%(polyphony,timeunit))

# parse body
i,j=0,0
L,R=lines[1].rstrip(),lines[2].rstrip()
lt_trk=[Note(sn,swaramap) for sn in L.split(' ')]
rt_trk=[Note(sn,swaramap) for sn in R.split(' ')]

with open(fout,mode='w') as fo:
  while True:
    if i>=len(lt_trk) or j>=len(rt_trk):
      break
    lnote=lt_trk[i]
    rnote=rt_trk[j]
    if not lnote.on:
      lnote.genplay(fo)
    if not rnote.on:
      rnote.genplay(fo)
    mnote=minnote(lnote,rnote)
    mindur=mnote.elapsedtime
    print('w %d'%(int(mindur*timeunit)),file=fo)
    lnote.genelapse(mindur,fo)
    rnote.genelapse(mindur,fo)
    if not lnote.on:
      i+=1
    if not rnote.on:
      j+=1

