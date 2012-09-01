/*
 Copyright (c) 2011, a4a881d4
 All rights reserved.

 */

#include "sha1.h"
#include <string.h>
#include <stdio.h>
#include <string>

using namespace std;

void Usage() {
  printf("split-file big-file blocksize(1^blocksize) out-path\n");
}
  
int main(int argc, char* argv[])
{

  unsigned char hash[20];
  char hexstring[41]; // 40 chars + a zero
  int end = 0;
  hexstring[40] = 0;
  if( argc != 4 ) {
    Usage();
    return -1;
  }
  FILE* fh = fopen(argv[1], "r"); 
  int bs;
  sscanf(argv[2],"%d",&bs);
  bs = 1<<bs;
  unsigned char *teststr = new unsigned char [bs];
  fseek(fh,0L,2);
  long fl = ftell(fh);
  fseek(fh,0L,0);
  printf("{\n");
  printf("\"filelength\":%ld,\n\"blocksize\":%d,\n",fl,bs);
  printf("\"block\":[\n");
  long bn = fl/bs;
  long rest = fl%bs;
  for (long i = 0; i < bn; i++ ) {
    fread(teststr,1,bs,fh);
    sha1::calc(teststr, bs, hash);
    sha1::toHexString(hash, hexstring);
    string fwn = string(argv[3])+"/"+string(hexstring);
    FILE *fw = fopen(fwn.c_str(),"wb");
    fwrite(teststr,1,bs,fw);
    fclose(fw);
    printf("\"%s\",\n",hexstring);
  }
  fread(teststr,1,(int)rest,fh);
  sha1::calc(teststr,(int)rest, hash);
  sha1::toHexString(hash, hexstring);
  string fwn = string(argv[3])+"/"+string(hexstring);
  FILE *fw = fopen(fwn.c_str(),"wb");
  fwrite(teststr,1,(int)rest,fw);
  fclose(fw);
  printf("\"%s\"\n]\n}\n",hexstring);
  fclose(fh);
  return (0);
}
