/*************************************************************************
* aidbf - Advanced Interpreter and Debugger for Brain Fuck               *
* Version 0.1                                                            *
* Copyright (C) 1999 by Klaus Reimer <kr@ailis.de>                       *
* ---------------------------------------------------------------------- *
* This is free software; you can redistribute it and/or modify it under  *
* the terms of the GNU General Public License as published by the Free   *
* Software Foundation; either version 2 of the License, or (at your      *
* option) any later version.                                             *
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <termios.h>

#ifndef DATASEGSIZE
#define DATASEGSIZE 8192
#endif

#ifndef MAJVER
#define MAJVER 0
#endif

#ifndef MINVER
#define MINVER 1
#endif

int iDataSegSize=DATASEGSIZE, iCodeSegSize;
int iDataIndex, iCodeIndex;
int iRandomize=0, iRandSeed, iInputMode=1;
int iKeep=0, bDebug=0, bBreak=0, bQuit=0;
int cBreakChar=0;
char *pDataSeg, *pCodeSeg;

char *itoa(unsigned int value, char *string, int radix, int len) {
  int z;
  char sTemp[255];
  
  strcpy(string,"");
  for (z=0;z<len;z++) {
    if ((value%radix)<10) {
      sprintf(sTemp,"%c%s",48+value%radix,string);
      strcpy(string,sTemp);
    }
    else {
      sprintf(sTemp,"%c%s",55+value%radix,string);
      strcpy(string,sTemp);
    }
    value=value/radix;
  }
  return string;
}

char rgetch(void) {
  struct termios newterm, oldterm;
  char c;

  if (iInputMode) {
    tcgetattr(fileno(stdin),&oldterm);
    newterm=oldterm;
    if (iInputMode==1)
      newterm.c_lflag &=~ICANON;
    else
      newterm.c_lflag &=~(ICANON|ECHO);
    tcsetattr(fileno(stdin),TCSANOW,&newterm);
  }
  c=getchar();
  if (iInputMode)
    tcsetattr(fileno(stdin),TCSANOW,&oldterm);
  return c;
}

void displayUsage(void) {
  printf("Usage: aidbf [OPTION]... FILE...\n");
  printf("Advanced Interpreter and Debugger for Brain Fuck.\n\n");
  printf("  -r, --randomize       Randomize data segment before execution\n");
  printf("  -R, --seed=SEED       Randomize data segment with SEED before execution\n");
  printf("  -m, --memory=BYTES    Size of data segment in bytes (Default: %i bytes)\n",DATASEGSIZE);
  printf("  -k, --keep            Keep data segment between program executions\n");
  printf("  -i, --inputmode=MODE  Input mode (0=Buffered, 1=Unbuffered (Default),\n");
  printf("                          2=Unbuffered noecho)\n");
  printf("  -d, --debug           Start debugger before execution\n");
  printf("  -D, --break=CMD       Start debugging at first occurence of command CMD\n");
  printf("  -h, --help            Display help and exit\n");
  printf("  -V, --version         Display version and exit\n");
  printf("\nWithout any options aidbf will execute all brain fuck programs specified.\n");
  printf("You can change some runtime behaviours using the options above. Use the\n");
  printf("randomize and seed options to random initialize the data segment before\n");
  printf("execution. Use the inputmode option to switch between various input modes.\n");
  printf("Finally you can use the debug and break options to debug your brain fuck\n");
  printf("programs. Use the help command in the debugger to get a short but sufficient\n");
  printf("usage help.\n");
  printf("\nReport bugs to <kr@ailis.de>.\n");
  printf("\n");
}

void displayVersion(void) {
  printf("aidbf %i.%i\n",MAJVER,MINVER);
  printf("Written by Klaus Reimer <kr@ailis.de>\n");
  printf("\nCopyright (C) 2000 by Klaus Reimer\n");
  printf("This is free software; you can redistribute it and/or modify it under\n");
  printf("the terms of the GNU General Public License as published by the Free\n");
  printf("Software Foundation; either version 2 of the License, or (at your\n");
  printf("option) any later version.\n");
}

void checkOptions(int argc, char *argv[]) {
  char cOpt;
  int iOptIndex;
  static struct option SOpts[]={
    {"randomize",0,NULL,'r'},
    {"seed",1,NULL,'R'},
    {"inputmode",1,NULL,'i'},
    {"memory",1,NULL,'m'},
    {"keep",0,NULL,'k'},
    {"help",0,NULL,'h'},
    {"version",0,NULL,'V'},
    {"debug",0,NULL,'d'},
    {"break",1,NULL,'D'},
    {NULL,0,NULL,0}
  };

  opterr=0;
  while((cOpt=getopt_long(argc,argv,"rR:m:ki:dD:hV",SOpts,&iOptIndex))!=-1) {
    switch(cOpt) {
      case 'r':
        iRandomize=1;
        break;
      case 'R':
        iRandomize=2;
        if (!optarg) {
          displayUsage();
          exit(1);
        }
        iRandSeed=atoi(optarg);
        break;
      case 'i':
        if (!optarg) {
          displayUsage();
          exit(1);
        }
        iInputMode=atoi(optarg);
        break;
      case 'm':
        if (!optarg) {
          displayUsage();
          exit(1);
        }
        iDataSegSize=atoi(optarg);
        break;
      case 'k':
        iKeep=1;
        break;
      case 'h':
        displayUsage();
        exit(0);
        break;
      case 'V':
        displayVersion();
        exit(0);
        break;
      case 'd':
        bDebug=1;
        bBreak=1;
        break;
      case 'D':
        if (!optarg) {
          displayUsage();
          exit(1);
        }
        cBreakChar=optarg[0];
        if (!strchr(",.<>+-[]",cBreakChar)) {
          displayUsage();
          exit(1);
        }
        break;
      default:
        displayUsage();
        exit(1);
    }
  }
}

void createDataSeg(void) {
  if (!(pDataSeg=(char *) malloc(iDataSegSize))) {
    fprintf(stderr,"Error: Can't allocate data segment\n");
    exit(1);
  }
}

void initDataSeg(void) {
  int iDataIndex;
  
  switch(iRandomize) {
    case 0:
      memset(pDataSeg,0,iDataSegSize);
      break;
    case 1:
      srand(getpid());
      for (iDataIndex=0;iDataIndex<iDataSegSize;iDataIndex++)
        pDataSeg[iDataIndex]=rand()%256;
      break;
    case 2:
      srand(iRandSeed);
      for (iDataIndex=0;iDataIndex<iDataSegSize;iDataIndex++)
        pDataSeg[iDataIndex]=rand()%256;
      break;
  }
}

void loadFile(char *sFilename) {
  FILE *hFile;
  int iIndex;
  
  if (!(hFile=fopen(sFilename,"rb"))) {
    fprintf(stderr,"Error: Can't open file '%s'\n",sFilename);
    exit(1);
  }
  fseek(hFile,0,SEEK_END);
  iCodeSegSize=ftell(hFile);
  fseek(hFile,0,SEEK_SET);
  if (!(pCodeSeg=(char *) malloc(iCodeSegSize))) {
    fprintf(stderr,"Error: Can't allocate code segment\n");
    exit(1);
  }
  if (!fread(pCodeSeg,1,iCodeSegSize,hFile)) {
    fprintf(stderr,"Error: Can't read file '%s'\n",sFilename);
    exit(1);
  }
  fclose(hFile);
  iIndex=0;
  while (iIndex<iCodeSegSize) {
    if (!strchr("<>+-,.[]#",pCodeSeg[iIndex])) {
      memmove(&pCodeSeg[iIndex],&pCodeSeg[iIndex+1],iCodeSegSize-iIndex);
      iCodeSegSize--;
    } else iIndex++;
  }
}

unsigned char convertChar(unsigned char cChar) {
  if (((cChar>=32) && (cChar<=128)) || (cChar>=160))
    return cChar;
  else
    return '.';
}

void displayDebugStatus(void) {
  char sIndex[9],sSegSize[9],sData[3];
  int iCount;
  
  fprintf(stderr,"\n------------------------------------------+------------------\n");
  fprintf(stderr,"Code %s/%s: ",itoa(iCodeIndex,sIndex,16,8),
    itoa(iCodeSegSize,sSegSize,16,8));
  for (iCount=-18;iCount<=18;iCount++) {
    if ((iCodeIndex+iCount>=0) && (iCodeIndex+iCount<iCodeSegSize))
      fprintf(stderr,"%c",pCodeSeg[iCodeIndex+iCount]);
    else
      fprintf(stderr," ");
  } 
  fprintf(stderr,"\nData %s/%s:",itoa(iDataIndex,sIndex,16,8),
    itoa(iDataSegSize,sSegSize,16,8));
  for (iCount=-4;iCount<=4;iCount++) {
    if ((iDataIndex+iCount>=0) && (iDataIndex+iCount<iDataSegSize))
      fprintf(stderr," %s",itoa(pDataSeg[iDataIndex+iCount],sData,16,2));
    else
      fprintf(stderr,"   ");
  }
  fprintf(stderr,"  ");
  for (iCount=-4;iCount<=4;iCount++) {
    if ((iDataIndex+iCount>=0) && (iDataIndex+iCount<iDataSegSize))
      fprintf(stderr,"%c",convertChar(pDataSeg[iDataIndex+iCount]));
    else
      fprintf(stderr," ");
  }
  fprintf(stderr," ");
  fprintf(stderr,"\n------------------------------------++------------------+----\n");
  fprintf(stderr,"Code Segment size: %i (%s)\n",iCodeSegSize,
    itoa(iCodeSegSize,sSegSize,16,8));
  fprintf(stderr,"Code Segment index: %i (%s)\n",iCodeIndex,
    itoa(iCodeIndex,sIndex,16,8));
  fprintf(stderr,"Data Segment size: %i (%s)\n",iCodeSegSize,
    itoa(iCodeSegSize,sSegSize,16,8));
  fprintf(stderr,"Data Segment index: %i (%s)\n",iDataIndex,
    itoa(iDataIndex,sIndex,16,8));
  fprintf(stderr,"Current Command: %c\n",pCodeSeg[iCodeIndex]);
  fprintf(stderr,"Current Value: %i (%s)\n",(unsigned char) pDataSeg[iDataIndex],
    itoa(pDataSeg[iDataIndex],sData,16,2));
  fprintf(stderr,"-------------------------------------------------------------\n");
}

int runDebugger(void) {
  char sCommand[256];
  int bResume=0, bQuit=0;

  bDebug=1;
  displayDebugStatus();  
  while (!bResume && !bQuit) {
    fprintf(stderr,"(h=help) > ");
    fgets(sCommand,255,stdin);
      switch(sCommand[0]) {
      case 'q':
        bQuit=1;
        break;
      case 'g':
        bResume=1;
        cBreakChar=0;
        bBreak=0;
        break;
      case 's':
        bResume=1;
        bBreak=1;
        break;
      case 'r':
        if (!iKeep) initDataSeg();
        iDataIndex=0;
        iCodeIndex=-1;
        bBreak=1;
        bResume=1;
        break;
      case '<':
      case '>':
      case '+':
      case '-':
      case '.':
      case ',':
      case '[':
      case ']':
        cBreakChar=sCommand[0];
        bResume=1;
        bBreak=0;
        break;
      case 'h':
      case 13:
      case 10:
        fprintf(stderr,"<>+-,.[]     Resume program to given command\n");
        fprintf(stderr,"s (step)     Execute next command\n");
        fprintf(stderr,"g (go)       Start or resume program\n");
        fprintf(stderr,"r (reset)    Reset program\n");
        fprintf(stderr,"h (help)     Display help\n");
        fprintf(stderr,"q (quit)     Quit program\n");
        break;
      default:
        fprintf(stderr,"Unknown command '%c'\n",sCommand[0]);
    }
  }
  return bQuit;  
}

void runApp(void) {
  int iLoopCount;
  
  iCodeIndex=0;
  iDataIndex=0;
  bQuit=0;
  while (!bQuit && (iCodeIndex<iCodeSegSize)) {
    if ((bBreak) || (pCodeSeg[iCodeIndex]==cBreakChar)) bQuit=runDebugger();
    switch (pCodeSeg[iCodeIndex]) {
      case '#': 
        if (bDebug) bQuit=runDebugger();
        break;
      case '<':
        if (iDataIndex)
          iDataIndex--;
        else {
          fprintf(stderr,"Runtime Error: Data Pointer out of segment\n");
          exit(1);
        }
        break;
      case '>':
        if (iDataIndex<iDataSegSize-1)
          iDataIndex++;
        else {
          fprintf(stderr,"Runtime Error: Data Pointer out of segment\n");
          exit(1);
        }
        break;
      case '+':
        pDataSeg[iDataIndex]++;
        break;
      case '-':
        pDataSeg[iDataIndex]--;
        break;
      case '.':
        putchar(pDataSeg[iDataIndex]);
        fflush(stdout);
        break;
      case ',':
        pDataSeg[iDataIndex]=rgetch();
        break;
      case '[':
        iLoopCount=1;
  
        if (!pDataSeg[iDataIndex]) {
          while ((pCodeSeg[iCodeIndex]!=']') || (iLoopCount)) {
            if (iCodeIndex<iCodeSegSize-1)
              iCodeIndex++;
            else {
              fprintf(stderr,"Runtime error: Code pointer out of segment\n");
              exit(1);
            }
            switch (pCodeSeg[iCodeIndex]) {
              case ']':
                iLoopCount--;
                break;
              case '[':
                iLoopCount++;
                break;
            }
          }
        }
        break;
      case ']':
        iLoopCount=1;
        if (pDataSeg[iDataIndex]) {
          while ((pCodeSeg[iCodeIndex]!='[') || (iLoopCount)) {
            if (iCodeIndex)
              iCodeIndex--;
            else {
              fprintf(stderr,"Runtime error: Code pointer out of segment\n");
              exit(1);
            }
            switch (pCodeSeg[iCodeIndex]) {
              case '[':
                iLoopCount--;
                break;
              case ']':
                iLoopCount++;
                break;
            }
          }
        }
        break;
    }
    iCodeIndex++;
  }
}

void freeCodeSeg(void) {
  free(pCodeSeg);
}

void freeDataSeg(void) {
  free(pDataSeg);
}

int main(int argc, char *argv[]) {
  int iFileCount;
  
  checkOptions(argc,argv);
  argc-=optind;
  argv+=optind;
  if (!argc) {
    displayUsage();
    exit(1);
  }
  createDataSeg();
  for (iFileCount=0;iFileCount<argc;iFileCount++) {    
    if (!iFileCount || !iKeep) initDataSeg();
    loadFile(argv[iFileCount]);
    runApp();
    freeCodeSeg();
  }
  freeDataSeg();
  return 0;
}
