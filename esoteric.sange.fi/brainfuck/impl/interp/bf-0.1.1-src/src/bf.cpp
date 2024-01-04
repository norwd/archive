/*
bf, Copyright (C) 1999 Jean-Baptiste M. Queru

This program is free software; you can redistribute it and/or 
modify it under the terms of the GNU General Public License 
as published by the Free Software Foundation; either version 2 
of the License, or (at your option) any later version. 

This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
GNU General Public License for more details. 

You should have received a copy of the GNU General Public License 
along with this program; if not, write to the Free Software 
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

Contact the author at:
Jean-Baptiste M. Queru, 1706 Marina Ct #B, San Mateo, CA 94403, USA
or by e-mail at : djaybee@cyberdude.com
*/

#include "bf.h"

#include <stdio.h>
#include <File.h>
#include <string.h>

#define CHUNK_SIZE 128

class chunk {
public:
	chunk() {
		memset(dat,0,sizeof(dat));
		prev=next=NULL;
	}
	int64 dat[CHUNK_SIZE];
	chunk*prev,*next;
};

class BFEngine {
public:
	BFEngine(char*,int);
	void Run();
	char*prog;
	int psize;
	int pc;
	chunk*cc;
	int cd;
};

int main(int argc,char** argv) {
	if (argc!=2) {
		printf("usage : %s <source name>\n",argv[0]);
		return -1;
	}
	BFile*f=new BFile(argv[1],B_READ_ONLY);
	if (f->InitCheck()!=B_OK) {
		printf("could not initialize BFile\n");
		return -1;
	}
	int size=f->Seek(0,SEEK_END);
	f->Seek(0,SEEK_SET);
	char*prog=new char[size];
	if (f->Read(prog,size)!=size) {
		printf("error while reading\n");
		return -1;
	}
	BFEngine(prog,size).Run();
}

BFEngine::BFEngine(char*p,int s) {
	prog=p;
	psize=s;
	pc=0;
	cc=new chunk;
	cd=0;
}

void BFEngine::Run() {
	do {
		switch(prog[pc]) {
			case '<' : {
				if (cd!=0) {
					cd--;
				} else {
					if (cc->prev==NULL) {
						cc->prev=new chunk;
						cc->prev->next=cc;
					}
					cc=cc->prev;		
					cd=CHUNK_SIZE-1;
				}
				break;
			}
			case '>' : {
				if (cd!=CHUNK_SIZE-1) {
					cd++;
				} else {
					if (cc->next==NULL) {
						cc->next=new chunk;
						cc->next->prev=cc;
					}
					cc=cc->next;		
					cd=0;
				}
				break;
			}
			case '.' : {
				if (cc->dat[cd]>=1&&cc->dat[cd]<=126) {
					putchar(cc->dat[cd]);
				} else {
					putchar('#');
				}
				break;
			}
			case ',' : {
				int c=getchar();
				if (c==EOF) {
					fprintf(stderr,"bf : no inputs - program terminated\n");
					exit(1);
				}
				cc->dat[cd]=c;
				break;
			}
			case '+' : {
				cc->dat[cd]++;
				break;
			}
			case '-' : {
				cc->dat[cd]--;
				break;
			}
			case '[' : {
				if (cc->dat[cd]==0) {
					int nlvl=0;
					pc++;
					while(pc<=psize && (nlvl!=0 || prog[pc]!=']')) {
						if (prog[pc]=='[') {
							nlvl++;
						}
						if (prog[pc]==']') {
							nlvl--;
						}
						pc++;
					}
				}
				break;
			}
			case ']' : {
				int nlvl=0;
				pc--;
				while(pc>=0 && (nlvl!=0 || prog[pc]!='[')) {
					if (prog[pc]==']') {
						nlvl++;
					}
					if (prog[pc]=='[') {
						nlvl--;
					}
					pc--;
				}
				pc--;
				break;
			}
		}
		fflush(stdout);
		pc++;
	} while (pc<psize);
}
