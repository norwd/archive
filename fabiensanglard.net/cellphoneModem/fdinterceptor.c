/*
 *  fdinterceptor.h
 *  fdinterceptor
 *
 *  Created by fabien sanglard on 10-05-12.
 *  Copyright 2010 Memset Software All rights reserved.
 *
 */

#include <stdio.h>
#include <stdarg.h> 
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>

char pairInitialized=0;
FILE* fdToFILE[1024];
int lessThan[1024];

//Safer to use the mounted public land instead of system partition (/tmp).
char* commCenterLogFilename =  "/private/var/logs/commCenter.log" ;
char* baseBandOutLogFilename = "/private/var/logs/" ;

typedef struct interposer_s{
	void* new_func;
	void* origin_func;
} interposer_t;

int my_open(const char*, int , mode_t);
int my_close(int);
int my_read(  int  handle,  void  *buffer,  int  nbyte );
int my_write(  int  handle,  void  *buffer,  int  nbyte  );


static const interposer_t interposers[] __attribute__ ((section("__DATA, __interpose")))=
{
	{ (void*)my_open, (void*)open },
	{ (void*)my_close, (void*)close},
	{ (void*)my_read, (void*)read},
	{ (void*)my_write, (void*)write},
};

void traceBaseband(FILE* f,char* string,  ...)
{
	va_list vl; 
	va_start(vl,string); 
	vfprintf(f,string, vl);
	va_end(vl);
	
	fflush(f);
}

FILE* traceFile;
int fd_baseband=0;
void traceCommCenter(char* string, ...)
{
	if (!traceFile)
		 traceFile = fopen(commCenterLogFilename, "wt");

	
	va_list vl; 
	va_start(vl,string); 
	vfprintf(traceFile,string, vl);
	va_end(vl);
	
	fflush(traceFile);
}

char* afterLastSlash(char* string)
{
	int length ;
	char* cursor;
	
	if (!string)
		return 0;
	
	length = strlen(string);
	
	cursor = &string[length-1];
	
	while (cursor != string-1) 
	{
		if (*cursor == '/')
			return cursor;
		cursor--;
	}
	
	return 0;
}

int getFirstCRIndex(void* string, int nbyte)
{
	int index;
	char* buffer = (char*)string;
	
	
	index =  1 ;
	while (index < nbyte)
	{
		if (buffer[index] == 0xD)
			return index;
		
		index++;
	}
	
	return nbyte;
}

//#define trace printf 
char tmpPath[1024];
int my_open(const char* path, int flags, mode_t mode)
{
	char* terminalName; 
	
	if (!pairInitialized)
	{
		pairInitialized=1;
		memset( fdToFILE, 0, sizeof(fdToFILE));

	}
	
	int ret = open(path,flags,mode);
	traceCommCenter("call open(%s,%x,%x)\n",path,flags,mode);
	
	if (ret != 0 && (!strncmp("/dev/dlci.h5-baseband.",path,22)||   // 2G
					 !strncmp("/dev/dlci.spi­baseband.",path,22)		// 3G
					 )
	{
		traceCommCenter("Captured'%s'\n",path);
		if (fdToFILE[ret] == 0)
		{
			terminalName = afterLastSlash((char*)path);
			tmpPath[0] = '\0';
			strcat(tmpPath,baseBandOutLogFilename);
			strcat(tmpPath,terminalName+1);
			fdToFILE[ret] = fopen(tmpPath, "wt");
			traceCommCenter("Captured '%s', created log %s and fdToFile[%d] = %d\n",path,tmpPath,ret,fdToFILE[ret]);
		}
	}
	
	if (!strcmp(path, "/dev/mux.h5-baseband"))
	{
		fd_baseband = ret;
	}
	
	return ret;
}

int my_close(int d)
{
	int ret = close(d);
	//traceCommCenter("--> %d = close(%d)\n",ret,d);
	
	if (fdToFILE[d] != 0)
	{
		fclose(fdToFILE[d]);
		fdToFILE[d] = 0;
	}
	
	return ret ;
}

int my_read(  int  handle,  void  *buffer,  int  nbyte )
{
	int i;
	int lastCRindex;
	int ret = read(handle,buffer,nbyte);
	
	lastCRindex = getFirstCRIndex(buffer,nbyte);
	
	if (fd_baseband == handle)
	{
		traceCommCenter("[recv] :");
		for (i=0; i < lastCRindex; i++) 
				fputc(((char*)buffer)[i], traceFile);
		traceCommCenter("\n");
	}
	else if (fdToFILE[handle] != 0)
	{
		traceCommCenter("Detected READ on a traced termimal, tracing handle=%d with %d bytes to FILE*=%d\n",handle,nbyte,fdToFILE[handle]);
		traceBaseband(fdToFILE[handle] ,"[recv] ",nbyte,handle);
		fwrite(buffer, 1, lastCRindex, fdToFILE[handle]);
		traceBaseband(fdToFILE[handle] ,"\n");
		
		
	}
	return ret;
}


int my_write(  int  handle,  void  *buffer,  int  nbyte  )
{
	
	int ret;
	int i;
	
	if (fd_baseband == handle)
	{
		
		
		 traceCommCenter("[send] :");
		 for (i=0; i < nbyte; i++) 
				 fputc(((char*)buffer)[i], traceFile);
		 traceCommCenter("\n");
	}
	else if (fdToFILE[handle] != 0)
	{
		traceCommCenter("Detected WRITE on a traced termimal, tracing handle=%d with %d bytes to FILE*=%d\n",handle,nbyte,fdToFILE[handle]);
		traceBaseband(fdToFILE[handle] ,"[send] ");
		fwrite(buffer, 1, nbyte, fdToFILE[handle]);
		traceBaseband(fdToFILE[handle] ,"\n");
				
	}
	
	ret = write(handle,buffer,nbyte);
	
	return ret;
}
