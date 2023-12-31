#include <fcntl.h>
#include <unistd.h>
#include <cerrno> 
#include <cstring>
#include <iostream>
#include <stdio.h>
#include <rfb/rfb.h>
#include <rfb/rfbclient.h>
//sudo apt-get install libvnc-dev
int main(int argc, char *argv[]) {
   int i;
  uint8_t bytes[256*3];

  rfbScreenInfoPtr server=rfbGetScreen(&argc,argv,256,256,8,1,1);
  if(!server)
    return 0;
  server->serverFormat.trueColour=FALSE;
  server->colourMap.count=256;
  server->colourMap.is16=FALSE;
  for(i=0;i<256;i++) {
    bytes[i*3+0]=255-i; /* red */
    bytes[i*3+1]=0; /* green */
    bytes[i*3+2]=i; /* blue */
  }
  bytes[128*3+0]=0xff;
  bytes[128*3+1]=0;
  bytes[128*3+2]=0;
  server->colourMap.data.bytes=bytes;

  server->frameBuffer=(char*)malloc(256*256);
  for(i=0;i<256*256;i++)
     server->frameBuffer[i]=(i/256);

  rfbInitServer(server);
  rfbRunEventLoop(server,-1,FALSE);

  return(0);
}
