/*
 *  Sample code posted by Lawrence Kirby
 *  Date: Mon, 02 Mar 98 01:51:38 GMT
 *  Subject: temporarily reassigning stdout/stderr
 *  Message-ID: <28182@genesis.demon.co.uk>
 *
 *  (Nonportable: uses dup() and dup2() system calls for
 *  duplicating underlying file descriptors, which are
 *  present in Unix but not necessarily anywhere else.)
 */

#include <stdio.h>

main()
{
    int    fd;
    fpos_t pos;

    printf("stdout, ");

    fflush(stdout);
    fgetpos(stdout, &pos);
    fd = dup(fileno(stdout));
    freopen("stdout.out", "w", stdout);
    
    f();

    fflush(stdout);
    dup2(fd, fileno(stdout));
    close(fd);
    clearerr(stdout);
    fsetpos(stdout, &pos);        /* for C9X */

    printf("stdout again\n");
}

f()
{
printf("stdout in f()");
}
