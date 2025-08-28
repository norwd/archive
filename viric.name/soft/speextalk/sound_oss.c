/***************************************************************************
 * Speextalk
 * (C) Nicolas George - 2005-07-24
 * This OSS module (C) Lluís Batlle - 2007-08-26
 * This code is distributed under the terms of the GNU GPL.
 * sound_oss.c: OSS interface
 ***************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <alloca.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/soundcard.h> /* My linux had this file in sys/ */
#include <sys/ioctl.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "speextalk.h"

static int rec_fd;
static int play_fd;

/*
 * Dies printing the OSS error message.
 */
static void
oss_fatal(const char *msg)
{
    const char *t;

    t = strerror(errno);
    fprintf(stderr, "%s: %s\n", msg, t);
    exit(1);
}

/*
 * Opens a PCM stream on the device name for recording or playing according
 * the the boolean rec. Dies on failure. Sample rate must be exact.
 */
int
setup_pcm(const char *name, int rec, int sample_rate, int channels)
{
    short endian = 0x1234;
    int fd;
    int res;
    const char defaultdevice[] = "/dev/audio";

    if (strcmp(name, "default") == 0)
        name = defaultdevice;

    pthread_mutex_lock(&global_mutex);
    if (rec)
        fd = open(name, O_RDONLY);
    else
        fd = open(name, O_WRONLY | O_NONBLOCK);
    if (fd == -1)
        oss_fatal(rec ? "open(capture)" : "open(playback)");
    pthread_mutex_unlock(&global_mutex);

    if(sizeof(endian) == 2 &&
	((unsigned char *)&endian)[0] == 0x12 &&
	((unsigned char *)&endian)[1] == 0x34) {
        int format = AFMT_S16_BE;
        res = ioctl(fd, SNDCTL_DSP_SETFMT, &format);
        if (res == -1)
            oss_fatal("SNDCTL_DSP_SETFMT");
    } else if(sizeof(endian) == 2 &&
	((unsigned char *)&endian)[0] == 0x34 &&
	((unsigned char *)&endian)[1] == 0x12) {
        int format = AFMT_S16_LE;
        res = ioctl(fd, SNDCTL_DSP_SETFMT, &format);
        if (res == -1)
            oss_fatal("SNDCTL_DSP_SETFMT");
    } else {
	fprintf(stderr, "Unsupported endianness\n");
	exit(1);
    }

    res = ioctl(fd, SNDCTL_DSP_CHANNELS, &channels);
    if (res == -1)
        oss_fatal("SNDCTL_DSP_CHANNELS");
    res = ioctl(fd, SNDCTL_DSP_SPEED, &sample_rate);
    if (res == -1)
        oss_fatal("SNDCTL_DSP_SPEED");
    return(fd);
}

/*
 * Opens the recording PCM.
 */
void
prepare_recording(int sample_rate, int channels)
{
    rec_fd = setup_pcm(capture_device, 1, sample_rate, channels);
}

/*
 * Opens the playing PCM.
 */
void
prepare_playing(int sample_rate, int channels)
{
    play_fd = setup_pcm(playback_device, 0, sample_rate, channels);
}

#if 0
Useful for measuring data throughput.
static int measure(int count)
{
    static int total = 0;
    struct timeval tv;
    static int last_sec;

    total += count;
    gettimeofday(&tv, 0);
    if (last_sec != tv.tv_sec)
    {
        printf("record rate: %i/s\n", total);
        total = 0;
    }

    last_sec = tv.tv_sec;
}
#endif

/*
 * Reads some samples from the recording PCM. Retries on recoverable errors.
 * Dies on fatal errors. Returns the number of samples read. Blocks.
 * Note: this API is not yet specified for multi-channels streams.
 */
int
read_samples(short *buf, int buf_size)
{
    int n;

    while(1) {
        if((n = read(rec_fd, buf, buf_size*(sizeof(*buf)))) < 0) {
            if (n == -1 && errno == EAGAIN)
                return 0;
            oss_fatal("read");
        }
        return(n/(sizeof(*buf)));
    }
}

/*
 * Plays some samples on the playing PCM. Retries on recoverable errors.
 * Dies on fatal errors. Returns the number of samples written. Blocks.
 * Note: this API is not yet specified for multi-channels streams.
 */
int
play_samples(short *buf, int buf_size)
{
    int n;

    while(1) {
        if((n = write(play_fd, buf, buf_size*sizeof(*buf))) < 0) {
            oss_fatal("write");
        }
        return(n/(sizeof(*buf)));
    }
}
