The history of UTF-8 as told by Rob Pike
========================================

[Rob Pike](http://genius.cat-v.org/rob-pike) explains how [Ken
Thompson](http://genius.cat-v.org/ken-thompson/) invented [UTF-8](/plan_9/4th_edition/papers/utf) in one evening and how they
together built the first system-wide implementation in less than a week.


    Subject: UTF-8 history
    From: "Rob 'Commander' Pike" <r (at) google.com>
    Date: Wed, 30 Apr 2003 22:32:32 -0700 (Thu 06:32 BST)
    To: mkuhn (at) acm.org, henry (at) spsystems.net
    Cc: ken (at) entrisphere.com

    Looking around at some UTF-8 background, I see the same incorrect
    story being repeated over and over.  The incorrect version is:
        1. IBM designed UTF-8.
        2. Plan 9 implemented it.
    That's not true.  UTF-8 was designed, in front of my eyes, on a
    placemat in a New Jersey diner one night in September or so 1992.

    What happened was this.  We had used the original UTF from ISO 10646
    to make Plan 9 support 16-bit characters, but we hated it.  We were
    close to shipping the system when, late one afternoon, I received a
    call from some folks, I think at IBM - I remember them being in Austin
    - who were in an X/Open committee meeting.  They wanted Ken and me to
    vet their FSS/UTF design.  We understood why they were introducing a
    new design, and Ken and I suddenly realized there was an opportunity
    to use our experience to design a really good standard and get the
    X/Open guys to push it out.  We suggested this and the deal was, if we
    could do it fast, OK.  So we went to dinner, Ken figured out the
    bit-packing, and when we came back to the lab after dinner we called
    the X/Open guys and explained our scheme.  We mailed them an outline
    of our spec, and they replied saying that it was better than theirs (I
    don't believe I ever actually saw their proposal; I know I don't
    remember it) and how fast could we implement it?  I think this was a
    Wednesday night and we promised a complete running system by Monday,
    which I think was when their big vote was.

    So that night Ken wrote packing and unpacking code and I started
    tearing into the C and graphics libraries.  The next day all the code
    was done and we started converting the text files on the system
    itself.  By Friday some time Plan 9 was running, and only running,
    what would be called UTF-8.  We called X/Open and the rest, as they
    say, is slightly rewritten history.

    Why didn't we just use their FSS/UTF?  As I remember, it was because
    in that first phone call I sang out a list of desiderata for any such
    encoding, and FSS/UTF was lacking at least one - the ability to
    synchronize a byte stream picked up mid-run, with less that one
    character being consumed before synchronization.  Becuase that was
    lacking, we felt free - and were given freedom - to roll our own.

    I think the "IBM designed it, Plan 9 implemented it" story originates
    in RFC2279.  At the time, we were so happy UTF-8 was catching on we
    didn't say anything about the bungled history.  Neither of us is at
    the Labs any more, but I bet there's an e-mail thread in the archive
    there that would support our story and I might be able to get someone
    to dig it out.

    So, full kudos to the X/Open and IBM folks for making the opportunity
    happen and for pushing it forward, but Ken designed it with me
    cheering him on, whatever the history books say.

    -rob

    Date: Sat, 07 Jun 2003 18:44:05 -0700
    From: "Rob `Commander' Pike" <r@google.com>
    To: Markus Kuhn <Markus.Kuhn@cl.cam.ac.uk>
    cc: henry@spsystems.net, ken@entrisphere.com,
       Greger Leijonhufvud <greger@friherr.com>
    Subject: Re: UTF-8 history

    I asked Russ Cox to dig through the archives. I have attached his message.
    I think you'll agree it supports the story I sent earlier. The mail we
    sent to X/Open (I believe Ken did the editing and mailing of that document)
    includes a new desideratum #6 about discovering character boundaries.
    We'll never know how much the original X/Open proposal influenced us;
    the two proposals are very different but do share some characteristics.
    I don't remember looking at it in detail, but it was a long time ago.
    I very clearly remember Ken writing on the placemat and wished we had
    kept it!

    -rob

    From: Russ Cox <rsc@plan9.bell-labs.com>
    To: r@google.com
    Subject: utf digging
    Date-Sent: Saturday, June 07, 2003 7:46 PM -0400


    bootes's /sys/src/libc/port/rune.c changed from the
    division-heavy old utf on sep 4 1992.
    the version that made it into the dump
    is dated 19:51:55.  it was commented
    the next day but otherwise remained unchanged
    until nov 14 1996, when runelen was sped up by
    inspecting the rune explicitly rather than
    using runetochar's return value.  may 26 2001
    was the next and last change, to add runenlen.

    here are some mails from your mail boxes
    that turn up by grepping for utf.  the first
    refers to utf.c, which is a copy of a wctomb and mbtowc
    that handle the full 6-byte utf-8 encoding of 32-bit runes.
    it's quite ugly, with all the logic in control flow.
    i assume it became the code in the proposal
    as a result of that first mail.

    in /usr/ken/utf/xutf i found a copy of what
    appears to be the original not-self-synchronizing
    encoding proposal, with the utf-8 scheme tacked
    onto the end (starting at "We define 7 byte types").
    that's also below.  the version below is the first,
    dated sep 2 23:44:10.  it went through a number of
    edits to become the second mail below by the
    morning of Sep 8.

    the mail log shows that second mail going out
    as well as taking a while to come back to ken.

    helix: Sep  8 03:22:13: ken: upas/sendmail: remote inet!xopen.co.uk!xojig 
    >From ken Tue Sep  8 03:22:07 EDT 1992 (xojig@xopen.co.uk) 6833
    helix: Sep  8 03:22:13: ken: upas/sendmail: delivered rob From ken Tue Sep 
    8 03:22:07 EDT 1992 6833
    helix: Sep  8 03:22:16: ken: upas/sendmail: remote pyxis!andrew From ken 
    Tue Sep  8 03:22:07 EDT 1992 (andrew) 6833
    helix: Sep  8 03:22:19: ken: upas/sendmail: remote coma!dmr From ken Tue 
    Sep  8 03:22:07 EDT 1992 (dmr) 6833
    helix: Sep  8 03:25:52: ken: upas/sendmail: delivered rob From ken Tue Sep 
    8 03:24:58 EDT 1992 141
    helix: Sep  8 03:36:13: ken: upas/sendmail: delivered ken From ken Tue Sep 
    8 03:36:12 EDT 1992 6833

    enjoy.



    >From ken Fri Sep  4 03:37:39 EDT 1992
    you might want to look at
        /usr/ken/utf/utf.c
    and see if you can make it prettier.

    >From ken Tue Sep  8 03:22:07 EDT 1992
    Here is our modified FSS-UTF proposal.  The words are the same as on
    the previous proposal.  My apologies to the author.  The code has been
    tested to some degree and should be pretty good shape.  We have
    converted Plan 9 to use this encoding and are about to issue a
    distribution to an initial set of university users.

    File System Safe Universal Character Set Transformation Format (FSS-UTF)
    --------------------------------------------------------------------------

    With the approval of ISO/IEC 10646 (Unicode) as an international
    standard and the anticipated wide spread use of this universal coded
    character set (UCS), it is necessary for historically ASCII based
    operating systems to devise ways to cope with representation and
    handling of the large number of characters that are possible to be
    encoded by this new standard.

    There are several challenges presented by UCS which must be dealt with
    by historical operating systems and the C-language programming
    environment.  The most significant of these challenges is the encoding
    scheme used by UCS. More precisely, the challenge is the marrying of
    the UCS standard with existing programming languages and existing
    operating systems and utilities.

    The challenges of the programming languages and the UCS standard are
    being dealt with by other activities in the industry.  However, we are
    still faced with the handling of UCS by historical operating systems
    and utilities.  Prominent among the operating system UCS handling
    concerns is the representation of the data within the file system.  An
    underlying assumption is that there is an absolute requirement to
    maintain the existing operating system software investment while at
    the same time taking advantage of the use the large number of
    characters provided by the UCS.

    UCS provides the capability to encode multi-lingual text within a
    single coded character set.  However, UCS and its UTF variant do not
    protect null bytes and/or the ASCII slash ("/") making these character
    encodings incompatible with existing Unix implementations.  The
    following proposal provides a Unix compatible transformation format of
    UCS such that Unix systems can support multi-lingual text in a single
    encoding.  This transformation format encoding is intended to be used
    as a file code.  This transformation format encoding of UCS is
    intended as an intermediate step towards full UCS support.  However,
    since nearly all Unix implementations face the same obstacles in
    supporting UCS, this proposal is intended to provide a common and
    compatible encoding during this transition stage.


    Goal/Objective
    --------------

    With the assumption that most, if not all, of the issues surrounding
    the handling and storing of UCS in historical operating system file
    systems are understood, the objective is to define a UCS
    transformation format which also meets the requirement of being usable
    on a historical operating system file system in a non-disruptive
    manner.  The intent is that UCS will be the process code for the
    transformation format, which is usable as a file code.

    Criteria for the Transformation Format
    --------------------------------------

    Below are the guidelines that were used in defining the UCS
    transformation format:

        1) Compatibility with historical file systems:

        Historical file systems disallow the null byte and the ASCII
        slash character as a part of the file name.

        2) Compatibility with existing programs:

        The existing model for multibyte processing is that ASCII does
        not occur anywhere in a multibyte encoding.  There should be
        no ASCII code values for any part of a transformation format
        representation of a character that was not in the ASCII
        character set in the UCS representation of the character.

        3) Ease of conversion from/to UCS.

        4) The first byte should indicate the number of bytes to
        follow in a multibyte sequence.

        5) The transformation format should not be extravagant in
        terms of number of bytes used for encoding.

        6) It should be possible to find the start of a character
        efficiently starting from an arbitrary location in a byte
        stream.


    Proposed FSS-UTF
    ----------------

    The proposed UCS transformation format encodes UCS values in the range
    [0,0x7fffffff] using multibyte characters of lengths 1, 2, 3, 4, 5,
    and 6 bytes.  For all encodings of more than one byte, the initial
    byte determines the number of bytes used and the high-order bit in
    each byte is set.  Every byte that does not start 10xxxxxx is the
    start of a UCS character sequence.

    An easy way to remember this transformation format is to note that the
    number of high-order 1's in the first byte signifies the number of
    bytes in the multibyte character:

       Bits  Hex Min  Hex Max  Byte Sequence in Binary
    1    7  00000000 0000007f 0vvvvvvv
    2   11  00000080 000007FF 110vvvvv 10vvvvvv
    3   16  00000800 0000FFFF 1110vvvv 10vvvvvv 10vvvvvv
    4   21  00010000 001FFFFF 11110vvv 10vvvvvv 10vvvvvv 10vvvvvv
    5   26  00200000 03FFFFFF 111110vv 10vvvvvv 10vvvvvv 10vvvvvv 10vvvvvv
    6   31  04000000 7FFFFFFF 1111110v 10vvvvvv 10vvvvvv 10vvvvvv 10vvvvvv 
    10vvvvvv

    The UCS value is just the concatenation of the v bits in the multibyte
    encoding.  When there are multiple ways to encode a value, for example
    UCS 0, only the shortest encoding is legal.

    Below are sample implementations of the C standard wctomb() and
    mbtowc() functions which demonstrate the algorithms for converting
    from UCS to the transformation format and converting from the
    transformation format to UCS. The sample implementations include error
    checks, some of which may not be necessary for conformance:

    typedef
    struct
    {
        int	cmask;
        int	cval;
        int	shift;
        long	lmask;
        long	lval;
    } Tab;

    static
    Tab	tab[] =
    {
        0x80,	0x00,	0*6,	0x7F,		0,		/* 1 byte sequence */
        0xE0,	0xC0,	1*6,	0x7FF,		0x80,		/* 2 byte sequence */
        0xF0,	0xE0,	2*6,	0xFFFF,		0x800,		/* 3 byte sequence */
        0xF8,	0xF0,	3*6,	0x1FFFFF,	0x10000,	/* 4 byte sequence */
        0xFC,	0xF8,	4*6,	0x3FFFFFF,	0x200000,	/* 5 byte sequence */
        0xFE,	0xFC,	5*6,	0x7FFFFFFF,	0x4000000,	/* 6 byte sequence */
        0,							/* end of table */
    };

    int
    mbtowc(wchar_t *p, char *s, size_t n)
    {
        long l;
        int c0, c, nc;
        Tab *t;

        if(s == 0)
            return 0;

        nc = 0;
        if(n <= nc)
            return -1;
        c0 = *s & 0xff;
        l = c0;
        for(t=tab; t->cmask; t++) {
            nc++;
            if((c0 & t->cmask) == t->cval) {
                l &= t->lmask;
                if(l < t->lval)
                    return -1;
                *p = l;
                return nc;
            }
            if(n <= nc)
                return -1;
            s++;
            c = (*s ^ 0x80) & 0xFF;
            if(c & 0xC0)
                return -1;
            l = (l<<6) | c;
        }
        return -1;
    }

    int
    wctomb(char *s, wchar_t wc)
    {
        long l;
        int c, nc;
        Tab *t;

        if(s == 0)
            return 0;

        l = wc;
        nc = 0;
        for(t=tab; t->cmask; t++) {
            nc++;
            if(l <= t->lmask) {
                c = t->shift;
                *s = t->cval | (l>>c);
                while(c > 0) {
                    c -= 6;
                    s++;
                    *s = 0x80 | ((l>>c) & 0x3F);
                }
                return nc;
            }
        }
        return -1;
    }

    >From ken Tue Sep  8 03:24:58 EDT 1992
    i mailed it out, but it went into a black hole.
    i didnt get my copy. it must be hung up on the
    internat address with coma down or something.

    >From ken Tue Sep  8 03:42:43 EDT 1992
    i finally got my copy.



    --- /usr/ken/utf/xutf from dump of Sep 2 1992 ---

     File System Safe Universal Character Set Transformation Format (FSS-UTF)
     --------------------------------------------------------------------------

     With the approval of ISO/IEC 10646 (Unicode) as an international
     standard and the anticipated wide spread use of this universal coded
     character set (UCS), it is necessary for historically ASCII based
     operating systems to devise ways to cope with representation and
     handling of the large number of characters that are possible to be
     encoded by this new standard.

     There are several challenges presented by UCS which must be dealt with
     by historical operating systems and the C-language programming
     environment. The most significant of these challenges is the encoding
     scheme used by UCS.  More precisely, the challenge is the marrying of
     the UCS standard with existing programming languages and existing
     operating systems and utilities.

     The challenges of the programming languages and the UCS standard are
     being dealt with by other activities in the industry.	However, we are
     still faced with the handling of UCS by historical operating systems and
     utilities. Prominent among the operating system UCS handling concerns is
     the representation of the data within the file system. An underlying
     assumption is that there is an absolute requirement to maintain the
     existing operating system software investment while at the same time
     taking advantage of the use the large number of characters provided by
     the UCS.

     UCS provides the capability to encode multi-lingual text within a single
     coded character set.  However, UCS and its UTF variant do not protect
     null bytes and/or the ASCII slash ("/") making these character encodings
     incompatible with existing Unix implementations.  The following proposal
     provides a Unix compatible transformation format of UCS such that Unix
     systems can support multi-lingual text in a single encoding.  This
     transformation format encoding is intended to be used as a file code.
     This transformation format encoding of UCS is intended as an
     intermediate step towards full UCS support.  However, since nearly all
     Unix implementations face the same obstacles in supporting UCS, this
     proposal is intended to provide a common and compatible encoding during
     this transition stage.


     Goal/Objective
     --------------

     With the assumption that most, if not all, of the issues surrounding the
     handling and storing of UCS in historical operating system file systems
     are understood, the objective is to define a UCS transformation format
     which also meets the requirement of being usable on a historical
     operating system file system in a non-disruptive manner. The intent is
     that UCS will be the process code for the transformation format, which
     is usable as a file code.

     Criteria for the Transformation Format
     --------------------------------------

     Below are the guidelines that were used in defining the UCS
     transformation format:

         1) Compatibility with historical file systems:

        Historical file systems disallow the null byte and the ASCII
        slash character as a part of the file name.

         2) Compatibility with existing programs:

        The existing model for multibyte processing is that ASCII does
        not occur anywhere in a multibyte encoding.  There should be no
        ASCII code values for any part of a transformation format
        representation of a character that was not in the ASCII character
        set in the UCS representation of the character.

         3) Ease of conversion from/to UCS.

         4) The first byte should indicate the number of bytes to follow in a
        multibyte sequence.

         5) The transformation format should not be extravagant in terms of
        number of bytes used for encoding.


     Proposed FSS-UTF
     ----------------

     The proposed UCS transformation format encodes UCS values in the range
     [0,0x7fffffff] using multibyte characters of lengths 1, 2, 3, 4, and 5
     bytes.  For all encodings of more than one byte, the initial byte
     determines the number of bytes used and the high-order bit in each byte
     is set.

     An easy way to remember this transformation format is to note that the
     number of high-order 1's in the first byte is the same as the number of
     subsequent bytes in the multibyte character:

        Bits  Hex Min  Hex Max         Byte Sequence in Binary
     1    7  00000000 0000007f 0zzzzzzz
     2   13  00000080 0000207f 10zzzzzz 1yyyyyyy
     3   19  00002080 0008207f 110zzzzz 1yyyyyyy 1xxxxxxx
     4   25  00082080 0208207f 1110zzzz 1yyyyyyy 1xxxxxxx 1wwwwwww
     5   31  02082080 7fffffff 11110zzz 1yyyyyyy 1xxxxxxx 1wwwwwww 1vvvvvvv

     The bits included in the byte sequence is biased by the minimum value
     so that if all the z's, y's, x's, w's, and v's are zero, the minimum
     value is represented.	In the byte sequences, the lowest-order encoded
     bits are in the last byte; the high-order bits (the z's) are in the
     first byte.

     This transformation format uses the byte values in the entire range of
     0x80 to 0xff, inclusive, as part of multibyte sequences.  Given the
     assumption that at most there are seven (7) useful bits per byte, this
     transformation format is close to minimal in its number of bytes used.

     Below are sample implementations of the C standard wctomb() and
     mbtowc() functions which demonstrate the algorithms for converting from
     UCS to the transformation format and converting from the transformation
     format to UCS.  The sample implementations include error checks, some
     of which may not be necessary for conformance:

    #define OFF1   0x0000080
    #define OFF2   0x0002080
    #define OFF3   0x0082080
    #define OFF4   0x2082080

    int wctomb(char *s, wchar_t wc)
    {
           if (s == 0)
               return 0;       /* no shift states */
    #ifdef wchar_t_is_signed
           if (wc < 0)
               goto bad;
    #endif
           if (wc <= 0x7f)         /* fits in 7 bits */
           {
               s[0] = wc;
               return 1;
           }
           if (wc <= 0x1fff + OFF1)        /* fits in 13 bits */
           {
               wc -= OFF1;
               s[0] = 0x80 | (wc >> 7);
               s[1] = 0x80 | (wc & 0x7f);
               return 2;
           }
           if (wc <= 0x7ffff + OFF2)       /* fits in 19 bits */
           {
               wc -= OFF2;
               s[0] = 0xc0 | (wc >> 14);
               s[1] = 0x80 | ((wc >> 7) & 0x7f);
               s[2] = 0x80 | (wc & 0x7f);
               return 3;
           }
           if (wc <= 0x1ffffff + OFF3)     /* fits in 25 bits */
           {
               wc -= OFF3;
               s[0] = 0xe0 | (wc >> 21);
               s[1] = 0x80 | ((wc >> 14) & 0x7f);
               s[2] = 0x80 | ((wc >> 7) & 0x7f);
               s[3] = 0x80 | (wc & 0x7f);
               return 4;
           }
    #if !defined(wchar_t_is_signed) || defined(wchar_t_is_more_than_32_bits)
           if (wc > 0x7fffffff)
               goto bad;
    #endif
           wc -= OFF4;
           s[0] = 0xf0 | (wc >> 28);
           s[1] = 0x80 | ((wc >> 21) & 0x7f);
           s[2] = 0x80 | ((wc >> 14) & 0x7f);
           s[3] = 0x80 | ((wc >> 7) & 0x7f);
           s[4] = 0x80 | (wc & 0x7f);
           return 5;
    bad:;
           errno = EILSEQ;
           return -1;
    }


    int mbtowc(wchar_t *p, const char *s, size_t n)
    {
           unsigned char *uc;      /* so that all bytes are nonnegative */

           if ((uc = (unsigned char *)s) == 0)
               return 0;               /* no shift states */
           if (n == 0)
               return -1;
           if ((*p = uc[0]) < 0x80)
               return uc[0] != '\0';   /* return 0 for '\0', else 1 */
           if (uc[0] < 0xc0)
           {
               if (n < 2)
                   return -1;
               if (uc[1] < 0x80)
                   goto bad;
               *p &= 0x3f;
               *p <<= 7;
               *p |= uc[1] & 0x7f;
               *p += OFF1;
               return 2;
           }
           if (uc[0] < 0xe0)
           {
               if (n < 3)
                   return -1;
               if (uc[1] < 0x80 || uc[2] < 0x80)
                   goto bad;
               *p &= 0x1f;
               *p <<= 14;
               *p |= (uc[1] & 0x7f) << 7;
               *p |= uc[2] & 0x7f;
               *p += OFF2;
               return 3;
           }
           if (uc[0] < 0xf0)
           {
               if (n < 4)
                   return -1;
               if (uc[1] < 0x80 || uc[2] < 0x80 || uc[3] < 0x80)
                   goto bad;
               *p &= 0x0f;
               *p <<= 21;
               *p |= (uc[1] & 0x7f) << 14;
               *p |= (uc[2] & 0x7f) << 7;
               *p |= uc[3] & 0x7f;
               *p += OFF3;
               return 4;
           }
           if (uc[0] < 0xf8)
           {
               if (n < 5)
                   return -1;
               if (uc[1] < 0x80 || uc[2] < 0x80 || uc[3] < 0x80 || uc[4] < 0x80)
                   goto bad;
               *p &= 0x07;
               *p <<= 28;
               *p |= (uc[1] & 0x7f) << 21;
               *p |= (uc[2] & 0x7f) << 14;
               *p |= (uc[3] & 0x7f) << 7;
               *p |= uc[4] & 0x7f;
               if (((*p += OFF4) & ~(wchar_t)0x7fffffff) == 0)
                   return 5;
           }
    bad:;
           errno = EILSEQ;
           return -1;
    }

    We define 7 byte types:
    T0	0xxxxxxx	7 free bits
    Tx	10xxxxxx	6 free bits
    T1	110xxxxx	5 free bits
    T2	1110xxxx	4 free bits
    T3	11110xxx	3 free bits
    T4	111110xx	2 free bits
    T5	111111xx	2 free bits

    Encoding is as follows.
    >From hex	Thru hex	Sequence		Bits
    00000000	0000007f	T0			7
    00000080	000007FF	T1 Tx			11
    00000800	0000FFFF	T2 Tx Tx		16
    00010000	001FFFFF	T3 Tx Tx Tx		21
    00200000	03FFFFFF	T4 Tx Tx Tx Tx		26
    04000000	FFFFFFFF	T5 Tx Tx Tx Tx Tx	32

    Some notes:

    1. The 2 byte sequence has 2^11 codes, yet only 2^11-2^7
    are allowed. The codes in the range 0-7f are illegal.
    I think this is preferable to a pile of magic additive
    constants for no real benefit. Similar comment applies
    to all of the longer sequences.

    2. The 4, 5, and 6 byte sequences are only there for
    political reasons. I would prefer to delete these.

    3. The 6 byte sequence covers 32 bits, the FSS-UTF
    proposal only covers 31.

    4. All of the sequences synchronize on any byte that is
    not a Tx byte.

