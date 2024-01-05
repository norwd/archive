


bfa(1)                 Brain Fuck Assembler                bfa(1)


NNAAMMEE
       bfa - Brain Fuck Assembler

SSYYNNOOPPSSIISS
       bbffaa IINNFFIILLEE OOUUTTFFIILLEE

DDEESSCCRRIIPPTTIIOONN
       bbffaa  is  an assembler for the minimalized programming lan-
       guage Brain Fuck. It  translates  a  better  readable  BFA
       source  code  to  native  absolutely unreadable Brain Fuck
       code.  The produced code can be executed with a Brain Fuck
       Interpreter  like bbffii from Urban Mueller, or directly on a
       system providing a Brain Fuck processor.

       The first argument IINNFFIILLEE is the  file  name  of  the  BFA
       source code.  This file will be translated to native Brain
       Fuck code and written to the  file  given  by  the  second
       argument.   Use  --  instead  of a filename to use ssttddiinn or
       ssttddoouutt.

EEXXAAMMPPLLEESS
       bbffaa oorrddeerr..bbffaa oorrddeerr..bb
              Read BFA code from oorrddeerr..bbffaa translate it to  Brain
              Fuck code and write it to oorrddeerr..bb.

       bbffaa -- oorrddeerr..bb
              Read BFA code from ssttddiinn translate it to Brain Fuck
              code and write it to oorrddeerr..bb.

       bbffaa oorrddeerr..bbffaa --
              Read BFA code from oorrddeerr..bbffaa translate it to  Brain
              Fuck code and write it to ssttddoouutt.

SSOOUURRCCEE CCOODDEE
       One  command  per  line. Empty lines will be ignored. Text
       behind the comment char ;; will be ignored. Spaces and tabs
       outside  quotation marks will be ignored.  To print a quo-
       tation mark it must be escaped with \\.   The  sequence  \\nn
       will  brake  a line. To print the char \\ itself it must be
       written as \\\\.

       The following standard commands are currently supported:

       MMVVLL    Move left. This is equivalent  to  the  Brain  Fuck
              command <<.

       MMVVRR    Move  right.  This  is equivalent to the Brain Fuck
              command >>.

       AADDDD    Add one. This is equivalent to the Brain Fuck  com-
              mand ++.

       SSUUBB    Subtract  one. This is equivalent to the Brain Fuck
              command --.



0.2                     January 26th, 2000                      1





bfa(1)                 Brain Fuck Assembler                bfa(1)


       GGEETT    Get char from ssttddiinn.  This  is  equivalent  to  the
              Brain Fuck command ,,.

       PPUUTT    Write  char  to  ssttddoouutt.  This is equivalent to the
              Brain Fuck command ...

       LLOOBB    Begin loop. This is equivalent to  the  Brain  Fuck
              command [[.

       LLOOEE    End loop. This is equivalent to the Brain Fuck com-
              mand ]].

       The following extended commands are currently supported:

       MMVVLL xx  Move left xx times.

       MMVVRR xx  Move right xx times.

       AADDDD xx  Add xx.

       SSUUBB xx  Subtract xx.

       GGEETT xx  Get xx chars from ssttddiinn.

       PPUUTT xx  Write character number xx to ssttddoouutt.

       PPUUTT ""TTeexxtt""
              Write text to ssttddoouutt.

       SSEETT    Set current value to zero.

       SSEETT xx  Set current value to xx.

       CCPPLL xx  Create xx copies of current value to the left. After
              this  copy action the current value will be zeroed.

       CCPPRR xx  Create xx copies of the current value to the  right.
              After  this  copy  action the current value will be
              zeroed.

EEXXIITT SSTTAATTUUSS
       00      Successfull program execution.

       11      Unsuccessfull program execution. An  error  message
              was sent to ssttddeerrrr.

SSEEEE AALLSSOO
       bbffii.

HHIISSTTOORRYY
       VVeerrssiioonn 00..11 -- 1122//1199//11999999
              Initial release.





0.2                     January 26th, 2000                      2





bfa(1)                 Brain Fuck Assembler                bfa(1)


       VVeerrssiioonn 00..22 -- 0011//2266//22000000
              bbffaa now creates optimized Brain Fuck code. Man page
              added.  Some other file changes in the archive.

AAUUTTHHOORR
       bbffaa was written by Klaus Reimer <kr@ailis.de> and is  free
       software;  you  can redistribute it and/or modify it under
       the terms of the GNU General Public License  as  published
       by  the  Free Software Foundation; either version 2 of the
       License, or (at your option) any later version.















































0.2                     January 26th, 2000                      3


