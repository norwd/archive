/*************************************************************************
* BFA - Brain Fuck Assembler                                             *
* Version 0.2                                                            *
* Copyright (C) 1999 by Klaus Reimer <kr@ailis.de>                       *
* ---------------------------------------------------------------------- *
* bfa is free software; you can redistribute it and/or modify it under   *
* the terms of the GNU General Public License as published by the Free   *
* Software Foundation; either version 2 of the License, or (at your      *
* option) any later version.                                             *
*************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFERLEN 4096
#define CMDLEN 3
#define PARAMLEN 4096

#define ERRUNKNOWNCMD "Unknown command '%s' in line %i: %s"
#define ERRUNKNOWN "Unknown error in line %i: %s"
#define ERRSYNTAX "Syntax error in line %i: %s"
#define ERRINVALIDPARAM "Invalid parameter in line %i: %s"

#define CMDCOUNT 11
#define CMDMVL 0
#define CMDMVR 1
#define CMDADD 2
#define CMDSUB 3
#define CMDGET 4
#define CMDPUT 5
#define CMDLOB 6
#define CMDLOE 7
#define CMDSET 8
#define CMDCPL 9
#define CMDCPR 10

const char asCmds[CMDCOUNT][CMDLEN+1]={"MVL","MVR","ADD","SUB","GET",
  "PUT","LOB","LOE","SET","CPL","CPR"};

FILE *hOutFile;
int iLineLen=0;

char *trim(char *sDest, const char *sSource) {
  int iBegin;
  
  iBegin=0;
  while ((iBegin<strlen(sSource)) && (sSource[iBegin]==' ')) iBegin++;
  strcpy(sDest,&sSource[iBegin]);
  while ((sDest[strlen(sDest)-1]==' ')
    || (sDest[strlen(sDest)-1]==9)
    || (sDest[strlen(sDest)-1]==13)
    || (sDest[strlen(sDest)-1]==10)) sDest[strlen(sDest)-1]=0; 
  return sDest;
}

char *uncomment(char *sDest, const char *sSource) {
  char *cPos;
  int bInTxt, bSpecial, bFound, iPos;
  
  bInTxt=0;
  bFound=0;
  bSpecial=0;
  iPos=0;
  while (!bFound && (iPos<strlen(sSource))) {
    switch (sSource[iPos]) {
      case '\\':
        bSpecial=!bSpecial;
        iPos++;
        break;
      case '"':
        if (!bSpecial) bInTxt=!bInTxt;
        bSpecial=0;
        iPos++;
        break;
      case ';':
        if (!bInTxt) 
          bFound=1;
        else
          iPos++;
        break;
      default:
        bSpecial=0;
        iPos++;
    }
  }
  strncpy(sDest,sSource,iPos);
  sDest[iPos]=0;
  return sDest;
}

void bfwrite(const char *sCmds) {
  int iPos;
  
  for (iPos=0;iPos<strlen(sCmds);iPos++) {
    fprintf(hOutFile,"%c",sCmds[iPos]);
    iLineLen++;
    if (iLineLen==64) {
      fprintf(hOutFile,"\n");
      iLineLen=0;
    }
  }
}

void cmdMoveLeft(int iCount) {
  int z;
  
  for (z=0;z<iCount;z++) {
    bfwrite("<<");
  }
}

void cmdMoveRight(int iCount) {
  int z;
  for (z=0;z<iCount;z++) {
    bfwrite(">>");
  }
}

void cmdAdd(int iCount) {
  int iMul1, iMul2, iRest, iLength;
  int iMinMul1, iMinMul2, iMinRest, iMinLength;
  int z;
  
  iMinMul1=1;
  iMinMul2=iCount;
  iMinRest=0;
  iMinLength=iCount;
  for (iMul1=2;iMul1<iCount;iMul1++) {
    iMul2=iCount/iMul1;
    iRest=iCount%iMul1;
    iLength=7+iMul1+iMul2+iRest;
    if (iLength<iMinLength) {
      iMinMul1=iMul1;
      iMinMul2=iMul2;
      iMinRest=iRest;
      iMinLength=iLength;
    }
  }
  if (iMinMul1==1)
    for (z=0;z<iCount;z++) bfwrite("+");
  else {
    bfwrite(">");
    for (z=0;z<iMinMul1;z++) bfwrite("+");
    bfwrite("[<");
    for (z=0;z<iMinMul2;z++) bfwrite("+");
    bfwrite(">-]<");
    for (z=0;z<iMinRest;z++) bfwrite("+");
  }
}

void cmdSubtract(int iCount) {
  int iMul1, iMul2, iRest, iLength;
  int iMinMul1, iMinMul2, iMinRest, iMinLength;
  int z;
  
  iMinMul1=1;
  iMinMul2=iCount;
  iMinRest=0;
  iMinLength=iCount;
  for (iMul1=2;iMul1<iCount;iMul1++) {
    iMul2=iCount/iMul1;
    iRest=iCount%iMul1;
    iLength=7+iMul1+iMul2+iRest;
    if (iLength<iMinLength) {
      iMinMul1=iMul1;
      iMinMul2=iMul2;
      iMinRest=iRest;
      iMinLength=iLength;
    }
  }
  if (iMinMul1==1)
    for (z=0;z<iCount;z++) bfwrite("-");
  else {
    bfwrite(">");
    for (z=0;z<iMinMul1;z++) bfwrite("+");
    bfwrite("[<");
    for (z=0;z<iMinMul2;z++) bfwrite("-");
    bfwrite(">-]<");
    for (z=0;z<iMinRest;z++) bfwrite("-");
  }
}

void cmdPut(void) {
  bfwrite(".");
}

void cmdPutChar(const char cChar) {
  cmdAdd(cChar);
  cmdPut();
  cmdSubtract(cChar);
}

void cmdPutText(const char *sText) {
  int iPos, iOld;
  
  iOld=0;
  for (iPos=0;iPos<strlen(sText);iPos++) {
    if (sText[iPos]>iOld)
      cmdAdd(sText[iPos]-iOld);
    else if (sText[iPos]<iOld)
      cmdSubtract(iOld-sText[iPos]);
    cmdPut();
    iOld=sText[iPos];
  }
  cmdSubtract(iOld);
}

void cmdGet(const int iCount) {
  int iPos;
  
  for (iPos=0;iPos<iCount;iPos++) {
    if (iPos) cmdMoveRight(1);
    bfwrite(",");  
  }
  if (iCount>1) cmdMoveLeft(iCount-1);
}

void cmdLoopBegin(void) {
  bfwrite("[");
}

void cmdLoopEnd(void) {
  bfwrite("]");
}

void cmdSet(int iValue) {
  bfwrite("[-]");
  cmdAdd(iValue);
}

void cmdCopyLeft(int iCount) {
  int iPos;
  
  for (iPos=0;iPos<iCount;iPos++) {
    cmdMoveLeft(1);
    cmdSet(0);
  }
  for (iPos=0;iPos<iCount;iPos++) cmdMoveRight(1);
  cmdLoopBegin();
  for (iPos=0;iPos<iCount;iPos++) {
    cmdMoveLeft(1);
    cmdAdd(1);
  }
  for (iPos=0;iPos<iCount;iPos++) cmdMoveRight(1);
  cmdSubtract(1);
  cmdLoopEnd();
} 

void cmdCopyRight(int iCount) {
  int iPos;
  
  for (iPos=0;iPos<iCount;iPos++) {
    cmdMoveRight(1);
    cmdSet(0);
  }
  for (iPos=0;iPos<iCount;iPos++) cmdMoveLeft(1);
  cmdLoopBegin();
  for (iPos=0;iPos<iCount;iPos++) {
    cmdMoveRight(1);
    cmdAdd(1);
  }
  for (iPos=0;iPos<iCount;iPos++) cmdMoveLeft(1);
  cmdSubtract(1);
  cmdLoopEnd();
} 
 
int strparse(char *sDest, const char *sSource) {
  int bSpecial, bInText, iPos;
  
  bSpecial=0;
  bInText=0;
  strcpy(sDest,"");
  for (iPos=0;iPos<strlen(sSource);iPos++) {
    switch (sSource[iPos]) {
      case '"':
        if (!bSpecial)
          bInText=!bInText;
        else {
          if (bInText) strcat(sDest,"\"");
          bSpecial=0;
        }
        break;
      case '\\':
        if (!bSpecial) 
          bSpecial=!bSpecial;
        else
          if (bInText) strcat(sDest,"\\");
        break;
      default:
        if (bInText) {
          if (bSpecial) {
            switch (sSource[iPos]) {
              case 'n':
                strcat(sDest,"\n");
                break;
              case 'r':
                strcat(sDest,"\r");
                break;
            }
          }
          else {
            sDest[strlen(sDest)+1]=0;
            sDest[strlen(sDest)]=sSource[iPos];
          }
        }
        bSpecial=0;  
    }
  }
  return 0;
}

int parse(const char *sLine, const iLine) {
  char sCmd[CMDLEN+1], sParam[PARAMLEN+1], sText[PARAMLEN+1], *cPos;
  int iLen, iCmd, iParam;
  
  if (cPos=strchr(sLine,' ')) {
    iLen=((int) cPos)-((int) sLine);
    if (iLen>CMDLEN) iLen=CMDLEN;
    strncpy(sCmd,sLine,iLen);
    sCmd[iLen]=0;
    strncpy(sParam,cPos+1,PARAMLEN);
    sParam[PARAMLEN]=0;
  }
  else {
    strncpy(sCmd,sLine,CMDLEN);
    sCmd[CMDLEN]=0;
    strcpy(sParam,"");
  }
  iCmd=0;
  while ((iCmd<CMDCOUNT) && (strcmp(sCmd,asCmds[iCmd]))) iCmd++;
  if (iCmd>=CMDCOUNT) {
    fprintf(stderr,ERRUNKNOWNCMD"\n",sCmd,iLine,sLine);
    return 1;
  }
  if (strlen(sParam)) {
    if (sParam[0]=='"') {
      if (strparse(sText,sParam)) return 1;
      switch (iCmd) {
        case CMDPUT:
          cmdPutText(sText);
          break;
        default:
          fprintf(stderr,ERRINVALIDPARAM"\n",iLine,sLine);
          return 1;
      }
    }
    else {
      iParam=atoi(sParam);
      switch (iCmd) {
        case CMDMVL:
          cmdMoveLeft(iParam);
          break;
        case CMDMVR:
          cmdMoveRight(iParam);
          break;
        case CMDADD:
          cmdAdd(iParam);
          break;
        case CMDSUB:
          cmdSubtract(iParam);
          break;
        case CMDPUT:
          cmdPutChar(iParam);
          break;
        case CMDGET:
          cmdGet(iParam);
          break;
        case CMDSET:
          cmdSet(iParam);
          break;
        case CMDCPL:
          cmdCopyLeft(iParam);
          break;
        case CMDCPR:
          cmdCopyRight(iParam);
          break;
        default:
          fprintf(stderr,ERRINVALIDPARAM"\n",iLine,sLine);
          return 1;
      }          
    }
  }
  else {
    switch(iCmd) {
      case CMDMVL:
        cmdMoveLeft(1);
        break;
      case CMDMVR:
        cmdMoveRight(1);
        break;
      case CMDADD:
        cmdAdd(1);
        break;
      case CMDSUB:
        cmdSubtract(1);
        break;
      case CMDGET:
        cmdGet(1);
        break;
      case CMDPUT:
        cmdPut();
        break;
      case CMDLOB:
        cmdLoopBegin();
        break;
      case CMDLOE:
        cmdLoopEnd();
        break;
      case CMDSET:
        cmdSet(0);
        break;
      case CMDCPL:
        cmdCopyLeft(1);
        break;
      case CMDCPR:
        cmdCopyRight(1);
        break; 
      default:
        fprintf(stderr,ERRUNKNOWN"\n",iLine,sLine);
        return 1;
    }
  }
  return 0;
}

int main(int argc, char *argv[]) {
  FILE *hInFile;
  int bError, iLine;
  char sLine[BUFFERLEN+1], sLine2[BUFFERLEN+1];
  
  if (argc!=3) {
    printf("Syntax: %s <INFILE> <OUTFILE>\n",argv[0]);
    return 1;
  }
  if (!strcmp(argv[1],"-"))
    hInFile=stdin;
  else
    hInFile=fopen(argv[1],"rt");
  if (!hInFile) {
    fprintf(stderr,"Can't open input file.\n");
    return 1;
  }
  if (!strcmp(argv[2],"-"))
    hOutFile=stdout;
  else
    hOutFile=fopen(argv[2],"wt");
  if (!hOutFile) {
    fprintf(stderr,"Can't open output file.\n");
    return 1;
  }
  bError=0;
  iLine=1;
  while (!bError && fgets(sLine,BUFFERLEN,hInFile)) {
    uncomment(sLine2,sLine);
    trim(sLine,sLine2);
    if (strlen(sLine)) bError=parse(sLine,iLine);
    iLine++;
  }
  fclose(hInFile);
  fclose(hOutFile);
}
