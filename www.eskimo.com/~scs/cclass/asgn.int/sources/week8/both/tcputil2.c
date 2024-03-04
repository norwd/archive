#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int
socksetup(int port)
{
int sock;
int one = 1;
struct sockaddr_in server;

if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
	fprintf(stderr, "can't create socket: ");
	perror("");
	return -1;
	}

if(setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one)) < 0)
	{
	fprintf(stderr, "can't set SO_REUSEADDR: ");
	perror("");
	}

server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;	/* htons() ? */
server.sin_port = htons(port);

if(bind(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
	{
	fprintf(stderr, "can't bind: ");
	perror("");
	return -1;
	}

listen(sock, 5);

return sock;
}

int sockaccept(int sock, struct sockaddr_in **clientp)
{
static struct sockaddr_in client;
int len = sizeof(client);
int msgsock;

if((msgsock = accept(sock, (struct sockaddr *)&client, &len)) < 0)
	{
	fprintf(stderr, "accept error: ");
	perror("");
	return -1;
	}

if(clientp != NULL)
	*clientp = &client;

return msgsock;
}
