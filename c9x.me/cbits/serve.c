/*% cc -Wall -o # %
 * serve [-n N] [-p PORT] [-h] file
 * One time use HTTP server.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>

enum {
	IBufLen = 4096,
	OBufLen = 4096,
};

char *fpath;
int lsock, rsock;
volatile sig_atomic_t nchld, done;

void sigchld(int sig)
{
	int wstat;
	pid_t pid;

	for (;;) {
		pid = waitpid(-1, &wstat, WNOHANG);
		if (pid != 0 && pid != -1) {
			nchld--;
			if (WIFEXITED(wstat))
				printf("[+] Servlet exited (%d)\n",
					WEXITSTATUS(wstat));
		} else
			return;
	}
}

void sigint(int sig)
{
	done = 1;
}

void serve(void)
{
	struct stat s;
	char ibuf[IBufLen], obuf[OBufLen];
	char *p, *base;
	int ilen, rd, wr, fd;
	off_t sent, fsize;

	ilen = read(rsock, ibuf, IBufLen - 1);
	if (ilen == -1) {
		perror("[!] read");
		exit(1);
	}
	ibuf[ilen] = 0;
	if (!strstr(ibuf, "\r\n\r\n")) {
		puts("[!] Request too long, denying connection.");
		exit(1);
	}

	/* write(1, ibuf, ilen); */

	if (stat(fpath, &s) == -1) {
		fprintf(stderr, "[!] Cannot stat '%s'.\n", fpath);
		exit(1);
	}
	fsize = s.st_size;

	base = strrchr(fpath, '/');
	if (!base)
		base = fpath;

	p = obuf + sprintf(obuf, "HTTP/1.1 200 Ok\r\n");
	p += sprintf(p, "Content-Length: %llu\r\n", (unsigned long long)fsize);
	p += sprintf(p, "Content-Disposition: attachement; filename=\"%s\"\r\n", base);
	p += sprintf(p, "\r\n");

	fd = open(fpath, O_RDONLY);
	if (fd == -1) {
		printf("[!] Cannot open '%s' for reading.\n", fpath);
		exit(1);
	}

	printf("[+] Sending data...\n");
	sent = 0;
	do {
		wr = write(rsock, obuf, p - obuf);
		if (wr < 0) {
			puts("[!] Cannot send data to client.");
			exit(1);
		}
		sent += wr;
		p -= wr;
		memmove(obuf, obuf + wr, p - obuf);
		rd = read(fd, p, OBufLen - (p - obuf));
		p += rd;
	} while (rd > 0 || p > obuf);

	printf("[+] Sent %lluKb to remote host, closing connection.\n",
		(unsigned long long)sent >> 10);
}

int main(int ac, char *av[])
{
	int a, c, on, op;
	struct sockaddr_in sin;
	socklen_t len;
	struct sigaction sa;

	on = -1;
	op = -1;
	for (a = 1; a < ac; a++)
		if (av[a][0] == '-' && (c = av[a][1]) && !av[a][2])
			switch (c) {
			case 'p':
			case 'n':
				if (++a >= ac)
					goto usage;
				*(c == 'n' ? &on : &op) = atoi(av[a]);
				break;
			default:
			case 'h':
			usage:
				puts("usage: serve [-n N] [-p PORT] [-h] FILE");
				exit(c != 'h');
			}
		else
			break;
	if (a >= ac)
		goto usage;
	fpath = av[a];

	signal(SIGCHLD, sigchld);

	len = sizeof sin;
	if ((lsock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("[!] socket");
		exit(1);
	}
	if (op != -1) {
		sin.sin_family = AF_INET;
		sin.sin_port = htons(op);
		sin.sin_addr.s_addr = INADDR_ANY;
		if (bind(lsock, (struct sockaddr *)&sin, len) == -1) {
			perror("[!] bind");
			exit(1);
		}
	}
	if (listen(lsock, 256) == -1) {
		perror("[!] listen");
		exit(1);
	}
	if (op == -1)
		getsockname(lsock, (struct sockaddr *)&sin, &len);
	printf("[+] Listening on port %d.\n", ntohs(sin.sin_port));

	sa.sa_handler = sigint;
	sa.sa_flags = SA_RESETHAND;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, 0);

	done = 0;
	while ((on < 0 || on--) && !done) {
		rsock = accept(lsock, (struct sockaddr *)&sin, &len);
		if (rsock == -1)
			continue;

		printf("[+] Got connection from %s:%d.\n",
			inet_ntoa(sin.sin_addr), ntohs(sin.sin_port));
		nchld++;
		if (fork() == 0) {
			serve();
			exit(0);
		}

		close(rsock);
	}

	puts("[+] Waiting for children.");
	while (nchld > 0)
		sleep(1);

	exit(0);
}
